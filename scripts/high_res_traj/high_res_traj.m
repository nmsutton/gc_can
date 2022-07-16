% create high-resolution trajectory and firing plot

pi=3.1415926535897932384626433832795028841971;
lines = [];

% load trajectory path
animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_angles.csv');
animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_speeds.csv');
Xs = []; Ys = []; spk_x = []; spk_y = [];
timestep = 20;

% load spike times
use_hopper = 0;
hopper_run = 3;
if use_hopper
    hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/highres_trajx.csv']);
    spk_x = readmatrix(hopper_path);    
    hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/highres_trajy.csv']);
    spk_y = readmatrix(hopper_path); 
else
    %spk_x = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajx.csv');
    %spk_y = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajy.csv');
    spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajt.csv');
end

%x = 0; y = 0;
x = pos(1,1); % use pos from reformatted positions file used in moves_analysis.m
y = pos(2,1);
for i=1:length(animal_speeds)
%for i=1:5000
	t=i*timestep; % in ms
	a=animal_angles(i);
	s=animal_speeds(i);
	a=a/360 * pi*2;
    x=cos(a)*s+x;
	y=sin(a)*s+y;
	%fprintf("%f %f\n",x2,y2);
	Xs=[Xs;x];
	Ys=[Ys;y];
end

x = Xs(1:5000);
y = Ys(1:5000);

for i=1:length(spk_t)
	spk_x=[spk_x,x(i)];
	spk_y=[spk_y,y(i)];
end

% plot
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts'
plot_trajectory_custom
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/'