% create high-resolution trajectory and firing plot

% run parameters
angles_speeds = 0; % load angles and speeds or x,y position coordinates
use_hopper = 1;
hopper_run = 3;
restrict_time = 0;%725000/20;%5000; % 0 for no restriction; in 20ms bins
timestep = 20;
orig_xy = 1; % use orig x,y animal positions with no wrapping around or carlsim x,y that wraps around a taurus
plot_spikes = 1;
laptop_data = 0;

pi=3.1415926535897932384626433832795028841971;
lines = [];

% load trajectory path
Xs = []; Ys = []; spk_x = []; spk_y = [];
if angles_speeds
    animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_angles.csv');
    animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_speeds.csv');
    %animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_angles.csv');
    %animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_speeds.csv');
else
    if orig_xy == 0
        if laptop_data == 0
            Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_x.csv');
            Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_y.csv');
        else
            Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_x.csv');
            Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_y.csv');
        end
    else
        %Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_x.csv');
        %Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_y.csv');
        load /home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/191108_S1_lightVSdarkness_cells11and12_scaleddown_Xs_40min.mat;
        load /home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/191108_S1_lightVSdarkness_cells11and12_scaleddown_Ys_40min.mat;
    end
end

% load spike times
if plot_spikes
    if use_hopper
        %{
        hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/highres_trajx.csv']);
        spk_x = readmatrix(hopper_path);    
        hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/highres_trajy.csv']);
        spk_y = readmatrix(hopper_path); 
        %}
        hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/highres_trajt.csv']);
        spk_t = readmatrix(hopper_path); 
    else
        %spk_x = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajx.csv');
        %spk_y = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajy.csv');
        if laptop_data == 0
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_trajt.csv');
        else
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_trajt.csv');
        end
    end
end

if angles_speeds
    x = 0; y = 0;
    %x = pos(1,1); % use pos from reformatted positions file used in moves_analysis.m
    %y = pos(2,1);
    for i=1:length(animal_speeds)
	    t=i*timestep; % in ms
	    a=animal_angles(i);
	    s=animal_speeds(i);
	    a=a/360*pi*2;
        x=cos(a)*s+x;
	    y=sin(a)*s+y;
	    %fprintf("%f %f\n",x2,y2);
	    Xs=[Xs;x];
	    Ys=[Ys;y];
        if mod(i,10000)==0
            fprintf("i:%d\n",i);
        end
    end
end

if restrict_time ~= 0
    x = Xs(1:floor(restrict_time/timestep));
    y = Ys(1:floor(restrict_time/timestep));
else
    x = Xs;
    y = Ys;
end

if plot_spikes
    for i=1:length(spk_t)
        if restrict_time == 0 
            disp(i)
            spk_x=[spk_x,x(floor(spk_t(i)/timestep))];
	        spk_y=[spk_y,y(floor(spk_t(i)/timestep))];
        elseif spk_t(i) < restrict_time
	        spk_x=[spk_x,x(floor(spk_t(i)/timestep))];
	        spk_y=[spk_y,y(floor(spk_t(i)/timestep))];
            %spk_x=[spk_x,x(spk_t(i))];
	        %spk_y=[spk_y,y(spk_t(i))];
        end
    end
end

% plot
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts'
plot_trajectory_custom
cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/'