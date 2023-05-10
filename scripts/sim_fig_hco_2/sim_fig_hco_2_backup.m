% Plot voltage and spike times for sim figure in hco 2.0 article

run("../initOAT");
% read in voltages
stel_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_MEC_LII_Stellate.dat');
bask_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_MEC_LII_Basket.dat');
pyra_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_CA1_Pyramidal.dat');
axoa_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_EC_LII_Axo_Axonic.dat');
bkmp_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_EC_LII_Basket_Multipolar.dat');
mppy_nR = NeuronReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/n_EC_LI_II_Multipolar_Pyramidal.dat');
stel_nV = stel_nR.readValues();
bask_nV = bask_nR.readValues();
pyra_nV = pyra_nR.readValues();
axoa_nV = axoa_nR.readValues();
bkmp_nV = bkmp_nR.readValues();
mppy_nV = mppy_nR.readValues();
stel_sels = []; bask_sels = []; pyra_sels = [];
axoa_sels = []; bkmp_sels = []; mppy_sels = [];
% read in spikes
stel_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_MEC_LII_Stellate.dat');
bask_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_MEC_LII_Basket.dat');
pyra_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_CA1_Pyramidal.dat');
axoa_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_EC_LII_Axo_Axonic.dat');
bkmp_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_EC_LII_Basket_Multipolar.dat');
mppy_sR = SpikeReader('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/hco_2/sim_fig/results/spk_EC_LI_II_Multipolar_Pyramidal.dat');
stel_nS = stel_sR.readSpikes(1); % import spikes with bin of recording size of 1ms
bask_nS = bask_sR.readSpikes(1);
pyra_nS = pyra_sR.readSpikes(1);
axoa_nS = axoa_sR.readSpikes(1);
bkmp_nS = bkmp_sR.readSpikes(1);
mppy_nS = mppy_sR.readSpikes(1);
stel_spk_sels = []; bask_spk_sels = []; pyra_spk_sels = [];
axoa_spk_sels = []; bkmp_spk_sels = []; mppy_spk_sels = [];
% set run params
t_start = 800;%1;%800;%12400;%11400;%7000%12400;%8000;%10000;%5000; % start time
t_end = t_start+400;%10000;%400;%600;%3000;%12800;%13000;%11000;%13000; % end time
nrns_tot = 1; % number of neurons to plot
i_start = 51;%100; % starting neuron index
plot_spikes = 1;
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
plot_n1=1; plot_n2=1; % choose neurons to plot
%line_width_1=2; line_width_2=2; % plotted line widths
line_width_1=1; line_width_2=1; % plotted line widths
plot_legend=0; % choose if to plot legend
plotnum = 12; % number of total subplots
fn = 1; % first neuron to plot
N=49; % number of spikes to plot
X=[]; Y=[];
spike_marker_size=5;%30;%5;
%neuron_numbers=randperm(128,49); % generate non-repeating list of random integers
%neuron_numbers=randperm(128,20); % generate non-repeating list of random integers
%neuron_numbers=[neuron_numbers,randperm(833,29)];
neuron_numbers=load('neuron_numbers3.mat'); % load pseudo-random neuron numbers list for repeatablility
neuron_numbers=neuron_numbers.neuron_numbers;
%volt_nn = [116,68,116,68,68,68]; % neuron numbers to include in voltage plot
%volt_nn = [neuron_numbers(1),neuron_numbers(1),neuron_numbers(1),neuron_numbers(1),neuron_numbers(1),neuron_numbers(1)];
volt_nn = [55,22,55,123,102,117];%102%86%8
colors=[
[.224,.698,.898]; % stel
[.925,.608,.643]; % pyra
[.553,.157,.118]; % mp pyra
[.467,.737,.396]; % axo-a
[.204,.396,.643]; % bask
[.357,.153,.490]; % bask mp
];
j=0; i=1; clf;

