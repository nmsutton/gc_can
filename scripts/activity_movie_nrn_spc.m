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
hopper_use=0;
hopper_run=3;
if hopper_use
    hopper_path=strcat('/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/results/spk_MEC_LII_Stellate.dat');
    SpikeReader(hopper_path, false, 'silent');
    spk_data = SpikeReader(hopper_path, false, 'silent');
else
    SpikeReader('/comp_neuro/PhD/gmu/research/simulation/code/gc_can/results/spk_MEC_LII_Stellate.dat', false, 'silent');
    spk_data = SpikeReader('/comp_neuro/PhD/gmu/research/simulation/code/gc_can/results/spk_MEC_LII_Stellate.dat', false, 'silent');
end

delay_frames = false;%true;
time=8000;%10000;%1200000;%990; % time steps, use (end frame - 1) = time. unit is 10ms per time step
bin_size=400; % size of firing bin in ms
t=[0:(1/bin_size):(time*(1/bin_size))];
x_size = 30; % size of network on x-axis
y_size = 30; % size of network on y-axis
spk_window = spk_data.readSpikes(bin_size);
% Set up the movie structure. Preallocate recalledMovie, which will be an array of structures. First get a cell array with all the frames.
hFigure = figure;
numberOfFrames = (length(t)-1)*(1/bin_size);
if delay_frames == true
    numberOfFrames = (length(t)-1);
end
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
custom_colormap = load('neuron_space_colormap.mat');

for frameIndex = 1 : numberOfFrames
%for frameIndex = (numberOfFrames-200) : (numberOfFrames-10)
  start_frame = 0;
  imgfile = reshape(spk_window(ceil((frameIndex+start_frame)/bin_size),:),[x_size,y_size])';
  if delay_frames == false
      imgfile = reshape(spk_window((frameIndex+start_frame),:),[x_size,y_size])';
  end
  cla reset;
  hAxes = gca;
  imagesc(hAxes, imgfile);
  % use colormapeditor to edit colors
  colormap(custom_colormap.CustomColormap2);
  axis('tight')
  xlabel('neuron position on x axis') 
  ylabel('neuron position on y axis')
  shading interp;
  %caxis([0 5.5])
  %caxis([0 8.0])
  caxis([0 5.5])
  cb = colorbar;
  set(cb, 'ylim', [0 11.0]); % set colorbar range
  caption = sprintf('Neuron space grid cell firing amounts, t = %.0f ms', ((frameIndex+start_frame)*bin_size));
  if delay_frames == true
      caption = sprintf('Neuron space grid cell firing amounts, t = %.0f ms', ceil((frameIndex+start_frame)/bin_size)*bin_size);
  end
  title(caption, 'FontSize', 15);
  thisFrame = getframe(gcf);
  myMovie(frameIndex) = thisFrame;
end
close(hFigure);
temp = myMovie(1);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('./videos/firing_neuron_space.avi'); % Create a VideoWriter object to write the video out to a new, different file.
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)