initOAT;
local_run=3;%1;%4;
fdr_prefix="gc_can_";
report_all_nt=0; % report on results from all neuron types combined
report_all_meclii_nt=0; % report on results from all MEC LII neuron types combined
neuron_types=["MEC_LII_Stellate","EC_LI_II_Multipolar_Pyramidal","EC_LII_Axo_Axonic","MEC_LII_Basket","EC_LII_Basket_Multipolar","CA1_Pyramidal"];
neuron_types_mec_lii=["MEC_LII_Stellate","EC_LI_II_Multipolar_Pyramidal","EC_LII_Axo_Axonic","MEC_LII_Basket","EC_LII_Basket_Multipolar"];
if report_all_meclii_nt == 1 neuron_types = neuron_types_mec_lii; end
neuron_type=neuron_types(5);

% 1. retrieve the spikes that will be used for analyses 

% Import Spikes
local_path=strcat('/comp_neuro/PhD/gmu/research/simulation/code/',fdr_prefix,int2str(local_run),'/results/spk_',neuron_type,'.dat');
SpikeReader(local_path, false, 'silent');
spk_data = SpikeReader(local_path, false, 'silent');
time_start=500;
time_end=time_start+2000;
bin_size=1;%-1;%1;
%t=[(time_start*(1/bin_size)):(1/bin_size):(time_end*(1/bin_size))];
spk_window = spk_data.readSpikes(bin_size);
restrict_time=1;
if report_all_nt || report_all_meclii_nt
    spk_window=[];
    for i=1:length(neuron_types)
        disp(neuron_types(i));
        local_path=strcat('/comp_neuro/PhD/gmu/research/simulation/code/',fdr_prefix,int2str(local_run),'/results/spk_',neuron_types(i),'.dat');
        SpikeReader(local_path, false, 'silent');
        spk_data = SpikeReader(local_path, false, 'silent');
        window = spk_data.readSpikes(bin_size);
        if restrict_time
            window = window(time_start:time_end,:);
        end
        spk_window = [spk_window,window];
    end
else
    if restrict_time
        spk_window = spk_window(time_start:time_end,:);
    end
end

% 2. take the sum of all the spikes at every millisecond (this should be a 2001 by 1 matrix)

spk_window=spk_window';
activity = sum(spk_window);
%spk_window=spk_window';
%activity = activity / (size(spk_window, 2));

% 3. run detrend function on the sum matrix (shifts distribution to be centered at 0)

% Compute Power Spectra from first approximation LFP
Fs = 1000; % 1000 ms per second
% activity = [1,2,3,4,5,6,7,8,9,10];
activity = detrend(activity);

% 4. compute the power spectral density in each of the rhythm bands

% Perform a FFT on the mean-centered, filtered, summed pyramidal activity
NFFT = 2^nextpow2(length(activity));
Y = fft(activity,NFFT)/length(activity);
f = Fs/2*linspace(0,1,NFFT/2+1);
ampSpec = 2*abs(Y(1:NFFT/2+1));
powSpec = ampSpec.^2;

% Find the power spectrum in the theta, gamma, and SWR range
thetaRng = find(f(:) >= 4 & f(:) <= 12);
betaRng = find(f(:) >= 12.0001 & f(:) <=24.9999);
gammaRng = find(f(:) >= 25 & f(:) <=100);
HFORng = find(f(:) >= 100.0001 & f(:) <= 149.9999);
SWRRng = find(f(:) >= 150 & f(:) <=200);

[thetaPow,thetaPeakIdx] = max(powSpec(thetaRng));
[betaPow,betaPeakIdx] = max(powSpec(betaRng));
[gammaPow,gammaPeakIdx] = max(powSpec(gammaRng));
[HFOPow,HFOPeakIdx] = max(powSpec(HFORng));
[SWRPow,SWRPeakIdx] = max(powSpec(SWRRng));

% 5. get the peaks of each rhythm band

thetaPeak = f(thetaRng(thetaPeakIdx));
betaPeak = f(betaRng(betaPeakIdx));
gammaPeak = f(gammaRng(gammaPeakIdx));
HFOPeak = f(HFORng(HFOPeakIdx));
SWRPeak = f(SWRRng(SWRPeakIdx));

powerSpecAll = [thetaPow, betaPow, gammaPow, HFOPow, SWRPow];
peaksAll = [thetaPeak, betaPeak, gammaPeak, HFOPeak, SWRPeak];

fprintf("power spectrums: total: %f theta: %f; beta: %f; gamma: %f; HFO: %f; SWR: %f",sum(powerSpecAll),powerSpecAll);
fprintf("\npower spectrums percentages: theta: %f; beta: %f; gamma: %f; HFO: %f; SWR: %f",powerSpecAll(1)/sum(powerSpecAll),powerSpecAll(2)/sum(powerSpecAll),powerSpecAll(3)/sum(powerSpecAll),powerSpecAll(4)/sum(powerSpecAll),powerSpecAll(5)/sum(powerSpecAll));
fprintf("\nrhythm peaks: theta: %f; beta: %f; gamma: %f; HFO: %f; SWR: %f\n",peaksAll);

% 6. find the rhythm range that had the highest power. round peak to nearest integer of that highest power rhythm.

highest_power_spec_idx = 1;
highest_power_spec_val = powerSpecAll(1);
for i=2:5
    if powerSpecAll(i) > highest_power_spec_val
        highest_power_spec_idx = i;
        highest_power_spec_val = powerSpecAll(i);
    end
end

rhythm_names={'Theta','Beta','Gamma','HFO','SWR'};
fprintf("Rhythm with highest power: %s\n",rhythm_names{highest_power_spec_idx});
rounded_top_peak = round(peaksAll(highest_power_spec_idx));

% 7. filter (band pass filter) the activity within that rhythm with the most power.

rhythm_hz_ranges = [[4,12];[12.0001,24.9999];[25,100];[100.0001,149.9999];[150,200]];
filteredNet = bandpass(activity,rhythm_hz_ranges(highest_power_spec_idx,:),1000);

% 8. find the peaks and locations of the peaks within the filtered activity

[pks,locs] = findpeaks(filteredNet,1000,'MinPeakDistance',5/1000,'MinPeakProminence',1.0);

% 9. compute the phase coupling relationships for each NT with the locations of the peaks
% 10. observe what the phase coupling relationships are. mean resultant vector length 
%   (normalized between 0 and 1) this will describe the strength of a NT matching a rhythm.
%   0.2 is low coupling and 0.6 or 0.7 is high coupling.

reporting_mvrl