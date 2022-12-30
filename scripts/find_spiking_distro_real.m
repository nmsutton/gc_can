clear all;
addpath /comp_neuro/Software/Github/CMBHOME_github/
[filename,f_length]=get_filename(1);
spk_hz_group = [];

for i=1:f_length
	[filename,f_length]=get_filename(i);
	cell_selection=get_cell_selection(i);
	spk_hz=find_hz(filename,cell_selection);
    spk_hz_group=[spk_hz_group;spk_hz];
    if i==1 fprintf("Processed:\n"); end
	fprintf("File:%d/%d Hz:%f\n",i,f_length,spk_hz);
end

% plot
hist(spk_hz_group);
axis('tight')
xlabel('Spiking Frequency of Neurons (Hz)') 
ylabel('Neuron Count')
caption = sprintf('Spiking Frequencies of %d Real Neurons',f_length);
title(caption, 'FontSize', 15);

function spk_hz=find_hz(filename,cell_selection);
	y_offset = 660;
    rec_seconds = 0;
	limit_time = false; % choose to limit time of data extracted
	total_time = 2400000; % max time of recordings to save in ms
	time_step = 20; % recording timestep
	timevars = [limit_time, total_time, time_step];

	% load data
    clear lightON; % clear old epoch data
	load(filename);
    root.cel = cell_selection; % select cell of interest
    if exist('lightON')
        root.epoch=lightON; % use lightON if it exists
    end
	CMBHOME.Utils.ContinuizeEpochs(root.ts); 
    for i=1:size(root.epoch,1)
	    rec_seconds = rec_seconds + (root.epoch(i,2) - root.epoch(i,1));
    end

	% retrieve spikes
	cd /home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/holger_data/nate_scripts/for_jeffrey
	spikes=retrieve_spikes(root, timevars, y_offset, cell_selection);
	cd /home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/scripts

	spk_count = size(spikes(1,:),2);
	spk_hz = spk_count/rec_seconds;
end

function [filename,f_length]=get_filename(i)
	full_list=0;
	if full_list
	% full list
	filenames=[ "/media/nmsutton/StorageDrive7/comp_neuro/holger_data/0823_S1_0824_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/180815_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/180815_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190805_S3_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190805_S3_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190807_S1_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190809_S1_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190812_S2_LightVSdarkness_72min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190812_S2_LightVSdarkness_72min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191101_S1_lightVSdarkness_cell9.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191103_S1_lightVSdarkness_cells13and14.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191105_S1_lightVSdarkness_cell15.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191108_S1_lightVSdarkness_cells11and12.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191108_S1_lightVSdarkness_cells11and12.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/GCaMP6fChAT10_gridCell_mergedSessions.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_ArchTChAT22_cell3.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_ArchTChAT22_cell4.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_cell8_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/Merged_sessions.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT22_cell2.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT#22_cell1.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_gridCells.mat"];
	else
	% reduced list
	filenames=[ "/media/nmsutton/StorageDrive7/comp_neuro/holger_data/0823_S1_0824_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/180815_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/180815_S1_S2_lightVSdarkness_merged.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190720_S2_lightVSdarkness.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190805_S3_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190805_S3_LightVSdarkness_42min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190812_S2_LightVSdarkness_72min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/190812_S2_LightVSdarkness_72min.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191101_S1_lightVSdarkness_cell9.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191103_S1_lightVSdarkness_cells13and14.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191105_S1_lightVSdarkness_cell15.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191108_S1_lightVSdarkness_cells11and12.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191108_S1_lightVSdarkness_cells11and12.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/GCaMP6fChAT10_gridCell_mergedSessions.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_ArchTChAT22_cell3.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_ArchTChAT22_cell4.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_session_cell8_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/Merged_sessions.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT22_cell2.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT#22_cell1.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat";
				"/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_cells5to7_ArchTChAT22.mat"];
	end

	filename=filenames(i);
    f_length=length(filenames);
end

function cell_selection=get_cell_selection(i)
	full_list=0;
	if full_list
	% full list
	tetrodes = [1;2;2;1;1;1;2;2;2;2;2;2;2;2;1;1;1;1;2;1;1;2;2;2;2;1;1;1;2];
	cells =    [3;2;5;2;6;7;7;4;9;7;5;4;5;12;9;3;9;15;1;1;1;1;1;1;1;1;2;3;1];
	else
	% reduced list
	tetrodes = [1;2;2;1;1;1;2;2;2;2;2;2;1;1;1;1;2;1;1;2;2;2;2;1;1;1];
	cells =    [3;2;5;2;6;7;7;4;9;4;5;12;9;3;9;15;1;1;1;1;1;1;1;1;2;3];
	end

	cell_selection = [tetrodes(i),cells(i)];
end