% https://www.mathworks.com/matlabcentral/answers/456241-how-to-apply-command-line-arguments-in-matlab
function exitcode = gridscore_sim(p1,p2)
	run_on_hopper=1; % run from hopper's system 
	hopper_run=8;
	if run_on_hopper
		addpath /home/nsutton2/git/CMBHOME_github/ 
		%run("/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/gc_can_"+hopper_run+"/scripts/high_res_traj/high_res_traj.m");	
		run("/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/param_explore_tm/scripts/high_res_traj/high_res_traj.m");	
	else
		addpath /comp_neuro/Software/Github/CMBHOME_github/
		run('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/high_res_traj.m');
	end
	m = []; % empty matrix
	[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
	gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
	c = clock;
	hr = mod(c(4),12);
	output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
	fprintf(gridness_file,"%s,%s,%s,%f,%f\n",output_time,p1,p2,HDgridScore,gridness3Score);
	fclose(gridness_file);
	exitcode = 0;
end