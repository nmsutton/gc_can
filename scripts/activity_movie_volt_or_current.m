% Plot voltage for article figure
% Note: SpikeReader returns entries with 1 less index then NeuronReader.
% E.g., length(stel_nV.v) vs. length(stel_nS).
% Todo: This could be looked into to see if the indices are offset by 1.

initOAT;
plot_voltage=1; % choose to plot current or voltage
include_in=0; % choose to include interneurons
% read in voltages
stel_nR = NeuronReader('../results/n_MEC_LII_Stellate.dat');
if include_in bask_nR = NeuronReader('../results/n_MEC_LII_Basket.dat'); end
stel_nV = stel_nR.readValues();
if include_in bask_nV = bask_nR.readValues(); end
stel_sels = []; bask_sels = [];
% read in spikes
stel_sR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
if include_in bask_sR = SpikeReader('../results/spk_MEC_LII_Basket.dat'); end
stel_nS = [0];%stel_sR.readSpikes(1); % import spikes with bin of recording size of 1ms
if include_in bask_nS = bask_sR.readSpikes(1); end
stel_spk_sels = []; bask_spk_sels = [];
if include_in==0 bask_nR=[0]; bask_nV=[0]; bask_sR=[0]; bask_nS=[0]; end
% set run params
t_start = 1;%3600000;%8180000;%10000;%7200000;%1;%17500;%11400;%7000%12400;%8000;%10000;%5000; % start time
t_end = t_start+10000;%302000;%10000;%1500;%600;%3000;%12800;%13000;%11000;%13000; % end time
t_window = 5000;%1500;
nrns_tot = 1;%3; % number of neurons to plot
nrn_select = 1;%100; % starting neuron index
plot_spikes = 0;
t_range = linspace(t_start,t_end,(t_end-t_start+1));
% resize peak params
rsz_peaks_active = 1;%1; % toggle resizing of peaks
window_size = 50; % size of rolling window
min_spk_v = 0;%-20; % minimum voltage to be detected as a spike
min_isi = 5; % minimum inter-spike interval
new_peak = 40;%10; % new peak voltage
resize_params=[window_size,min_spk_v,min_isi,new_peak];
window_size2 = 50; % size of rolling window
min_spk_v2 = -30;%-20; % minimum voltage to be detected as a spike
min_isi2 = 20; % minimum inter-spike interval
new_peak2 = 40;%10; % new peak voltage
resize_params2=[window_size2,min_spk_v2,min_isi2,new_peak2];
plot_n1=0; plot_n2=1; % choose neurons to plot
plot_legend=0; % choose if to plot legend

% animation
hFigure = figure;
hFigure.Position = [1 0 1920 204];
time_bin = 40;%10;
numberOfFrames = (t_end-t_start)*(1/time_bin);
allTheFrames = cell(numberOfFrames,1);
vidHeight = 300;%337;
vidWidth = 1920;%442;
min_y = -80;
max_y = 40;
allTheFrames(:) = {zeros(vidHeight, vidWidth, 3, 'uint8')};
% Next get a cell array with all the colormaps.
allTheColorMaps = cell(numberOfFrames,1);
allTheColorMaps(:) = {zeros(256, 3)};
% Now combine these to make the array of structures.
myMovie = struct('cdata', allTheFrames, 'colormap', allTheColorMaps); 
set(gcf, 'nextplot', 'replacechildren'); 
% Need to change from the default renderer to zbuffer to get it to work right. openGL doesn't work and Painters is way too slow.
set(gcf, 'renderer', 'zbuffer');
caxis manual; % allow subsequent plots to use the same color limits

for frameIndex = 1 : numberOfFrames
    cla reset;
    hAxes = gca;
    t_start2 = t_start+(frameIndex*time_bin); % start time
    t_end2 = t_start2+t_window; % end time
    t_range = linspace(t_start2,t_end2,(t_end2-t_start2+1));
    [stel_sels, t_range]=extract_voltages(plot_voltage, stel_nV, bask_nV, stel_nS, ...
                bask_nS, rsz_peaks_active, resize_params, resize_params2, nrn_select, ...
                t_start2, t_end2, t_range, include_in);
    if include_in 
        if plot_n1==1 plot(t_range, bask_sels(:,1),'Color','#ff9900','LineWidth',2); end
    end
    if plot_n2==1 plot(t_range, stel_sels(:,1),'Color','#80B3FF','LineWidth',2); end
    set(gca,'FontSize',14)
    xlabel('Time (ms)','FontSize',14) 
    if plot_voltage==1 ylabel('Voltage (mV)','FontSize',14); end
    caption = sprintf("Simulated Voltage Recordings, t = %.0f ms", t_end2);
    if plot_voltage==1 title(caption, 'FontSize', 16); end
    ylim([min_y max_y])
    xlim([t_start2 t_end2])
    thisFrame = getframe(gcf);
    myMovie(frameIndex) = thisFrame;
end

close(hFigure);
temp = myMovie(1);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('./videos/volt_movie.avi'); % Create a VideoWriter object to write the video out to a new, different file.
% fix color map
for i=1:length(myMovie)
    myMovie(i).colormap=[];%zeros(256, 3);
end
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)

function volt_sel=resize_peaks(volt_sel,t_range,resize_params)
	% resize peak voltages for biological realism
	window_size=resize_params(1);min_spk_v=resize_params(2);
	min_isi=resize_params(3);new_peak=resize_params(4);last_spk=window_size*-1;
	for i=1:length(t_range)
		peak_v = -500; % peak voltage
		peak_i = 0; % peak voltage index
		spk_detect = 0; % spike detected
		for j=0:window_size-1
			if i+window_size<length(t_range) && volt_sel(i+j)>peak_v && volt_sel(i+j)>min_spk_v
				peak_v=volt_sel(i+j);
				peak_i=i+j;
				spk_detect=1;
			end
		end
		if i+window_size<length(t_range) && spk_detect && peak_i > last_spk+min_isi
			volt_sel(peak_i)=new_peak;
			last_spk=peak_i;
		end
	end
end

function [stel_sels, t_range]=extract_voltages(plot_voltage, stel_nV, bask_nV, stel_nS, ...
            bask_nS, rsz_peaks_active, resize_params, resize_params2, nrn_select, ...
            t_start2, t_end2, t_range, include_in)
    if plot_voltage
        %stel_sel = stel_nV.v(nrn_select,t_start2:t_end2);
        stel_sel = stel_nV.v(nrn_select,t_start2:t_end2);
        if include_in bask_sel = bask_nV.v(nrn_select,t_start2:t_end2); end
    else
        stel_sel = stel_nV.I(nrn_select,t_start2:t_end2);
        if include_in bask_sel = bask_nV.I(nrn_select,t_start2:t_end2); end
    end
    %stel_spk_sel = stel_nS(t_start2:t_end2,nrn_select);
    if include_in bask_spk_sel = bask_nS(t_start2:t_end2,nrn_select); end
    stel_sels(:,1) = stel_sel;
    if include_in bask_sels(:,1) = bask_sel; end
    %stel_spk_sels(:,1) = stel_spk_sel;
    %if include_in bask_spk_sels(:,1) = bask_spk_sel; end
    
    if rsz_peaks_active
	    stel_sels(:,1)=resize_peaks(stel_sels(:,1),t_range,resize_params);
        if include_in bask_sels(:,1)=resize_peaks(bask_sels(:,1),t_range,resize_params2); end
    end
end