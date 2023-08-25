initOAT;
use_selected_time=1; % use file with selected time of spikes
if use_selected_time==0
    SR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
    spikes = SR.readSpikes(1); X=[]; Y=[];
elseif use_selected_time==1
    spikes = readmatrix('sel_spks.csv'); X=[]; Y=[];
end
T=size(spikes,1); % time to plot
%fn = 75; % first neuron to plot
N=50; % number of spikes to plot
n_order=randperm(N);
t_window = 5000;%1500;
min_y = 1;%fn;
max_y = N;%fn+N;

% animation
hFigure = figure;
hFigure.Position = [1 0 1920 204];
time_bin = 40;
t_start = 1;%8180000;%10000; % start time
t_end = t_start+300000;
alter_plot_start_time = 0;
if use_selected_time==1
    alter_plot_start_time = 3600000; % add time to the time reported in the plot
end
numberOfFrames = (t_end-t_start)*(1/time_bin);
allTheFrames = cell(numberOfFrames,1);
vidHeight = 300;%337;
vidWidth = 1920;%442;
allTheFrames(:) = {zeros(vidHeight, vidWidth, 3, 'uint8')};
% Next get a cell array with all the colormaps.
allTheColorMaps = cell(numberOfFrames,1);
allTheColorMaps(:) = {zeros(256, 3)};
% Now combine these to make the array of structures.
myMovie = struct('cdata', allTheFrames, 'colormap', allTheColorMaps); 
set(gcf, 'nextplot', 'replacechildren'); 
% Need to change from the default renderer to zbuffer to get it to work right. openGL doesn't work and Painters is way too slow.
set(gcf, 'renderer', 'zbuffer');
caxis manual; % allow subsequent plots to use the same color limits

for frameIndex = 1 : numberOfFrames
    cla reset;
    hAxes = gca;
    t_start2 = t_start+(frameIndex*time_bin); % start time
    t_end2 = t_start2+t_window; % end time
    t_range = linspace(t_start2,t_end2,(t_end2-t_start2+1));
    for y=t_start2:t_end2
    for x=1:N
      %if spikes(y,x+fn)==1 X=[X;x+fn]; Y=[Y;y]; end
      if spikes(y,n_order(x))==1 X=[X;x]; Y=[Y;y]; end
    end
    end
    X=X(Y>=t_start2); % clear old times
    Y=Y(Y>=t_start2); % clear old times
    scatter(Y,X,50,"filled");
    caption = sprintf("Spike Times, t = %.0f ms", (alter_plot_start_time+t_end2));
    title(caption, 'FontSize', 16);
    set(gca,'FontSize',14)
    axis('tight'); xlabel('Time'); ylabel('Neuron');
    ylim([min_y max_y])
    xlim([t_start2 t_end2])
    thisFrame = getframe(gcf);
    myMovie(frameIndex) = thisFrame;
end

close(hFigure);
temp = myMovie(1);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('./videos/spike_group_movie.avi'); % Create a VideoWriter object to write the video out to a new, different file.
% fix color map
for i=1:length(myMovie)
    myMovie(i).colormap=[];%zeros(256, 3);
end
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)
