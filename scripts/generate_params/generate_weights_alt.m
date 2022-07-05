% references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point
% https://stackoverflow.com/questions/19343863/find-new-coordinate-x-y-given-x-y-theta-and-velocity

% run options
show_full_matrix = 0;

% params
grid_size = 90.0;
grid_size_target = 30; % target grid size for neuron weights
p1=20;%.68;
p2=2;p3=2;
p4=40; % bump width
p5=p3;p6=p4;p7=1;
p8=0.0058; % y-intercept shift
wsf = 1;%1.005; % weights scaling factor
wsf2 = 1;%-0.1; % weights scaling factor 2
p=[p1,p2,p3,p4,p5,p6,p7,p8,wsf];
po=[1,1,1,1,grid_size,1,1,grid_size_target,1,1,1,1,wsf];

high_weight=0.00681312463724531; % highest inhib synapse weight
synapse_weights=ones(grid_size);

cx=0; % init feild center x
cy=0; % init field center y
cx_sft=-30; % x-axis shift
cy_sft=-30; % y-axis shift
tiles=25;
t_shifts=15; % tile shifts
% spacing control
d=15/2; % spacing along axis that is tiled
t_sft_x=15; % x-axis tile shift distance
t_sft_y=0; % y-axis tile shift distance
stag_x=t_sft_x/2; %0; %t_sft_x/2; % x-axis tile stagger distance
stag_y=0; % y-axis tile stagger distance
% rotations
a=90;%90-18; % angle of movement
a=a/360 * pi*2; % convert to radians

for i=1:t_shifts
    cx_sft=cx_sft+t_sft_x; % x-axis shifts
    %cy_sft=cy_sft+t_sft_y; % y-axis shifts
    cx=0;cy=0;
    po2=[cx,cy,cx_sft,cy_sft,d,a,tiles,stag_x,stag_y,grid_size,grid_size_target];
    [synapse_weights,cx,cy]=tile_rot(po2,grid_size,p,synapse_weights);
end

% rescale to desired value ranges
max_v=max(synapse_weights);
max_v=max(max_v);
min_v=min(synapse_weights);
min_v=min(min_v);
synapse_weights=synapse_weights-min_v;
max_v=max(synapse_weights);
max_v=max(max_v);
synapse_weights=synapse_weights*(high_weight/max_v);

synapse_weights_crop=crop_weights(po2,synapse_weights);

if show_full_matrix
    plt = imagesc(synapse_weights);
else
    plt = imagesc(synapse_weights_crop);
end

function [synapse_weights,cx,cy]=tile_rot(po2,grid_size,p,synapse_weights)
    cx=po2(1);cy=po2(2);cx_sft=po2(3);cy_sft=po2(4);d=po2(5);a=po2(6);
    tiles=po2(7);

    for i=1:tiles
        cx=cos(a)*d+cx;
        cy=sin(a)*d+cy;        
        for j=1:grid_size^2
            y=mod((j-1),grid_size);
            x=floor((j-1)/grid_size);
            x_shift = cx+cx_sft;
            y_shift = cy+cy_sft;
            z=field(x,y,x_shift,y_shift,p,po2,i);
            synapse_weights(j)=synapse_weights(j)-z;
        end
    end
end

function z=field(x,y,x_shift,y_shift,p,po2,i)
    % firing bumps function
    x=(x-x_shift);
    y=(y-y_shift);
    % stagger x and y
    stag_x=po2(8);stag_y=po2(9);
    if mod((i-1),2)==0
        x=x+stag_x;
        y=y+stag_y;
    end
    p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);wsf=p(9);
    % gaussian function
    z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4) ...
        -(y.^p5/p6)))*p7)-p8;
    z=z*wsf; % scaling factor
    if z < 0
        z = 0; % negative values rectifier
    end
end

function synapse_weights_crop=crop_weights(po2,synapse_weights)
    % apply rotation to synapse weights matrix

    grid_size=po2(10);grid_size_target=po2(11);synapse_weights_crop=zeros(grid_size_target);

    %% crop larger distribution into smaller target sized one
    target_offset = (grid_size-grid_size_target)/2;
    for y=1:grid_size_target
        for x=1:grid_size_target
            x2 = target_offset + x;
            y2 = target_offset + y;
            synapse_weights_crop(x,y)=synapse_weights(x2,y2);
        end
    end
end