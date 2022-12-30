% reference https://www.mathworks.com/help/matlab/ref/animatedline.html#:~:text=Create%20an%20animation%20by%20adding,loop%20using%20the%20addpoints%20function.&text=an%20%3D%20animatedline(%20x%20%2C%20y%20)%20creates%20an%20animated%20line,x%20%2C%20y%20%2C%20and%20z%20.

% run options
use_hopper = 1;
hopper_run = 3;
laptop_data = 0;
use_unwrapped_data = 1;
plot_spikes = 1; 
restrict_time = 300000; % 0 for no restriction or input time value for restriction
timestep=20;
hFigure = figure;

% load traj data
if laptop_data == 0
    if use_unwrapped_data == 0
        Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/spikes/highres_pos_x.csv');
        Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/spikes/highres_pos_y.csv');
    else
        Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/output/Xs_unwrapped.csv');
        Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/output/Ys_unwrapped.csv');
    end
else
    if use_unwrapped_data == 0
        Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_x.csv');
        Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_y.csv');
    else
        Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/output/Xs_unwrapped.csv');
        Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/output/Ys_unwrapped.csv');            
    end
end

% load spike times
if plot_spikes
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
