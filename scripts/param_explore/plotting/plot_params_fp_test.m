downsample_colormap = 1; % activate colormap downsampling
downsample_amount = 10; % amount of downsampling; higher is more

% extract data
x=[];y=[];z=[];xyz=[];
p1_column=3;
p2_column=4;
plot_rotation_factor_1=10;%34.68;%34.6;%376;%-100000;%500;%1000;%34.65;%25.005;%.51999;%1.9999;
plot_rotation_factor_2=10;%100000;%800;%100000;%20000;%100000;%200;
results_data=readmatrix('param_records_ea_iz.txt');
rev_axes=0; % reverse axes plotting direction
rows_number=size(results_data(:,1));
for i=1:rows_number
	x=[x results_data(i,p1_column)];
	y=[y results_data(i,p2_column)];
	z=[z abs(results_data(i,2))];
end

% create interpolated points along y-axis
grid_points=floor(sqrt(size(x))); % points along each axis
zi=1;
xis=linspace(grid_points(2),rows_number(1),grid_points(2)); 
for xi=xis
    for yi=1:grid_points(2)
        if yi>1 % skip first entry because two points along same axis are needed
	        x=[x results_data(xi,2)];
	        y=[y (results_data(yi,3)+results_data(yi-1,3))/2];
	        z=[z (results_data(zi,4)+results_data(zi-1,4))/2];
            %disp(xi);
        end
        zi=zi+1;        
    end
end