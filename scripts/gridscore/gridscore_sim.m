% generate gridscore from rate map plot
% note: set use_supcomp and supcomp_run in high_res_traj.m if wanting to use supercomputer data
% while running locally.
% reference: https://www.mathworks.com/matlabcentral/answers/456241-how-to-apply-command-line-arguments-in-matlab

% run_on_supcomp: run from supercomputer's system 
% use1_supcomp_data: access supercomputer data on a local computer
% fdr_prefix: folder name prefix
% supcomp_run: supercomputer run number

if preloaded_spk_reader==0 spikes=[]; end

if run_on_supcomp==1
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
avg_firing_rate=mean(mean(heat_map));
peak_firing_rate=max(max(heat_map));
if exist('create_ac','var')
    if str2num([string(create_ac)])==1 
        PWD=pwd;
        cd ..
        activity_image_autocorr;
        cd(PWD);
    end
end
if exist('save_field_size','var') && exist('save_field_spacing','var') && exist('save_field_rotation','var')
    if str2num([string(save_field_size)])==1 || str2num([string(save_field_spacing)])==1 ...
	    || str2num([string(save_field_rotation)])==1
	    PWD=pwd;
	    cd ../../../gridcell_metrics/src
	    gridcell_metrics;
        cd(PWD);
    end	
end
fprintf("HDgridScore: %f; Gridness3Score: %f\n",HDgridScore,gridness3Score);
fprintf("Mean firing rate: %f; Peak firing rate: %f\n",avg_firing_rate,max(max(heat_map)));
if str2num([string(save_gridscore_file)])==1
	gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
	c = clock;
	hr = mod(c(4),12);
	output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
    if isnan(HDgridScore) HDgridScore=0; end
    fprintf(gridness_file,"%s,a_%f,b_%f,%f,%f\n",output_time,p1,p2,HDgridScore,gridness3Score);
	fclose(gridness_file);
end
if str2num([string(save_firingrate_file)])==1
	firingrate_file = fopen('../firing_rate_records.txt','at'); % append file
	fprintf(firingrate_file,"%f\n",avg_firing_rate);
	fclose(firingrate_file);
end
if str2num([string(save_firingpeak_file)])==1
	firingpeak_file = fopen('../firing_peak_records.txt','at'); % append file
	fprintf(firingpeak_file,"%f\n",peak_firing_rate);
	fclose(firingpeak_file);
end
exitcode = 0;