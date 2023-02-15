initOAT;
SR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
spikes = SR.readSpikes(1); X=[]; Y=[];
T=size(spikes,1); % time to plot
fn = 75; % first neuron to plot
N=50; % number of spikes to plot
%for y=1:T 
for y=1:30000
for x=1:N
  if spikes(y,x+fn)==1 X=[X;x+fn]; Y=[Y;y]; end
end
end
scatter(Y,X,10);
title("Spike Times", 'FontSize', 11); axis('tight'); xlabel('Time'); ylabel('Neuron');