% extract voltages
for i=1:nrns_tot
    stel_sel = stel_nV.v(volt_nn(1),t_start:t_end);
	pyra_sel = pyra_nV.v(volt_nn(2),t_start:t_end);
    mppy_sel = mppy_nV.v(volt_nn(3),t_start:t_end);
	axoa_sel = axoa_nV.v(volt_nn(4),t_start:t_end);
	bask_sel = bask_nV.v(volt_nn(5),t_start:t_end);
    bkmp_sel = bkmp_nV.v(volt_nn(6),t_start:t_end);
	stel_sels(:,i) = stel_sel;
	pyra_sels(:,i) = pyra_sel;
	mppy_sels(:,i) = mppy_sel;
	axoa_sels(:,i) = axoa_sel;
	bask_sels(:,i) = bask_sel;
	bkmp_sels(:,i) = bkmp_sel;
end

if rsz_peaks_active
	for i=1:nrns_tot
		stel_sels(:,i)=resize_peaks(stel_sels(:,i),t_range,resize_params);
        pyra_sels(:,i)=resize_peaks(pyra_sels(:,i),t_range,resize_params);
		mppy_sels(:,i)=resize_peaks(mppy_sels(:,i),t_range,resize_params);
        axoa_sels(:,i)=resize_peaks(axoa_sels(:,i),t_range,resize_params2);
        bask_sels(:,i)=resize_peaks(bask_sels(:,i),t_range,resize_params2);
		bkmp_sels(:,i)=resize_peaks(bkmp_sels(:,i),t_range,resize_params2);
	end
end

% plot spikes
% % stellate
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(stel_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(1,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% % pyramial
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(pyra_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(2,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% % mp pyramidal
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(mppy_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(3,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% % axo-axonic
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(axoa_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(4,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% % basket
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(bask_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(5,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% % basket mp
j=j+1; s_plot = subplot(plotnum, 1, j); X=[]; Y=[];
[X,Y]=find_spikes(bkmp_nS, t_start, t_end, neuron_numbers, N, X, Y);
scatter(s_plot, X,Y,spike_marker_size,colors(6,:),'filled');
xlim([t_start t_end]); ylim([fn (fn+N)]);
% plot voltage
% % stellate
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, stel_sels(:,1),'Color',colors(1,:),'LineWidth',line_width_2);
ylim(s_plot,[-70 40]);
% % pyramidal
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, pyra_sels(:,1),'Color',colors(2,:),'LineWidth',line_width_1);
ylim(s_plot,[-70 40]);
% % mp pyramidal
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, mppy_sels(:,1),'Color',colors(3,:),'LineWidth',line_width_1);
ylim(s_plot,[-70 40]);
% % axo-axonic
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, axoa_sels(:,1),'Color',colors(4,:),'LineWidth',line_width_1);
ylim(s_plot,[-70 40]);
% % basket
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, bask_sels(:,1),'Color',colors(5,:),'LineWidth',line_width_1);
ylim(s_plot,[-70 40]);
% % basket mp
j=j+1; s_plot = subplot(plotnum, 1, j);
plot(s_plot, t_range, bkmp_sels(:,1),'Color',colors(6,:),'LineWidth',line_width_1);
ylim(s_plot,[-70 40]);
%xlabel('Time (ms)','FontSize',14) 
%ylabel('Voltage (mV)','FontSize',14);
%set(gca,'FontSize',14)
%if plot_legend==1 legend({'Interneuron','Grid cell'},'FontSize',10); end
%if i==1 title("Simulated Voltage Recordings", 'FontSize', 16); end

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

function [X,Y]=find_spikes(stel_nS, t_start, t_end, neuron_numbers, N, X, Y)
	for y=t_start:t_end
		for x2=1:N
			x=neuron_numbers(x2);
			spk_sel = stel_nS(t_start:t_end,x);
			spk_sels(:,x) = spk_sel;
			spks = find(spk_sels(:,x)==1);
			spks=spks+t_start; % adjust for start time offset
			X=[X;spks];
			Y=[Y;ones(length(spks),1)*x2];
		end
	end
end