%
% Create autocorrelation plot
%

addpath /comp_neuro/Software/Github/CMBHOME_github/
use_carlsim = 1;
load filenames;
% small:
%191108_S1_lightVSdarkness_cells11and12.mat
%file_number=15;
% medium
%merged_sessions_ArchTChAT#22_cell1.mat
%file_number=23;
% large
%GCaMP6fChAT10_gridCell_mergedSessions.mat
file_number=17;
% other
%file_number=2;

% try to load either desktop or laptop files
% desktop data
try 
    load(filenames(file_number));
catch
end
% laptop data
try
    load("/comp_neuro/sim_project/holger_data/ChATControl_3/170224_S1_LS.mat");
catch
end
load tetrodes;
load cells;
%cell_selection=root.cel;
cell_selection=[tetrodes(file_number),cells(file_number)];
if use_carlsim == 0
    load('/media/nmsutton/StorageDrive7/comp_neuro/holger_data/merged_sessions_ArchTChAT#22_cell1.mat');
    auto_corr_rm=plot_rate_map_ac(root, cell_selection, rate_map, spk_x, spk_y);
else
    spk_x = [];
    spk_y = [];
    auto_corr_rm=plot_rate_map_ac(root, cell_selection, heat_map, spk_x, spk_y);
end
colormap default
%caxis([-0.46 1.05]);
%caxis([1 10]);
