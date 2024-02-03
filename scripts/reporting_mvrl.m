initOAT;
bin_size=-1;
%{
local_run=4;
fdr_prefix="gc_can_";
neuron_types=["MEC_LII_Stellate","EC_LI_II_Multipolar_Pyramidal","EC_LII_Axo_Axonic","MEC_LII_Basket","EC_LII_Basket_Multipolar","CA1_Pyramidal"];
neuron_type=neuron_types(1);
%}
%{
time_start=500;
time_end=time_start+2000;
restrict_time=1;
%}

% Import Spikes
if report_all_nt
    spk_window=[];
    for i=1:length(neuron_types)
        local_path=strcat('/comp_neuro/PhD/gmu/research/simulation/code/',fdr_prefix,int2str(local_run),'/results/spk_',neuron_types(i),'.dat');
        SpikeReader(local_path, false, 'silent');
        spk_data = SpikeReader(local_path, false, 'silent');
        window = spk_data.readSpikes(bin_size);
        if restrict_time
            window = window';
            window = window(:,1);
            window = window(find(window>time_start));
            window = window(find(window<time_end));
            spk_window = [spk_window',window'];
            spk_window = spk_window';
        else
            spk_window = [spk_window,window];
        end
    end
else
    local_path=strcat('/comp_neuro/PhD/gmu/research/simulation/code/',fdr_prefix,int2str(local_run),'/results/spk_',neuron_type,'.dat');
    SpikeReader(local_path, false, 'silent');
    spk_data = SpikeReader(local_path, false, 'silent');
    spk_window = spk_data.readSpikes(bin_size);
    if restrict_time
        spk_window = spk_window';
        spk_window = spk_window(:,1);
        spk_window = spk_window(find(spk_window>time_start));
        spk_window = spk_window(find(spk_window<time_end));
    end
end

rasterSim = spk_window;
locs2 = locs;%10000;%[50500,50500]; % locations of peaks. list of time of peaks in earier rhythm analysis results
netPer = 1000/rounded_top_peak;%100; % period_of_rhythm that was computed in step 6.
tStart = time_start; % start time in milliseconds of experiement (e.g., 500ms for fig 4 raster plot)
tf = time_end; % end time (e.g., 2500ms for fig 4 raster plot)

% Convert the locations of the peaks from s to ms
%locs2 = locs2*1000 + tStart;

% Duplicate rasterSim so as to not interfere with its data
rasterSim2 = rasterSim;

% Compute firing phase preferences, mean resultant vector lengths, and
% angular standard deviations for each neuron type relative to the filtered
% LFP. Additionally, test the spikes with a Rayleigh nonuniformity test and
% get the resultant p-values.
modActivityTimes = {};
% Note: the getspikephase line below was modified from the original version
% by not transposing [locs2(end)+netPer:netPer:(tf+netPer)] due to an error
% from that.
[angle, magnitude, modactivitytimes]=getspikephase(rasterSim2, netPer, [locs2(1)-netPer, locs2, [locs2(end)+netPer:netPer:(tf+netPer)]]);
phase = mod(angle+pi,2*pi)*180/pi;
MRVL = circ_r(modactivitytimes*pi/(netPer/2));
meanPhase = wrapTo360(rad2deg(real(circ_mean(modactivitytimes*pi/(netPer/2)))));
stdPhase = wrapTo360(rad2deg(real(circ_std(modactivitytimes*pi/(netPer/2)))));
modActivityTimes{end+1} = modactivitytimes;
if size(modactivitytimes,1) > 0
    [pval zval] = circ_rtest(modactivitytimes*pi/(netPer/2));
    rayleighPVals = pval;
else
    rayleighPVals = NaN;
end

fprintf("\nMVRL: %.2f p-val: %.15f\n",MRVL,pval);