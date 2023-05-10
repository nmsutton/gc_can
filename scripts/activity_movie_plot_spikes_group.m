initOAT;
SR = SpikeReader('../results/spk_MEC_LII_Stellate.dat');
spikes = SR.readSpikes(1); X=[]; Y=[];
T=size(spikes,1); % time to plot
fn = 75; % first neuron to plot
N=50; % number of spikes to plot
t_window = 5000;%1500;
min_y = fn;
max_y = fn+N;

% animation
hFigure = figure;
hFigure.Position = [1 0 1920 204];
time_bin = 40;
t_start = 1; % start time
t_end = t_start+300000;
numberOfFrames = ((t_end-t_start))*(1/time_bin);
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
    t_start = frameIndex*time_bin; % start time
    t_end = t_start+t_window; % end time
    t_range = linspace(t_start,t_end,(t_end-t_start+1));
    for y=t_start:t_end
    for x=1:N
      if spikes(y,x+fn)==1 X=[X;x+fn]; Y=[Y;y]; end
    end
    end
    X=X(Y>=t_start); % clear old times
    Y=Y(Y>=t_start); % clear old times
    scatter(Y,X,50,"filled");
    caption = sprintf("Spike Times, t = %.0f ms", t_end);
    title(caption, 'FontSize', 16);
    set(gca,'FontSize',14)
    axis('tight'); xlabel('Time'); ylabel('Neuron');
    ylim([min_y max_y])
    xlim([t_start t_end])
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