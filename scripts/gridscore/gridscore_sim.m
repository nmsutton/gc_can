% generate gridscore from rate map plot
% note: set use_hopper and hopper_run in high_res_traj.m if wanting to use hopper data
% while running locally.
% reference: https://www.mathworks.com/matlabcentral/answers/456241-how-to-apply-command-line-arguments-in-matlab
function exitcode = gridscore_sim(p1,p2,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file)
	% run_on_hopper: run from hopper's system 
	% use_hopper_data: access hopper data locally
	% fdr_prefix: folder name prefix
	% hopper_run: hopper run number
	%run_on_hopper=str2num([run_on_hopper]);
	%use_hopper_data=str2num([use_hopper_data]);
	%hopper_run=str2num([hopper_run]);
	%save_gridscore_file=str2num([save_gridscore_file]);

	if run_on_hopper==1
		addpath /home/nsutton2/git/CMBHOME_github/ 
		PWD=pwd;
		fldr="/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/"+fdr_prefix+hopper_run+"/scripts/high_res_traj/";
		cd(fldr);
		heat_map=high_res_traj(run_on_hopper,use_hopper_data,fdr_prefix,hopper_run);
		cd(PWD);
	elseif use_hopper_data==1
		addpath /comp_neuro/Software/Github/CMBHOME_github/
		PWD=pwd;
		fldr="/home/nsutton2/git/CARLsim4_dgx_hc_09_18_21/projects/"+fdr_prefix+hopper_run+"/scripts/high_res_traj/";
		cd(fldr);		
		heat_map=high_res_traj(run_on_hopper,use_hopper_data,fdr_prefix,hopper_run);
		cd(PWD);
	else
		addpath /comp_neuro/Software/Github/CMBHOME_github/
		PWD=pwd;
		fldr="/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/scripts/high_res_traj/";
		cd(fldr);
		heat_map=high_res_traj(run_on_hopper,use_hopper_data,fdr_prefix,hopper_run);
		cd(PWD);
	end

	m = []; % empty matrix
	[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
	fprintf("HDgridScore: %f; Gridness3Score: %f\n",HDgridScore,gridness3Score);
	if save_gridscore_file==1
		gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
		c = clock;
		hr = mod(c(4),12);
		output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
		fprintf(gridness_file,"%s,%s,%s,%f,%f\n",output_time,p1,p2,HDgridScore,gridness3Score);
		fclose(gridness_file);
	end
	exitcode = 0;
end