% plot voltage for article figure

initOAT;
stel_nR = NeuronReader('../results/n_MEC_LII_Stellate.dat');
bask_nR = NeuronReader('../results/n_MEC_LII_Basket.dat');
stel_nV = stel_nR.readValues();
bask_nV = bask_nR.readValues();
stel_sels = []; bask_sels = [];
t_start = 5000;
t_end = 6500;
nrns_tot = 10; % number of neurons to plot
t_range = linspace(t_start,t_end,(t_end-t_start+1));
% resize peak params
rsz_peaks_active = 1; % toggle resizing of peaks
window_size = 50; % size of rolling window
min_spk_v = -50; % minimum voltage to be detected as a spike
min_isi = 20; % minimum inter-spike interval
new_peak = 10; % new peak voltage
resize_params=[window_size,min_spk_v,min_isi,new_peak];

% extract voltages
%{
cell_e = 1;
cell_i = 1;
stel_sel = stel_nV.v(cell_e,t_start:t_end);
bask_sel = bask_nV.v(cell_i,t_start:t_end);
cell_e = 150;
cell_i = 150;
stel_sel2 = stel_nV.v(cell_e,t_start:t_end);
bask_sel2 = bask_nV.v(cell_i,t_start:t_end);
cell_e = 75;
cell_i = 75;
stel_sel3 = stel_nV.v(cell_e,t_start:t_end);
bask_sel3 = bask_nV.v(cell_i,t_start:t_end);
%}
% extract voltages
for i=1:nrns_tot
	stel_sel = stel_nV.v(i,t_start:t_end);
	bask_sel = bask_nV.v(i,t_start:t_end);
	stel_sels = [stel_sels; stel_sel];
	bask_sels = [bask_sels; bask_sel];
end

if rsz_peaks_active
	for i=1:nrns_tot
		stel_sels(i,:)=resize_peaks(stel_sels(i,:),t_range,resize_params);
	end
end

for i=1:nrns_tot
	s_plot = subplot(nrns_tot, 1, i);
	hold on;
	plot(s_plot, t_range, stel_sels(i,:));
	plot(s_plot, t_range, bask_sels(i,:));
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