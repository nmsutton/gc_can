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
stel_nS = stel_sR.readSpikes(1); % import spikes with bin of recording size of 1ms
if include_in bask_nS = bask_sR.readSpikes(1); end
stel_spk_sels = []; bask_spk_sels = [];
if include_in bask_nR=[]; bask_nV=[]; bask_sR=[]; bask_nS=[]; end
% set run params
t_start = 18000;%11400;%7000%12400;%8000;%10000;%5000; % start time
t_end = t_start+400;%600;%600;%3000;%12800;%13000;%11000;%13000; % end time
nrns_tot = 1;%3; % number of neurons to plot
i_start = 1;%51;%100; % starting neuron index
plot_spikes = 0;
t_range = linspace(t_start,t_end,(t_end-t_start+1));
% resize peak params
rsz_peaks_active = 0;%1; % toggle resizing of peaks
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
line_width_1=2; line_width_2=2; % plotted line widths
plot_legend=0; % choose if to plot legend

% extract voltages
for i=1:nrns_tot
    if plot_voltage
	    stel_sel = stel_nV.v(i+i_start,t_start:t_end);
	    if include_in bask_sel = bask_nV.v(i+i_start,t_start:t_end); end
    else
	    stel_sel = stel_nV.I(i+i_start,t_start:t_end);
	    if include_in bask_sel = bask_nV.I(i+i_start,t_start:t_end); end
    end
	stel_spk_sel = stel_nS(t_start:t_end,i+i_start);
	if include_in bask_spk_sel = bask_nS(t_start:t_end,i+i_start); end
	stel_sels(:,i) = stel_sel;
	if include_in bask_sels(:,i) = bask_sel; end
	stel_spk_sels(:,i) = stel_spk_sel;
	if include_in bask_spk_sels(:,i) = bask_spk_sel; end
end

if rsz_peaks_active
	for i=1:nrns_tot
		stel_sels(:,i)=resize_peaks(stel_sels(:,i),t_range,resize_params);
        if include_in bask_sels(:,i)=resize_peaks(bask_sels(:,i),t_range,resize_params2); end
	end
end

j=0;
clf;
for i=1:nrns_tot
	if plot_spikes plotnum = nrns_tot*2; else plotnum = nrns_tot; end
	j=j+1;
	s_plot = subplot(plotnum, 1, j);
	hold on;
    if include_in 
	    if plot_n1==1 plot(s_plot, t_range, bask_sels(:,i),'Color','#ff9900','LineWidth',line_width_1); end
    end
	if plot_n2==1 plot(s_plot, t_range, stel_sels(:,i),'Color','#80B3FF','LineWidth',line_width_2); end
	hold off;
	if plot_spikes
		j=j+1;
		s_plot = subplot(plotnum, 1, j);
		hold on;
		spks = find(stel_spk_sels(:,i)==1);
		spks=spks+t_start; % adjust for start time offset
		scatter(s_plot, spks, ones(length(spks),1)*2, 'filled','Color','#80B3FF');
		xlim([t_start t_end])
		if include_in spks = find(bask_spk_sels(:,i)==1); end
		spks=spks+t_start;
		scatter(s_plot, spks, ones(length(spks),1), 120,'Color','#ff9900');
		xlim([t_start t_end])
		caxis(s_plot,[0 3])
		hold off;
    end
    xlabel('Time (ms)','FontSize',14) 
    if plot_voltage==1 ylabel('Voltage (mV)','FontSize',14); end
    if plot_voltage==0 ylabel('Current (mA)','FontSize',14); end
    set(gca,'FontSize',14)
    if plot_legend==1 legend({'Interneuron','Grid cell'},'FontSize',10); end
    if i==1 && plot_voltage==1 title("Simulated Voltage Recordings", 'FontSize', 16); end
    if i==1 && plot_voltage==0 title("Simulated Interneuron Current Recording", 'FontSize', 16); end
end

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