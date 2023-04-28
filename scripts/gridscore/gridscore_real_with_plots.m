% script to plot real animal data and get gridscore

% select data to use
load filenames;load tetrodes;load cells;
% file_number 15 = small, 23 = medium, 17 = large
file_number=15;%15;%23;

run_real_recordings=1; 
plot_subsect=1;
grid_size=33;
plot_size=31;
restrict_time=0;
keep_vars=1; % avoid clearing variables set here
extract_x_y_spk;
gridscore_sim_run_local;