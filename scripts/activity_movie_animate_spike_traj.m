% reference https://www.mathworks.com/help/matlab/ref/animatedline.html#:~:text=Create%20an%20animation%20by%20adding,loop%20using%20the%20addpoints%20function.&text=an%20%3D%20animatedline(%20x%20%2C%20y%20)%20creates%20an%20animated%20line,x%20%2C%20y%20%2C%20and%20z%20.

close all;

% run options
use_hopper_data = 0;
local_run=6;
hopper_run = 7;
plot_spikes = 1; 
min_x = 0;%3.5;%4.5;
max_x = 40;%min_x+32;%31;
min_y = 0;%3.5;%4.5;
max_y = 40;%min_y+32;%31;
crop=4; % amount of space to crop
tick_size = 20; % spike marker size
spk_bin_size = 10; % spike reader bin size. Note: small bin sizes may take long processing with large spike sets. 40min sim with bin size 1 can take 10min to create plot.
% select neuron to plot
sel_nrn=1;%100;%348;%110;%210;%262;%454;%454;%453;%455;%591;%629;%547;%629;%494;%290;%393;%243;%358;%338;%210;%290;%497;%860;%810;%300;%1250;%410;%820;%516;%1228;%690;
spikes=[];
fdr_prefix="gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
start_time = 3604500;%1695000;%8180000;%30000;%1;
restrict_time = 302000;%367000;%300000; % 0 for no restriction or input time value for restriction
timestep=20;
hFigure = figure;

% load scripts
curr_dir=pwd;
curr_dir=replace(curr_dir,"gc_can_1",strcat(fdr_prefix,int2str(local_run)));
cd(curr_dir);
%cd ..
initOAT
cd(curr_dir);
addpath /comp_neuro/Software/Github/CMBHOME_github/

% load traj data
Xs = readmatrix(strcat('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_',int2str(local_run),'/output/spikes/highres_pos_x.csv'));
Ys = readmatrix(strcat('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_',int2str(local_run),'/output/spikes/highres_pos_y.csv'));

% load spike times
if plot_spikes
    spk_x = []; spk_y = [];
    [spk_t,spikes]=load_spk_times(use_hopper_data, hopper_run, ...
    spk_bin_size, sel_nrn, spikes, ...
    fdr_prefix, local_run, curr_dir);
end

time = restrict_time;
if restrict_time == 0
    time = length(Xs);
end

% video
numberOfFrames = (time/timestep);
allTheFrames = cell(numberOfFrames,1);
vidHeight = 337;%342;
vidWidth = 442;%434;
allTheFrames(:) = {zeros(vidHeight, vidWidth, 3, 'uint8')};
allTheColorMaps = cell(numberOfFrames,1);
allTheColorMaps(:) = {zeros(256, 3)};
myMovie = struct('cdata', allTheFrames, 'colormap', allTheColorMaps);
set(gcf, 'nextplot', 'replacechildren'); 
set(gcf, 'renderer', 'zbuffer');
caxis manual;          % allow subsequent plots to use the same color limits

for t = 1:timestep:time
    clf(hFigure)
	hold on
    plot(Xs(1:start_time),Ys(1:start_time),'LineWidth',1,'Color','black');
    if plot_spikes spikes = find(spk_t < (start_time+t)); end
    %scatter(Xs(1:t),Ys(1:t),10, [.1,.1,.1], 'filled'); % old positions
    line(Xs((start_time+1):(start_time+t)),Ys((start_time+1):(start_time+t)), 'Color', 'k', 'LineWidth', 1.5)
    if plot_spikes scatter(Xs(spk_t(spikes)), Ys(spk_t(spikes)), tick_size, [1,0,0], 'filled'); end % spikes
    scatter(Xs(start_time+t),Ys(start_time+t),100, [0,.5,1], 'filled'); % current position
    caption = sprintf('Virtual Animal Positions and Spikes; t = %.0f ms', start_time+t);
    title(caption, 'FontSize', 13);
    xlim([min_x+crop max_x-crop])    
    ylim([min_y+crop max_y-crop])
    hold off
    thisFrame = getframe(gcf);
    myMovie(ceil(t/20)) = thisFrame;	
end
%hold off

close(hFigure);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('./videos/spike_traj.avi'); % Create a VideoWriter object to write the video out to a new, different file.
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)

function [spk_t,spikes]=load_spk_times(use_hopper_data, hopper_run, ...
    spk_bin_size, sel_nrn, spikes, ...
    fdr_prefix, local_run, curr_dir)

    if use_hopper_data==1
        file_path="/mnt/hopper_scratch/gc_sim/"+fdr_prefix+hopper_run+"/results/spk_MEC_LII_Stellate.dat";                
    else
        file_path = strcat(curr_dir,"/../results/spk_MEC_LII_Stellate.dat");
        %disp(file_path);
    end
    spk_data = SpikeReader(file_path, false, 'silent');
    spikes = spk_data.readSpikes(spk_bin_size);
    spk_t=find(spikes(:,sel_nrn)~=0);
    spk_t=spk_t*spk_bin_size;
end