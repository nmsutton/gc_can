% reference: https://www.mathworks.com/help/matlab/ref/area.html
% https://www.mathworks.com/matlabcentral/fileexchange/5105-making-surface-plots-from-scatter-data
x=[];y=[];z=[];xyz=[];
results_data=readmatrix('iz_results_example.txt');
%grid_points=100;
%score_threshold = 0.2;
rows_number=size(results_data(:,1));
for i=1:rows_number
	x=[x results_data(i,2)];
	y=[y results_data(i,3)];
	z=[z results_data(i,4)];
end
% create interpolated points
grid_points=floor(sqrt(size(x)));
zi=2;
xis=linspace(grid_points(2),rows_number(1),grid_points(2));
for xi=xis
    for yi=1:grid_points(2)
        if yi>1 % skip first entry
	        x=[x results_data(xi,2)];
	        y=[y (results_data(yi,3)+results_data(yi-1,3))/2];
	        z=[z (results_data(zi,4)+results_data(zi-1,4))/2];
            zi=zi+1;
            %disp(xi);
        end
    end
end

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
%%%
plot3(x,y,z,'.-');
tri = delaunay(x,y);
plot(x,y,'.');
[r,c] = size(tri);
%disp(r);
h = trisurf(tri, x, y, z);

%axis vis3d
%axis off
%l = light('Position',[-50 -15 29])
%l = light('Position',[-.5 -.15 2])
%set(gca,'CameraPosition',[208 -50 7687])
lighting phong;
shading interp;
colorbar EastOutside;
campos([0.52,0,200]);

%xlim([min(x) max(x)])
%ylim([min(y) max(y)])
%colormap default
%colormap(parula(25))
%{
map = [0 0 0.0
    0 0 0.2
    0 0 0.4
    0 0 0.6
    0 0 0.8
    0 0 1.0];
colormap(map)
%}
load CustomBlueGreenColormap;
colormap(CustomBlueGreenColormap);
%colormapeditor
%axis([min(x) max(x) min(y) max(y)])
title("Gridness score of parameters for grid cells", 'FontSize', 11);
axis('tight');
%xlabel('Izhikevich k value') 
%ylabel('Izhikevich a value')
xlabel('tau_x value');
ylabel('tau_d value');
%legend('<0.2 gridness','>=0.2 gridness')