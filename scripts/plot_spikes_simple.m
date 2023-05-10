initOAT;
SR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
spikes = SR.readSpikes(1); X=[]; Y=[];
T=size(spikes,1); % time to plot
fn = 1; % first neuron to plot
N=49; % number of spikes to plot
%for y=1:T 
%for y=1:30000
for y=2400:2600%30000
for x=fn:(fn+N)
  if spikes(y,x+fn)==1 X=[X;x+fn]; Y=[Y;y]; end
end
end
scatter(Y,X,30,'filled');
title("Spike Times", 'FontSize', 11); xlabel('Time'); ylabel('Neuron');
ylim([fn (fn+N)]);