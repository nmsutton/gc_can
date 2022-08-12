% reference https://www.mathworks.com/help/matlab/ref/animatedline.html#:~:text=Create%20an%20animation%20by%20adding,loop%20using%20the%20addpoints%20function.&text=an%20%3D%20animatedline(%20x%20%2C%20y%20)%20creates%20an%20animated%20line,x%20%2C%20y%20%2C%20and%20z%20.

% run options
use_hopper = 1;
hopper_run = 7;
laptop_data = 0;
use_unwrapped_data = 1;
plot_spikes = 1; 
restrict_time = 100; % 0 for no restriction or input time value for restriction
hFigure = figure;

% load traj data
if laptop_data == 0
    if use_unwrapped_data == 0
        Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_x.csv');
        Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_y.csv');
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
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');
        else
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/spikes_recorded.csv');
        end
    end
end

time = restrict_time;
if restrict_time == 0
    time = length(Xs);
end

% video
numberOfFrames = (time);
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

close(hFigure);
myMovie(1) = []; % remove first frame causing issues due to wrong size
v = VideoWriter('./videos/spike_traj.avi'); % Create a VideoWriter object to write the video out to a new, different file.
open(v)
writeVideo(v,myMovie) % Write the movie object to a new video file.
close(v)

%{
figure;
hold on
%colormap(customMap);
axes('position',[0 0 1 1]);
plot1 = scatter(Ys(1),Xs(1),30,'.');
%xlim([lonMin lonMax]);
%ylim([latMin latMax]);
%set(gca,'Color','none');
%set(gca,'CLim',[0, 1E-4]);

for k = 2:10000 %length(Xs)

    % pause 2/10 second: 
    %pause(0.2)
    if isempty(find(spk_t==t)) == 0
        %scatter(Xs(i), Ys(i), 300, [1,0,0], 'filled');
        scatter(Xs(i), Ys(i), 300, [1,0,0]);
    else
        %plot1.XData = Xs(1:k); 
        %plot1.YData = Ys(1:k); 
    end
    %drawnow
end
hold off
%}

%{
% clear points
clearpoints(h)
drawnow
%}
