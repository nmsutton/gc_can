%
% This script generates custom movies from CARLsim simulation results.
% 
% Author: Nate Sutton, 2022
%
% References: 
% https://www.mathworks.com/matlabcentral/answers/154659-how-to-create-animation-of-matlab-plotting-points-on-a-graph
% https://www.mathworks.com/matlabcentral/answers/220094-how-do-i-make-a-video-of-a-graph-with-axes-and-axes-labels
% https://www.mathworks.com/matlabcentral/answers/285058-how-to-keep-the-numbers-on-the-colorbar-scale-of-a-surface-plot-fixed
%

clear all;
clc;
initOAT;
SpikeReader('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/results/spk_gc_exc.dat', false, 'silent');
spk_data = SpikeReader('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/results/spk_gc_exc.dat', false, 'silent');
time=250; % time steps, use (end frame - 1) = time
t=[0:0.1:(time*.1)];
bin_size = 10; % size of firing bin in ms
x_size = 20; % size of network on x-axis
y_size = 20; % size of network on y-axis
spk_window = spk_data.readSpikes(bin_size);
% Set up the movie structure. Preallocate recalledMovie, which will be an array of structures. First get a cell array with all the frames.
hFigure = figure;
numberOfFrames = length(t);
allTheFrames = cell(numberOfFrames,1);
vidHeight = 337;
vidWidth = 442;
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
  imgfile = reshape(spk_window(frameIndex,:),[x_size,y_size])';
  cla reset;
  imagesc(imgfile);
  axis('tight')
  xlabel('neuron position on x axis') 
  ylabel('neuron position on y axis')
  shading interp;
  caxis([0 5.5])
  cb = colorbar;
  set(cb, 'ylim', [0 5.5]); % set colorbar range
  caption = sprintf('Grid cell firing amounts, t = %.0f ms', (frameIndex*10));
  title(caption, 'FontSize', 15);
  thisFrame = getframe(gcf);
  myMovie(frameIndex) = thisFrame;
end
close(hFigure);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('firing.avi'); % Create a VideoWriter object to write the video out to a new, different file.
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)