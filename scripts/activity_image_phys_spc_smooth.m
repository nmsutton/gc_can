%%
%% Create phys space plot with smoothing using methods
%% from the CMBHome software
%%
%% Todo: something seems wrong with the alt_heatmap
%% so original heatmap should be used for now
%%
%% Note: this is set to only use highres_spikes.csv from high_res_traj.m
%% use_hopper and use_laptop options are commented out. high_res_traj.m
%% needs to be run first to create data for this script.
%%
%% References: https://lost-contact.mit.edu/afs/inf.ed.ac.uk/group/teaching/matlab-help/R2016b/matlab/creating_plots/save-figure-at-specific-size-and-resolution.html
%% https://hydroecology.net/resizing-matlab-figures-the-easy-way/
%% https://www.mathworks.com/matlabcentral/answers/43326-create-figure-without-displaying-it

function heat_map = activity_image_phys_spc_smooth(run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,local_run)
	import CMBHOME.Utils.*

	%[root c_ts] = load_spike_times();

	use_carlsim_spikes = 1;
	alt_heatmap = 0;
	use_smoothing = 1;
	display_plot = 0;
	save_plot = 0;
	if run_on_hopper==1 save_plot = 1; end
	%use_laptop = 0;
	limit_time = 0;
	rot90deg = 0; % rotate matrix 90 degrees clockwise
	flip_vert = 0; % flip matrix vertically

	if use_carlsim_spikes
        plot_subsect=1;%0; % plot only subsection of total data. this is set by the plot_size variable.
		grid_size = 42;%30; % sqrt of grid size
		plot_size = 30; % sqrt of plot size
		binside = 3;
		std_smooth_kernel = 3.333;
		% use highres_spikes.csv from high_res_traj.m not hopper created text file
	    %hopper_use=0                                                                      ; % enable hopper folder or use local folder
	    %hopper_run=5;
	    %hopper_path=(['/mnt/hopper_scratch/gc_sim/',int2str(hopper_run),'/spikes/spikes_recorded.csv']);
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

	if use_carlsim_spikes
	    %if hopper_use
	    if false
	        %carlsim_spikes = readmatrix(hopper_path);
	    else
	        %if use_laptop == 0
	        if false
		        %carlsim_spikes = readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can/output/spikes/spikes_recorded.csv');
	        else
	            curr_dir = pwd;
                %if use_hopper_data==0 run_number=local_run; else run_number=hopper_run; end
                %curr_dir = replace(curr_dir,"gc_can_1",strcat(fdr_prefix,int2str(run_number)));
                %curr_dir = replace(curr_dir,"code/1","code/gc_can_1");
                cd(curr_dir);
	            carlsim_spikes = readmatrix(curr_dir+"/high_res_traj/highres_spikes.csv");
                disp(curr_dir+"/high_res_traj/highres_spikes.csv");
	        end
	    end
		if alt_heatmap
			spike_x = carlsim_spikes(1:end,3); % matlab indices are (y,x) not (x,y)
			spike_y = carlsim_spikes(1:end,2);
		else
			if use_carlsim_spikes
				spike_x = carlsim_spikes(1:end,3);
				spike_y = carlsim_spikes(1:end,2);
			else
				spike_x = carlsim_spikes(1:end,3)*(360/30);
				spike_y = carlsim_spikes(1:end,2)*(360/30);
			end
	    end
	    % limit time included if wanted
	    if limit_time ~= 0
	        limit_i_max = find(carlsim_spikes(1:end,1)<limit_time);
	        spike_x=spike_x(1:length(limit_i_max));
	        spike_y=spike_y(1:length(limit_i_max));
	    end
		% update grid size if larger x or y values are found
		if max(spike_x)>grid_size || max(spike_y)>grid_size
			if max(spike_x)>max(spike_y)
				grid_size=ceil(max(spike_x));
	            if floor(min(spike_x)) < 0
	                grid_size=ceil(max(spike_x))-floor(min(spike_x));
	            end
			else
				grid_size=ceil(max(spike_y));
	            if floor(min(spike_y)) < 0
	                grid_size=ceil(max(spike_y))-floor(min(spike_y));
	            end
			end
	    end
	    % shift matrix to account for negative values
	    if floor(min(spike_x)) < 0
	        spike_x=spike_x-floor(min(spike_x));
	    end
	    if floor(min(spike_y)) < 0
	        spike_y=spike_y-floor(min(spike_y));
	    end
	end
	heat_map = zeros(1,grid_size*grid_size);

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
	            if y > grid_size
	                y = grid_size; % fix anomalous value error
	            elseif y < 0
	                y = 1;
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
			xdim = linspace(0,grid_size-1,grid_size);%xdim * 30/360;
			ydim2 = linspace(0,grid_size-1,grid_size);%ydim2 * 30/360;
			heat_map = hist3([spike_x, spike_y], 'Edges', {xdim, ydim2});
            if plot_subsect
			    s = (grid_size-plot_size)/2;
			    e = plot_size+s;
			    heat_map = heat_map(s:e, s:e); % crop to intended plot size
            end
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

	if rot90deg
		heat_map=rot90(heat_map,-1);
	end
	if flip_vert
		heat_map=flipud(heat_map);
	end

	% plot
	if display_plot == 0
		fig = figure('visible','off');
	else
		fig = figure;
	end
	imagesc(heat_map);
	axis('tight')
	xlabel('animal position on x axis') 
	ylabel('animal position on y axis')
	cb = colorbar;
	ax = gca;
	ax.YDir = 'normal'; % have y-axis 0 on bottom left
	if use_carlsim_spikes
		%caxis([0 160])
	    %caxis([0 80])
	    %caxis([0 30])
		caption = sprintf('Physical space grid cell firing, total t = %.0f ms', carlsim_spikes(end,1));
	else
		caxis([0 25])
		caption = sprintf('Physical space grid cell firing, total t = %.0f ms', c_ts(end)*1000);
	end
	title(caption, 'FontSize', 11);
	%set(fig, 'units', 'inches', 'position', [0 50 5 4.444]);
	set(fig, 'units', 'inches', 'position', [0 50 5.31 4.444]);
	if display_plot == 0
		set(fig,'visible','on');
	end
	if save_plot
		c = clock;
		hr = mod(c(4),12);
		output_filename = sprintf("ratemap_%.0f-%.0f-%.0f_%.0f-%.0f-%.0f.png",hr,c(5),c(6),c(2),c(3),c(1));
		exportgraphics(gcf,output_filename,'Resolution',300)
	end
end