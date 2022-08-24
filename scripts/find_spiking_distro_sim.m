% find distribution of spiking Hz

initOAT;
hopper_use=1;
hopper_run=5;
if hopper_use
    hopper_path=strcat('/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/results/spk_MEC_LII_Stellate.dat');
    SpikeReader(hopper_path, false, 'silent');
    spk_data = SpikeReader(hopper_path, false, 'silent');
else
    SpikeReader('/comp_neuro/PhD/gmu/research/simulation/code/gc_can/results/spk_MEC_LII_Stellate.dat', false, 'silent');
    spk_data = SpikeReader('/comp_neuro/PhD/gmu/research/simulation/code/gc_can/results/spk_MEC_LII_Stellate.dat', false, 'silent');
end
bin_size=400; % size of firing bin in ms
spikes = spk_data.readSpikes(bin_size);
nrn_count = size(spikes(1,:),2);
spk_count = [];
sim_seconds = (size(spikes(:,1),1)*bin_size)/1000;
spk_hz = [];

for i=1:nrn_count
    count = sum(spikes(:,i));
    spk_count = [spk_count; count];
    spk_hz = [spk_hz; count/sim_seconds];
end

% plot
hist(spk_hz);
axis('tight')
xlabel('Spiking Frequency of Neurons (Hz)') 
ylabel('Neuron Count')
caption = sprintf('Spiking Frequencies of %d Simulated Neurons',nrn_count);
title(caption, 'FontSize', 15);

fprintf("mode:%f median:%f sum:%f mean:%f max:%f\n",mode(spk_hz),median(spk_hz),sum(spk_hz),mean(spk_hz),max(spk_hz));