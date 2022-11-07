% generate gridscore from rate map plot
% note: set use_hopper and hopper_run in high_res_traj.m if wanting to use hopper data
% while running locally.
% reference: https://www.mathworks.com/matlabcentral/answers/456241-how-to-apply-command-line-arguments-in-matlab
function exitcode = gridscore_sim(p1,p2,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run)
	%run_on_hopper=0; % run from hopper's system 
	%use_hopper_data=0; % access hopper data locally
	%fdr_prefix="param_explore_tm_"; % folder name prefix
	%hopper_run=1; % set this in high_res_traj if using hopper data locally

	if run_on_hopper
		addpath /home/nsutton2/git/CMBHOME_github/ 
		PWD=pwd;
		cd "/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/"+fdr_prefix+hopper_run+"/scripts/high_res_traj/";
		high_res_traj run_on_hopper use_hopper_data fdr_prefix hopper_run
		cd PWD;
	elseif use_hopper_data
		addpath /comp_neuro/Software/Github/CMBHOME_github/
		PWD=pwd;
		cd "/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/"+fdr_prefix+hopper_run+"/scripts/high_res_traj/";
		high_res_traj run_on_hopper use_hopper_data fdr_prefix hopper_run
		cd PWD;
	else
		addpath /comp_neuro/Software/Github/CMBHOME_github/
		PWD=pwd;
		cd "/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/";
		high_res_traj run_on_hopper use_hopper_data fdr_prefix hopper_run
		cd PWD;
	end

	m = []; % empty matrix
	[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
	fprintf("%f,%f\n",HDgridScore,gridness3Score);
	gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
	c = clock;
	hr = mod(c(4),12);
	output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
	fprintf(gridness_file,"%s,%s,%s,%f,%f\n",output_time,p1,p2,HDgridScore,gridness3Score);
	fclose(gridness_file);
	exitcode = 0;
end