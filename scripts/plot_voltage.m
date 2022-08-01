% Plot voltage for article figure
% Note: SpikeReader returns entries with 1 less index then NeuronReader.
% E.g., length(stel_nV.v) vs. length(stel_nS).
% Todo: This could be looked into to see if the indices are offset by 1.

initOAT;
% read in voltages
stel_nR = NeuronReader('../results/n_MEC_LII_Stellate.dat');
bask_nR = NeuronReader('../results/n_MEC_LII_Basket_Speed.dat');
stel_nV = stel_nR.readValues();
bask_nV = bask_nR.readValues();
stel_sels = []; bask_sels = [];
% read in spikes
stel_sR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
bask_sR = SpikeReader('../results/spk_MEC_LII_Basket_Speed.dat');
stel_nS = stel_sR.readSpikes(1); % import spikes with bin of recording size of 1ms
bask_nS = bask_sR.readSpikes(1);
stel_spk_sels = []; bask_spk_sels = [];
t_start = 4000;
t_end = 6500;
nrns_tot = 5; % number of neurons to plot
i_start = 0; % starting neuron index
t_range = linspace(t_start,t_end,(t_end-t_start+1));
% resize peak params
rsz_peaks_active = 0; % toggle resizing of peaks
window_size = 50; % size of rolling window
min_spk_v = -50; % minimum voltage to be detected as a spike
min_isi = 20; % minimum inter-spike interval
new_peak = 10; % new peak voltage
resize_params=[window_size,min_spk_v,min_isi,new_peak];

% extract voltages
for i=1:nrns_tot
	stel_sel = stel_nV.v(i+i_start,t_start:t_end);
	bask_sel = bask_nV.v(i+i_start,t_start:t_end);
	stel_spk_sel = stel_nS(t_start:t_end,i+i_start);
	bask_spk_sel = bask_nS(t_start:t_end,i+i_start);
	stel_sels = [stel_sels; stel_sel];
	bask_sels = [bask_sels; bask_sel];
	stel_spk_sels = [stel_spk_sels; stel_spk_sel'];
	bask_spk_sels = [bask_spk_sels; bask_spk_sel'];
end

if rsz_peaks_active
	for i=1:nrns_tot
		stel_sels(i,:)=resize_peaks(stel_sels(i,:),t_range,resize_params);
	end
end

j=0;
for i=1:nrns_tot
	j=j+1;
	s_plot = subplot(nrns_tot*2, 1, j);
	hold on;
	plot(s_plot, t_range, bask_sels(i,:),'Color','#ff9900','LineWidth',1);
	plot(s_plot, t_range, stel_sels(i,:),'Color','#80B3FF','LineWidth',2);
	hold off;
	j=j+1;
	s_plot = subplot(nrns_tot*2, 1, j);
	hold on;
	spks = find(stel_spk_sels(i,:)==1);
	spks=spks+t_start; % adjust for start time offset
	%scatter(s_plot, spks, ones(length(spks),1)*2, 120,'Color','#80B3FF');
	scatter(s_plot, spks, ones(length(spks),1)*2, 'filled','Color','#80B3FF');
	xlim([t_start t_end])
	spks = find(bask_spk_sels(i,:)==1);
	spks=spks+t_start;
	scatter(s_plot, spks, ones(length(spks),1), 120,'Color','#ff9900');
	xlim([t_start t_end])
	caxis(s_plot,[0 3])
	hold off;
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