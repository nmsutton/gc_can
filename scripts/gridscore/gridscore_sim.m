addpath /comp_neuro/Software/Github/CMBHOME_github/
run('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/high_res_traj.m');
%run('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/activity_image_phys_spc_smooth.m');
m = []; % empty matrix
[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
c = clock;
hr = mod(c(4),12);
output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
fprintf(gridness_file,"%s,%f,%f\n",output_time,HDgridScore,gridness3Score);
fclose(gridness_file);