%%
%% Script to load spike firing times for a cell
%% c_ts: firing times, root.cel_x{1,1}: spike x coordinates,
%% root.cel_y{1,1}: spike y coordinates
%% reference: https://github.com/hasselmonians/CMBHOME/wiki/Tutorial-2:-Apply-an-epoch-and-get-theta-signal
%%

function [root c_ts] = load_spike_times()
	addpath /comp_neuro/Software/Github/CMBHOME_github/
	load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/180815_S1_S2_lightVSdarkness_merged.mat');
	root.cel = [2,5]; % select cell of interest
	c_ts = CMBHOME.Utils.ContinuizeEpochs(root.cel_ts);
end