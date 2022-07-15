% create high-resolution trajectory and firing plot

pi=3.1415926535897932384626433832795028841971;
lines = [];

% load trajectory path
animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_angles.csv');
animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_speeds.csv');
Xs = []; Ys = []; spk_x = []; spk_y = [];
timestep = 20;

% load spike times
carlsim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');

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

	% search timestep for spike
	for j=1:timestep
		spike_detect = find(carlsim_spikes(:,1)==(t+j));
		if spike_detect
			spk_x=[spk_x; x];
			spk_y=[spk_y; y];
		end
	end
end

x = Xs;
y = Ys;

% plot
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts'
plot_trajectory_custom
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/'