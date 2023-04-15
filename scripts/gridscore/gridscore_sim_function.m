% run from local pc and create gridscore, trajectory plot, and rate map plot

function [heat_map,spikes,spk_data] = gridscore_sim_function(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file,preloaded_spk_reader,sel_nrn,save_plot,save_traj_plot,save_firingrate_file,create_plot,spikes,spk_data)
	% general run options
	% run_on_hopper: run from hopper's system 
	% use_hopper_data: access hopper data locally
	% fdr_prefix: folder name prefix. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
	% hopper_run: hopper run number
	p1=str2double([string(p1)]); % param explore parameter for file naming
	p2=str2double([string(p2)]); % param explore parameter for file naming
	local_run=str2num([string(local_run)]); % local run number
	run_on_hopper=str2num([string(run_on_hopper)]); % supercomputer run options: run from hopper's system
	use_hopper_data=str2num([string(use_hopper_data)]); % access hopper data locally
	hopper_run=str2num([string(hopper_run)]); % hopper run number
	save_gridscore_file=str2num([string(save_gridscore_file)]); % save gridscore to file
	preloaded_spk_reader=str2num([string(preloaded_spk_reader)]); % save time of loading spike reader by using prior loaded one
 	sel_nrn=str2num([string(sel_nrn)]); % select neuron to plot
 	save_plot==str2num([string(save_plot)]);
 	save_traj_plot==str2num([string(save_traj_plot)]);
 	save_firingrate_file==str2num([string(save_firingrate_file)]);

	restrict_time=0; % limit time plotted. 0 for no restriction; in 20ms bins
	smaller_spk_ticks=1; % choose trajectory plot tick size. 2 for extra small.
	plot_spikes = 1; % turn off spike plotting when only movement trajectory is desired to be plotted
	if ~exist('run_real_recordings','var') run_real_recordings=0; end % run parameters for real recordings
	if ~exist('plot_subsect','var') plot_subsect=1; end % plot only subsection of total data. this is set by the plot_size variable.
	if ~exist('grid_size','var') grid_size=40; end % sqrt of grid size
	if ~exist('plot_size','var') plot_size=31; end % sqrt of plot size

	gridscore_sim
	exitcode = 0;
end