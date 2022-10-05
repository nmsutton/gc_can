run("/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/scripts/initOAT.m");
addpath /comp_neuro/Software/Github/CMBHOME_github/
import CMBHOME.Utils.*
spikes = [];
load("example_data/example_spk_t.mat")
load("example_data/example_spk_x.mat")
load("example_data/example_spk_y.mat")
load("example_data/example_Xs.mat")
load("example_data/example_Ys.mat")
recspk_file_path = 'highres_spikes.csv';
recspk_file = fopen(recspk_file_path,'w');
display_plot=0;
save_test_plot=1;
save_traj_plot=0;
grid_size=30;
shuffles=700;
binside = 3;
std_smooth_kernel = 3.333;
x = [1 grid_size]; % plot axis size
y = [1 grid_size]; % plot axis size
m = []; % empty matrix

for i=1:shuffles
	%[spk_x spk_y spk_t] = shuffle(spk_x, spk_y, spk_t);
	[spk_x spk_y] = shuffle3(spk_x, spk_y);
end

% plot
% create spikes file for plotting
for i=1:length(spk_t)
	fprintf(recspk_file,"%f,%f,%f\n",spk_t(i),spk_x(i),spk_y(i));
end

cd ../../high_res_traj
%plot_trajectory

carlsim_spikes = readmatrix(recspk_file_path);
spike_x = spk_y';%carlsim_spikes(1:end,3);
spike_y = spk_x';%carlsim_spikes(1:end,2);
heat_map = zeros(1,grid_size*grid_size);
xdim = linspace(0,grid_size-1,grid_size);%xdim * 30/360;
ydim2 = linspace(0,grid_size-1,grid_size);%ydim2 * 30/360;
heat_map = hist3([spike_x, spike_y], 'Edges', {xdim, ydim2});
for i=1:shuffles
	%heat_map = shuffle3(heat_map);
end
heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1

cd ..
%activity_image_phys_spc_smooth
cd gridscore/test_scores

% plot
if display_plot == 0 fig = figure('visible','off'); else fig = figure; end
imagesc(heat_map);
axis('tight')
xlabel('animal position on x axis') 
ylabel('animal position on y axis')
cb = colorbar;
ax = gca;
ax.YDir = 'normal'; % have y-axis 0 on bottom left
%caxis([0 25])
caption = sprintf('Physical space grid cell firing, total t = %.0f ms', 220000);
title(caption, 'FontSize', 11);
set(fig, 'units', 'inches', 'position', [0 50 5.31 4.444]);
if display_plot == 0 set(fig,'visible','on'); end
if save_test_plot
	c = clock;
	hr = mod(c(4),12);
	output_filename = sprintf("ratemap_%.0f-%.0f-%.0f_%.0f-%.0f-%.0f.png",hr,c(5),c(6),c(2),c(3),c(1));
	exportgraphics(gcf,output_filename,'Resolution',300)
end

% gridscore
cd ..
[HDgridScore,gridness3Score]=get_HDGridScore(m,m,m,heat_map);
fprintf("%f,%f\n",HDgridScore,gridness3Score);
gridness_file = fopen('../param_explore/output/gridness_score.txt','at'); % append file
c = clock;
hr = mod(c(4),12);
output_time = sprintf("%.0f-%.0f-%.0f_%.0f-%.0f-%.0f",hr,c(5),c(6),c(2),c(3),c(1));
fprintf(gridness_file,"%s,%f,%f\n",output_time,HDgridScore,gridness3Score);
fclose(gridness_file);
cd test_scores/

function [spk_x spk_y spk_t] = shuffle(spk_x, spk_y, spk_t)
	% shuffle
	r1 = randi([1 length(spk_x)],1,1);
	r2 = randi([1 length(spk_x)],1,1);
	temp = spk_x(r1);
	spk_x(r1) = spk_x(r2);
	spk_x(r2) = temp;
    temp = spk_y(r1);
	spk_y(r1) = spk_y(r2);
	spk_y(r2) = temp;
    temp = spk_t(r1);
	spk_t(r1) = spk_t(r2);
	spk_t(r2) = temp;
end

function heat_map = shuffle2(heat_map)
	% shuffle
	r1 = randi([1 length(heat_map)^2],1,1);
	r2 = randi([1 length(heat_map)^2],1,1);
	temp = heat_map(r1);
	heat_map(r1) = heat_map(r2);
	heat_map(r2) = temp;
end

function [spk_x spk_y] = shuffle3(spk_x, spk_y)
	% shuffle
    r = randi([1 length(spk_x)],1,1);
	xr = randi([1 100*30],1,1)*.01
	yr = randi([1 100*30],1,1)*.01
	spk_x(r) = xr;
	spk_y(r) = yr;
end