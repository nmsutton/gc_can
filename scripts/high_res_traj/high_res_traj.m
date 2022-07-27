% create high-resolution trajectory and firing plot

% run parameters
angles_speeds = 0; % load angles and speeds or x,y position coordinates
preloaded_XsYs = 0; % use prior loaded Ys and Xs instead of reading them from files
output_XsYs_file = 0;
output_spikes_file = 1; % output file that can be used in rate map plot
create_plot = 1;
use_hopper = 0;
hopper_run = 3;
restrict_time = 0;%2400000;%725000/20;%5000; % 0 for no restriction; in 20ms bins
timestep = 20;
orig_xy = 0; % use orig x,y animal positions with no wrapping around or carlsim x,y that wraps around a taurus
plot_spikes = 1;
laptop_data = 1;
use_unwrapped_data = 1;

pi=3.1415926535897932384626433832795028841971;
lines = [];
if output_spikes_file
    recspk_file = fopen('highres_spikes.csv','w');
end
if output_XsYs_file
    Xs_file = fopen('anim_trajx.csv','w');
    Ys_file = fopen('anim_trajy.csv','w');
end

% load trajectory path
if preloaded_XsYs == 0 Xs = []; Ys = []; end
spk_x = []; spk_y = [];
if angles_speeds
    if preloaded_XsYs ~= 1
        %animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_angles.csv');
        %animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/animal_speeds.csv');
        %animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_angles.csv');
        %animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/test_data_speeds.csv');
        animal_angles = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/anim_angles_limited.csv');
        animal_speeds = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/anim_speeds_limited.csv');
    end
else
    if orig_xy == 0
        if laptop_data == 0
            if use_unwrapped_data == 0
                Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_x.csv');
                Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/highres_pos_y.csv');
            else
                Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/Xs_unwrapped.csv');
                Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/Ys_unwrapped.csv');
            end
        else
            if use_unwrapped_data == 0
                Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_x.csv');
                Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/highres_pos_y.csv');
            else
                Xs = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/Xs_unwrapped.csv');
                Ys = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/moves_analysis/src/Ys_unwrapped.csv');            
            end
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
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');
        else
            spk_t = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_ltop/output/spikes/spikes_recorded.csv');
        end
    end
end
%{
if angles_speeds == 1 && preloaded_XsYs ~= 1
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
            fprintf("i:%d %.1f%% completed\n",i,i/length(animal_speeds)*100);
        end
    end
end
%}

if angles_speeds == 1 && preloaded_XsYs ~= 1
    x = 0; y = 0;
    %x = pos(1,1); % use pos from reformatted positions file used in moves_analysis.m
    %y = pos(2,1);
    for i=1:length(animal_speeds)
	    t=i*timestep; % in ms
	    a=animal_angles(i);
	    s=animal_speeds(i);
	    a=a/360*pi*2;
        [hor,ver]=hor_ver(a, s);
        x=x+hor;
	    y=y+ver;
	    %fprintf("%f %f\n",x2,y2);
	    Xs=[Xs;x];
	    Ys=[Ys;y];
        if mod(i,10000)==0
            fprintf("i:%d %.1f%% completed\n",i,i/length(animal_speeds)*100);
        end
    end
end

if restrict_time ~= 0
    if orig_xy
        x = Xs(1:floor(restrict_time/timestep));
        y = Ys(1:floor(restrict_time/timestep));
    else
        if angles_speeds
            x = Xs(1:floor(restrict_time/timestep));
            y = Ys(1:floor(restrict_time/timestep));            
        else
            x = Xs(1:restrict_time);
            y = Ys(1:restrict_time);
        end
    end
else
    x = Xs;
    y = Ys;
end

if plot_spikes || output_spikes_file
    for i=1:length(spk_t)
        if restrict_time == 0 
            if orig_xy || angles_speeds
                spk_x=[spk_x,x(floor(spk_t(i)/timestep))];
	            spk_y=[spk_y,y(floor(spk_t(i)/timestep))];
            else 
                spk_x=[spk_x,x(spk_t(i))];
	            spk_y=[spk_y,y(spk_t(i))];
            end
            if output_spikes_file
                fprintf(recspk_file,"%f,%f,%f\n",spk_t(i),spk_x(i),spk_y(i));
            end
        elseif spk_t(i) < restrict_time
            if orig_xy || angles_speeds
	            spk_x=[spk_x,x(floor(spk_t(i)/timestep))];
	            spk_y=[spk_y,y(floor(spk_t(i)/timestep))];
            else
                spk_x=[spk_x,x(spk_t(i))];
	            spk_y=[spk_y,y(spk_t(i))];
            end
            if output_spikes_file
                fprintf(recspk_file,"%f,%f,%f\n",spk_t(i),spk_x(i),spk_y(i));
            end
        end
    end
end

if output_XsYs_file
    for i=1:length(Xs)
        fprintf(Xs_file,'%.6f\n',Xs(i));
        fprintf(Ys_file,'%.6f\n',Ys(i));
        if mod(i,(length(Xs)/10))==0
            fprintf("%.6f%% completed\n",i/length(Xs));
        end 
    end
    fclose(Xs_file);
    fclose(Ys_file);   
end
if output_spikes_file
    fclose(recspk_file);
end

% plot
if create_plot
    cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts'
    plot_trajectory_custom
    cd '/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/'
end

function [hor,ver]=hor_ver(angle, speed)
    h = speed;
    if (angle < (pi/2)) 
		hor = sin(angle) * h;
		ver = sqrt(h^2-hor^2);
    elseif (angle >= (pi/2) && angle < pi) 
		hor = cos(angle-(pi/2)) * h;
		ver = sqrt(h^2-hor^2) * -1;
    elseif (angle >= pi && angle < (pi*1.5)) 
		hor = cos((pi*1.5)-angle) * h * -1;
		ver = sqrt(h^2-hor^2) * -1;
    elseif (angle >= (pi*1.5) && angle <= (pi*2)) 
		hor = cos(angle-(pi*1.5)) * h * -1;
		ver = sqrt(h^2-hor^2);
    end
end