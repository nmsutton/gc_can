%
% Create autocorrelation plot
%

addpath /comp_neuro/Software/Github/CMBHOME_github/
use_carlsim = 1;
%load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT#22_cell1.mat');
%load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/GCaMP6fChAT10_gridCell_mergedSessions.mat');
load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/191108_S1_lightVSdarkness_cells11and12.mat');
cell_selection=root.cel;
if use_carlsim == 0
    load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT#22_cell1.mat');
    plot_rate_map_ac(root, cell_selection, rate_map, spk_x, spk_y);
else
    spk_x = [];
    spk_y = [];
    plot_rate_map_ac(root, cell_selection, heat_map, spk_x, spk_y);
end
colormap default
%caxis([-0.46 1.05]);
%caxis([1 10]);
