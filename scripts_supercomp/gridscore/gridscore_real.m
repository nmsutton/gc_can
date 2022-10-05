addpath /comp_neuro/Software/Github/CMBHOME_github/
load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191101_S1_lightVSdarkness_cell9');
root.cel=[2 12];
[spk_x, spk_y] = CMBHOME.Utils.ContinuizeEpochs(root.cel_x, root.cel_y);
rate_map_grid_score_custom
[HDgridScore,gridness3Score]=get_HDGridScore(root,root.cel,root.epoch);
fprintf("HDgridScore:%f; gridness3Score:%f\n",HDgridScore,gridness3Score);