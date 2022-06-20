%%
%% Create phys space plot with smoothing using methods
%% from the CMBHome software
%%
%% Todo: something seems wrong with the alt_heatmap
%% so original heatmap should be used for now
%%

import CMBHOME.Utils.*

[root c_ts] = load_spike_times();

use_carlsim_spikes = 1;
alt_heatmap = 0;
use_smoothing = 1;

if use_carlsim_spikes
	grid_size = 30; % sqrt of grid size
else
	grid_size = 32;
	spike_x = root.cel_x{1,1};
	resize_factor = 660;
	spike_y = root.cel_y{1,1}-resize_factor;
	spike_y2 = root.cel_y{1,1};
	conversion_factor = grid_size/360;
	xdim = [];
	ydim = [];
	binside = 3;
	continuize_epochs = 1;
	std_smooth_kernel = 3;
end
heat_map = zeros(1,grid_size*grid_size);

if use_carlsim_spikes
	carlsim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_cs4/output/spikes/spikes_recorded.csv');
	if alt_heatmap
		spike_x = carlsim_spikes(1:end,2);
		spike_y = carlsim_spikes(1:end,3);
	else
		if use_carlsim_spikes
			spike_x = carlsim_spikes(1:end,2);
			spike_y = carlsim_spikes(1:end,3);
		else
			spike_x = carlsim_spikes(1:end,2)*(360/30);
			spike_y = carlsim_spikes(1:end,3)*(360/30);
		end
	end
end

if alt_heatmap
	if use_carlsim_spikes
		for i = 1:size(carlsim_spikes,1)
			x = floor(spike_x(i))+1;
			y = floor(spike_y(i));
            if x > grid_size
                x = grid_size; % fix anomalous value error
            elseif x < 0
                x = 1;
            end
			i2 = (y * grid_size) + x;
			heat_map(i2) = heat_map(i2) + 1;
		end
	else
		for i = 1:c_ts(end)
			x = floor(spike_x(i)*conversion_factor);
			y = floor(spike_y(i)*conversion_factor);
			i2 = (y * grid_size) + x;
			heat_map(i2) = heat_map(i2) + 1;
		end
	end
end

if alt_heatmap
	if use_carlsim_spikes
		heat_map = reshape(heat_map,grid_size,grid_size);
		if use_smoothing
			heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
		end
	else
		heat_map = reshape(heat_map,grid_size,grid_size);
		if use_smoothing
			heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
		end
	end
else
	if use_carlsim_spikes
		xdim = linspace(0,29,30);%xdim * 30/360;
		ydim2 = linspace(0,29,30);%ydim2 * 30/360;
		heat_map = hist3([spike_x, spike_y], 'Edges', {xdim, ydim2});
		if use_smoothing
			heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
		end
	else
		[occupancy, xdim, ydim] = root.Occupancy(xdim, ydim, continuize_epochs, binside);
		ydim2 = ydim - resize_factor;
		heat_map = hist3([spike_x, spike_y], 'Edges', {xdim, ydim2});
		if use_smoothing
			%heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside)./SmoothMat(occupancy, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
			heat_map = SmoothMat(heat_map, [5*std_smooth_kernel/binside, 5*std_smooth_kernel/binside], std_smooth_kernel/binside); % smooth the spikes and occupancy with a 5x5 bin gaussian with std=1
		end
	end		
end

% plot
imagesc(heat_map);
axis('tight')
xlabel('animal position on x axis') 
ylabel('animal position on y axis')
cb = colorbar;
if use_carlsim_spikes
	caxis([0 120])
	caption = sprintf('Physical space grid cell firing, total t = %.0f ms', carlsim_spikes(end,1));
else
	caxis([0 25])
	caption = sprintf('Physical space grid cell firing, total t = %.0f ms', c_ts(end)*1000);
end
title(caption, 'FontSize', 15);