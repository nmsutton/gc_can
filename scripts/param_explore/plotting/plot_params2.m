% references: https://www.mathworks.com/help/matlab/ref/area.html
% https://www.mathworks.com/matlabcentral/fileexchange/5105-making-surface-plots-from-scatter-data
% possible alt. plots: https://www.mathworks.com/help/matlab/ref/gradient.html#bvhqkfr

downsample_colormap = 1; % activate colormap downsampling
downsample_amount = 1;%4;%10; % amount of downsampling; higher is more

% extract data
x=[];y=[];z=[];xyz=[];
results_data=readmatrix('gridness_score.txt');
plot_rotation_factor_1=10000;
plot_rotation_factor_2=300000;
plot_rotation_factor_3=0;
hco_default_point=[11.69,3]; % yellow; location of default hco value [p1,p2]
sim_used_point=[11.69,0]; % red; location of value used in sim [p1,p2]
hco_2std_range1=[0.0,0.0]; % purple; location of edge of hco 2std range
hco_2std_range2=[0.0,0.0];
show_selected_points=0; % plot the additional points
show_only_sel_points=0; % only show additional points
rev_axes_y=0; % reverse axes plotting direction
rev_axes_x=0;
rows_number=size(results_data(:,1));
for i=1:rows_number
	x=[x results_data(i,2)];
	y=[y results_data(i,3)];
	z=[z results_data(i,4)];
end

% create interpolated points along y-axis
grid_points=floor(sqrt(size(x))); % points along each axis
zi=1;
xis=linspace(grid_points(2),rows_number(1),grid_points(2)); % create x indices that are stepped at "grid_points" sized intervals.
for xi=xis
    for yi=1:grid_points(2)
        if yi>1 % skip first entry because two points along same axis are needed
	        x=[x results_data(xi,2)];
	        y=[y (results_data(yi,3)+results_data(yi-1,3))/2];
	        z=[z (results_data(zi,4)+results_data(zi-1,4))/2];
        end
        zi=zi+1;        
    end
end

% sort points for loop that comes after this
rows_number=size(x);
for i=1:rows_number(2)
	xyz=[xyz; x(i) y(i) z(i)];
end
xyz_sorted = sortrows(xyz,[1 2]); % sort x,y,z data first by x column then y to break any ties
x=[];y=[];z=[];
rows_number=size(xyz_sorted(:,1));
for i=1:rows_number
	x=[x xyz_sorted(i,1)];
	y=[y xyz_sorted(i,2)];
	z=[z xyz_sorted(i,3)];
end

% create interpolated points along x-axis
yinds=((grid_points(2)*2)-1); % number of y-indices per column
for yi=1:yinds
	for xi=1:grid_points(2)
        if xi>1 % skip first entry because two points along same axis are needed
        	xi_new=(yinds*(xi-1))+yi;
        	xi_old=(yinds*(xi-2))+yi;
	        x=[x (xyz_sorted(xi_new,1)+xyz_sorted(xi_old,1))/2];
	        y=[y xyz_sorted(yi,2)];
	        z=[z (xyz_sorted(xi_new,3)+xyz_sorted(xi_old,3))/2];
            %disp(xi);
        end 
	end
end

% sort points for creating tris in the right order
rows_number=size(x);
for i=1:rows_number(2)
	xyz=[xyz; x(i) y(i) z(i)];
end
xyz_sorted = sortrows(xyz,[1 2]); % sort x,y,z data first by x column then y to break any ties
x=[];y=[];z=[];
rows_number=size(xyz_sorted(:,1));
for i=1:rows_number
	x=[x xyz_sorted(i,1)];
	y=[y xyz_sorted(i,2)];
	z=[z xyz_sorted(i,3)];
end

% create plotting
%hold on
if show_only_sel_points==0
plot3(x,y,z,'.-');
tri = delaunay(x,y);
plot(x,y,'.');
[r,c] = size(tri);
h = trisurf(tri, x, y, z);

lighting phong;
shading interp;
colorbar EastOutside;
campos([plot_rotation_factor_1,plot_rotation_factor_3,plot_rotation_factor_2]);
end

% load CustomBlueGreenColormap;
% colormap(CustomBlueGreenColormap);
load CustomPinkPurpleColormap7;
colormap(CustomPinkPurpleColormap7);

if downsample_colormap
	cm = colormap;
	cmx = downsample(cm(:,1),downsample_amount);
	cmy = downsample(cm(:,2),downsample_amount);
	cmz = downsample(cm(:,3),downsample_amount);
	cm2 = [cmx'; cmy'; cmz'];
	cm2 = cm2';
	colormap(cm2);
end
%colormapeditor
if show_selected_points
hold on
scatter(hco_default_point(2),hco_default_point(1),20,[1,1,0.5],'filled');
scatter(sim_used_point(2),sim_used_point(1),20,[1,0,1],'filled');
scatter(hco_2std_range1(2),hco_2std_range1(1),20,[1,0.5,0.5],'filled');
scatter(hco_2std_range2(2),hco_2std_range2(1),20,[1,0.5,0.5],'filled');
hold off
ylim([min(results_data(:,2)) max(results_data(:,2))]);
xlim([min(results_data(:,3)) max(results_data(:,3))]);
end
% Tsodyks-Markram or Izhikevich
% title("Gridness Scores of Tsodyks-Markram g and tau_d Parameters for Grid Cells", 'FontSize', 11);
% xlabel('Tsodyks-Markram tau_d') 
% ylabel('Tsodyks-Markram g')
title("Gridness Scores of Izhikevich b and d Parameters for Grid Cells", 'FontSize', 11);
xlabel('Izhikevich d') 
ylabel('Izhikevich b')
axis('tight');
if rev_axes_y set(gca,'YDir','reverse'); end
if rev_axes_x set(gca,'XDir','reverse'); end