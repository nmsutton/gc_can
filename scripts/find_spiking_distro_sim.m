% find distribution of spiking Hz

initOAT;
hopper_use=0;
local_run=3;
hopper_run=7;
hopper_local_copy=0;
fdr_prefix="gc_can_";
if hopper_use
    hopper_path=strcat('/mnt/hopper_scratch/gc_sim/',fdr_prefix,int2str(hopper_run),'/results/spk_MEC_LII_Stellate.dat');
    SpikeReader(hopper_path, false, 'silent');
    spk_data = SpikeReader(hopper_path, false, 'silent');
else
    if hopper_local_copy == 0
        local_path=strcat('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_',int2str(local_run),'/results/spk_MEC_LII_Stellate.dat');
    else
        local_path=strcat('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_hopper/results/spk_MEC_LII_Stellate.dat');
    end
    SpikeReader(local_path, false, 'silent');
    spk_data = SpikeReader(local_path, false, 'silent');
end
bin_size=400; % size of firing bin in ms
target_hz=2.36557; % target Hz to search for
similarity=90; % similarity percent to find
similarity=1-(similarity/100);
if 1
    spikes = spk_data.readSpikes(bin_size);
end
%spk_x=[spk_x,x(floor(spk_t(i)/timestep))];
nrn_count = size(spikes(1,:),2);
spk_count = [];
sim_seconds = (size(spikes(:,1),1)*bin_size)/1000;
spk_hz = [];

for i=1:nrn_count
    count = sum(spikes(:,i));
    spk_count = [spk_count; count];
    spk_hz = [spk_hz; count/sim_seconds];
end

high_spk=[find(spk_hz>=target_hz-similarity) spk_hz(find(spk_hz>=target_hz-similarity))];
high_spk=high_spk(find(high_spk(:,2)<target_hz+similarity),:);

% plot
hist(spk_hz);
axis('tight')
xlabel('Spiking Frequency of Neurons (Hz)') 
ylabel('Neuron Count')
caption = sprintf('Spiking Frequencies of %d Simulated Neurons',nrn_count);
title(caption, 'FontSize', 15);

fprintf("mode:%f median:%f sum:%f mean:%f max:%f\n",mode(spk_hz),median(spk_hz),sum(spk_hz),mean(spk_hz),max(spk_hz));