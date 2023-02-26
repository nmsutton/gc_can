% generate gridscore from rate map plot
% note: set use_hopper and hopper_run in high_res_traj.m if wanting to use hopper data
% while running locally.
% reference: https://www.mathworks.com/matlabcentral/answers/456241-how-to-apply-command-line-arguments-in-matlab

% run_on_hopper: run from hopper's system 
% use_hopper_data: access hopper data locally
% fdr_prefix: folder name prefix
% hopper_run: hopper run number

if preloaded_spk_reader==0 spikes=[]; end

if run_on_hopper==1
	addpath /home/nsutton2/git/CMBHOME_github/ 
else
	addpath /comp_neuro/Software/Github/CMBHOME_github/
end
PWD=pwd;
cd ../high_res_traj
high_res_traj
cd(PWD);

m = []; % empty matrix
[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
fprintf("HDgridScore: %f; Gridness3Score: %f\n",HDgridScore,gridness3Score);
if save_gridscore_file==1
	gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
	c = clock;
	hr = mod(c(4),12);
	output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
    if isnan(HDgridScore) HDgridScore=0; end
    fprintf(gridness_file,"%s,a_%f,b_%f,%f,%f\n",output_time,p1,p2,HDgridScore,gridness3Score);
	fclose(gridness_file);
end
exitcode = 0;