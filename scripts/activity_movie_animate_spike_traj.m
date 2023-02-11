% reference https://www.mathworks.com/help/matlab/ref/animatedline.html#:~:text=Create%20an%20animation%20by%20adding,loop%20using%20the%20addpoints%20function.&text=an%20%3D%20animatedline(%20x%20%2C%20y%20)%20creates%20an%20animated%20line,x%20%2C%20y%20%2C%20and%20z%20.

close all;

% run options
use_hopper_data = 0;
local_run=1;
hopper_run = 3;
plot_spikes = 1; 
spk_bin_size = 10; % spike reader bin size. Note: small bin sizes may take long processing with large spike sets. 40min sim with bin size 1 can take 10min to create plot.
% select neuron to plot
sel_nrn=348;%110;%210;%262;%454;%454;%453;%455;%591;%629;%547;%629;%494;%290;%393;%243;%358;%338;%210;%290;%497;%860;%810;%300;%1250;%410;%820;%516;%1228;%690;
spikes=[];
fdr_prefix="gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
restrict_time = 300000; % 0 for no restriction or input time value for restriction
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
    %{
    if use_hopper
        hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/spikes_recorded.csv']);
        spk_t = readmatrix(hopper_path); 
    else
        if laptop_data == 0
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/spikes/spikes_recorded.csv');
        else
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/spikes_recorded.csv');
        end
    end
    %}
    spk_x = []; spk_y = [];
    [spk_t,spikes]=load_spk_times(use_hopper_data, hopper_run, ...
    spk_bin_size, sel_nrn, spikes, ...
    fdr_prefix, local_run, curr_dir);
end

time = restrict_time;
if restrict_time == 0
    time = length(Xs);
end

% set plot axes sizes
min_x = min(Xs(1:time));
max_x = max(Xs(1:time));
min_y = min(Ys(1:time));
max_y = max(Ys(1:time));
if min_x > 0 min_x = 0; end
if max_x < 30 max_x = 30; end
if min_y > 0 min_y = 0; end
if max_y < 30 max_y = 30; end
if max_x > max_y max_y = max_x; else max_x = max_y; end % make square

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

%{
h = animatedline();
%hold on
for t = 1:time
    hold on
    if mod(t-1,20) == 0
        addpoints(h,Xs(t),Ys(t));
        drawnow
    end
    if isempty(find(spk_t==t)) == 0
        scatter(Xs(t), Ys(t), [], [1,0,0], 'filled');
        drawnow
    end
    caption = sprintf('t = %.0f ms', t);
    title(caption, 'FontSize', 15);
    hold off
    thisFrame = getframe(gcf);
    myMovie(t) = thisFrame;	
end
%hold off
%}



%axes('position',[0 0 1 1]);
%plot1 = scatter(Ys(1:time),Xs(1:time),30,'.');

for t = 1:timestep:time
    clf(hFigure)
	hold on
    if plot_spikes spikes = find(spk_t < t); end
    %scatter(Xs(1:t),Ys(1:t),10, [.1,.1,.1], 'filled'); % old positions
    line(Xs(1:t),Ys(1:t), 'Color', 'k', 'LineWidth', 1.5)
    if plot_spikes scatter(Xs(spk_t(spikes)), Ys(spk_t(spikes)), 100, [1,0,0], 'filled'); end % spikes
    scatter(Xs(t),Ys(t),100, [0,.5,1], 'filled'); % current position
    caption = sprintf('Virtual Animal Positions and Spikes; t = %.0f ms', t);
    title(caption, 'FontSize', 13);
    %xlim([min_x max_x])    
    %ylim([min_y max_y])
    xlim([min_x max_x])    
    ylim([min_y max_y])
    hold off
    thisFrame = getframe(gcf);
    myMovie(ceil(t/20)) = thisFrame;	
end

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