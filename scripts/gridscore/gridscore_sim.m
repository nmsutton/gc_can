addpath /comp_neuro/Software/Github/CMBHOME_github/
run('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/high_res_traj/high_res_traj.m');
%run('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/activity_image_phys_spc_smooth.m');
m = []; % empty matrix
[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
fprintf("HDgridScore:%f; gridness3Score:%f\n",HDgridScore,gridness3Score);