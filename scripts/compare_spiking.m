%
% Compare simulated spike times to real spike times
%

cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts/for_jeffrey/'
load_data
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/'

animal_spikes = spikes(3,:)';
sim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');
%sim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/in_spikes_recorded.csv');
time_limit_start = 450000; % time limit start in ms
time_limit_end = time_limit_start + 50000;%2400000; 
limit_indices = find(animal_spikes(find(animal_spikes*1000>time_limit_start))*1000<time_limit_end);
plot_data1 = animal_spikes(limit_indices)*1000;
plot_data1(:,2)=ones(1,length(limit_indices));
limit_indices = find(sim_spikes(find(sim_spikes>time_limit_start))<time_limit_end);
plot_data2 = sim_spikes(limit_indices);
plot_data2(:,2)=ones(1,length(limit_indices))*2;
plot_data_comb = [plot_data1;plot_data2];

scatter(plot_data_comb(:,1),plot_data_comb(:,2),300,'|');
a = axis;
a(3) = 0; a(4) = 3;
axis(a);
caption = sprintf('Sim vs. Real Spiking %.0f - %.0f ms', time_limit_start, time_limit_end);
title(caption, 'FontSize', 20);
xlabel('Time in ms','FontSize',20) 
ylabel('Animal              Simulation','FontSize',20)
legend({'Animal data y-value=1     Sim data y-value=2'},'FontSize',20)
set(gca,'FontSize',20)