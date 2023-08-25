% this software reports the percentage of speeds below a given value

speed_test=18; % speed to test values below
num_files=10; % number of input files
p_below=[]; % percentages below speed_test
hrs=[]; % number of hours tested
timestep=20; % millisecond sampling rate
ms_in_s=1000; % milliseconds in a second
sec_in_m=60; % seconds in a minute
min_in_h=60; % minutes in an hour

for i=1:num_files
    file=get_file(i);
    speeds=readmatrix(file);
    perc=length(find(speeds<=speed_test))/length(speeds);
    p_below=[p_below; perc];
    hrs=[hrs; length(speeds)*timestep];
end

fprintf("Percentage of speeds below %.1f mps: %.4f%%.\n", speed_test, mean(p_below));
fprintf("Experiment time evaluated: %.1f hrs.\n",((sum(hrs)/ms_in_s)/sec_in_m)/min_in_h);

function file=get_file(i)
    if i == 1; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/sml_fields_low_fr_070823/anim_speeds.csv'; end
    if i == 2; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/sml_fields_med_fr_011023/anim_speeds.csv'; end
    if i == 3; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/sml_fields_high_fr_070923/anim_speeds.csv'; end
    if i == 4; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/med_fields_low_fr_071023/anim_speeds.csv'; end
    if i == 5; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/med_fields_med_fr_010223/anim_speeds.csv'; end
    if i == 6; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/med_fields_high_fr_071023/anim_speeds.csv'; end
    if i == 7; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/large_fields_low_fr_071023/anim_speeds.csv'; end
    if i == 8; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/large_fields_med_fr_011023/anim_speeds.csv'; end
    if i == 9; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/animal_data_converted/large_fields_med_fr_2_071223/anim_speeds.csv'; end
    if i == 10; file='/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/projects_40x40/med_fields_alt/gc_can_1_high_score/data/anim_speeds.csv'; end
end