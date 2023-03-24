% run from local pc and create gridscore, trajectory plot, and rate map plot

function heat_map = gridscore_sim_function(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file)
	% general run options
	% run_on_hopper: run from hopper's system 
	% use_hopper_data: access hopper data locally
	% fdr_prefix: folder name prefix
	% hopper_run: hopper run number
	p1=str2double([string(p1)]); % param explore parameter for file naming
	p2=str2double([string(p2)]); % param explore parameter for file naming
	local_run=str2num([string(local_run)]); % local run number
	run_on_hopper=str2num([string(run_on_hopper)]); % supercomputer run options: run from hopper's system
	use_hopper_data=str2num([string(use_hopper_data)]); % access hopper data locally
	hopper_run=str2num([string(hopper_run)]); % hopper run number
	save_gridscore_file=str2num([string(save_gridscore_file)]); % save gridscore to file

	fdr_prefix="gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
	restrict_time=0; % limit time plotted. 0 for no restriction; in 20ms bins
	smaller_spk_ticks=1; % choose trajectory plot tick size. 2 for extra small.
	preloaded_spk_reader=0; % save time of loading spike reader by using prior loaded one
	plot_spikes = 1; % turn off spike plotting when only movement trajectory is desired to be plotted
	sel_nrn=1577; % select neuron to plot

	gridscore_sim
	exitcode = 0;
end