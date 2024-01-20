%{
    Phase lock reporting
%}

% General settings
initOAT;
local_run=4;
fdr_prefix="gc_can_";
restrict_time=1; % limit time to that specified in time_start and time_end
time_start=500;%10000;
time_end=time_start+2000;%60000;%2000;%7000;
%beta=30;theta=125;gamma=25;swr=8;hfo=5;
beta=47;theta=113;gamma=18;swr=6;hfo=5; % only whole numbers should be used currently
rhythm_period=beta; % period in ms
neuron_types=["EC_LI_II_Multipolar_Pyramidal","MEC_LII_Stellate","EC_LII_Axo_Axonic","MEC_LII_Basket","EC_LII_Basket_Multipolar","CA1_Pyramidal"];
neuron_type=neuron_types(3);
bin_size=1; % bin of time in ms of spiking to use with readSpikes()

% Import Spikes
local_path=strcat('/comp_neuro/PhD/gmu/research/simulation/code/',fdr_prefix,int2str(local_run),'/results/spk_',neuron_type,'.dat');
SpikeReader(local_path, false, 'silent');
spk_data = SpikeReader(local_path, false, 'silent');
spk_window = spk_data.readSpikes(bin_size);
if restrict_time spk_window=spk_window(time_start:time_end,:); end
spk_counts=sum(spk_window, 2);
time_points=length(spk_window);

% List times with firing
firing=[];
for i=1:time_points
    time_index=i;
    if restrict_time time_index=time_index+time_start; end
    firing=[firing;[time_index,spk_counts(i)]];
end

% Convert times into period-relative times
firing(:,1)=mod(firing(:,1),rhythm_period);
firing_in_period=zeros(rhythm_period,1);
for j=1:length(firing)
    period_index=firing(j,1)+1;
    firing_in_period(period_index)=firing_in_period(period_index)+firing(j,2);
end

% Plot
bar(firing_in_period)