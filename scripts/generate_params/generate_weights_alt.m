    % references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point
% https://stackoverflow.com/questions/19343863/find-new-coordinate-x-y-given-x-y-theta-and-velocity
% https://www.omnicalculator.com/math/right-triangle-side-angle#:~:text=If%20you%20have%20an%20angle,side%20adjacent%20to%20the%20angle.

% run options
grid_size = 120.0;
grid_size_target = 30; % target grid size for neuron weights
synapse_weights=ones(grid_size);
% field params
p1=20;%.68;
p2=2;p3=2;
p4=30; % bump width
p5=p3;p6=p4;p7=1;
p8=0.0058; % y-intercept shift
p=[p1,p2,p3,p4,p5,p6,p7,p8];
po=[1,1,1,1,grid_size,1,1,grid_size_target,1,1,1,1];
high_weight=0.00681312463724531; % highest inhib synapse weight
% tile spacing control
cx_sft=-40;%-29; % x-axis shift
cy_sft=-4;%-27; % y-axis shift
y_tiles=12;%4;%25;
x_tiles=17;%4;%15; % x-axis tiling
y_t_space=10.54; % spacing of tiling along y-axis
x_t_space=10; % spacing of tiling along x-axis
stag_x=0; %x_t_space/2; % x-axis tile stagger distance
stag_y=0; % y-axis tile stagger distance
x_wrap=0; % wrap around values on x-axis
y_wrap=0; % wrap around values on y-axis
% rotations
a=90-18.435;%90-18; % angle of movement
a=a/360 * pi*2; % convert to radians

cx=0; cy=0; % init feild centers
tempx=[]; tempy=[];
for i=1:x_tiles
    po2=[x_wrap,y_wrap,cx_sft,cy_sft,y_t_space,a,y_tiles,stag_x,stag_y,grid_size,grid_size_target];
    [synapse_weights,tempx,tempy]=tile_rot(po2,grid_size,p,synapse_weights,tempx,tempy);
    cx_sft=cx_sft+x_t_space; % x-axis shifts
    %cy_sft=cy_sft+y_t_space; % x-axis shifts
end

synapse_weights_crop=crop_weights(po2,synapse_weights);
[synapse_weights,synapse_weights_crop]=rescale(synapse_weights,synapse_weights_crop,high_weight);

plt = imagesc(synapse_weights_crop);

function [synapse_weights,synapse_weights_crop]=rescale(synapse_weights,synapse_weights_crop,high_weight)
    % rescale to desired value ranges
    % set it relative to cropped region
    % set min
    max_v=max(synapse_weights_crop); max_v=max(max_v);
    min_v=min(synapse_weights_crop); min_v=min(min_v);
    synapse_weights_crop=synapse_weights_crop-min_v;
    synapse_weights=synapse_weights-min_v;
    % set max
    max_v=max(synapse_weights_crop); max_v=max(max_v);
    synapse_weights_crop=synapse_weights_crop*(high_weight/max_v);
    synapse_weights=synapse_weights*(high_weight/max_v);
end

function [synapse_weights,tempx,tempy]=tile_rot(po2,grid_size,p,synapse_weights,tempx,tempy)
    cx=0;cy=0;x_wrap=po2(1);y_wrap=po2(2);cx_sft=po2(3);cy_sft=po2(4);y_t_space=po2(5);a=po2(6);
    y_tiles=po2(7);grid_size_target=po2(11);

    for i=1:y_tiles+1
        x_shift = cx+cx_sft;
        y_shift = cy+cy_sft;
        for j=1:(grid_size_target*1)^2 % assume (grid_size_target)^2 covers enough area for field values
            % x,y for field values calc
            %if i == 1
            y=floor((j-1)/grid_size_target) - ((grid_size_target*1)/2);
            x=mod((j-1),grid_size_target) - ((grid_size_target*1)/2);
            y=floor(y);x=floor(x); % make whole numbers for indices                   
            z=field(x,y,p,po2,i);
            % x,y for 2d plane position calc
            y2=y_shift-y; x2=x_shift-x;
            y2=floor(y2);x2=floor(x2);
            %{
            if x_wrap && x > grid_size x=grid_size-x; end
            if x_wrap && x < 1 x=grid_size+x; end
            if y_wrap && y > grid_size y=grid_size-y; end
            if y_wrap && y < 1 y=grid_size+y; end
            %}                       
            if x > -4 && x < 4 && y > -4 && y < 4
                %synapse_weights=add_weight(synapse_weights,x2,y2,z,grid_size);
                if x2 > 0 && y2 > 0 && x2 < grid_size && y2 < grid_size
                    synapse_weights(y2,x2)=-z;
                    tempx=[tempx x2];tempy=[tempy y2];
                end
            end   
            %end              
        end
        cx=cos(a)*y_t_space+cx; cy=sin(a)*y_t_space+cy;        
        %tempx=[tempx x_shift];tempy=[tempy y_shift]; 
    end
end

function synapse_weights2=crop_weights(po2,synapse_weights)
	% apply rotation to synapse weights matrix

	grid_size=po2(10);grid_size_target=po2(11);synapse_weights2=zeros(grid_size_target);

    %% crop larger distribution into smaller target sized one
    target_offset = (grid_size-grid_size_target)/2;
    for y=1:grid_size_target
        for x=1:grid_size_target
        	x2 = target_offset + x;
        	y2 = target_offset + y;
        	synapse_weights2(x,y)=synapse_weights(x2,y2);
        end
    end
end

function z=field(x,y,p,po2,i)
    %stag_x=po2(8);stag_y=po2(9); % stagger x and y
    %if mod((i-1),2)==0 x=x+stag_x; y=y+stag_y; end
    p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);
    z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4)-(y.^p5/p6)))*p7)-p8; % gaussian function
    %fprintf("%d %d %d\n",x,y,z);
    if z < 0 z = 0; end % negative values rectifier
end

function synapse_weights=add_weight(synapse_weights,x,y,z,grid_size)
    %% Convert fractions to whole number indicies and values
    %% split values across indicies according to their fractions.
    %% Matlab indices are (y,x) not (x,y).

    x_max=ceil(x);
    x_min=floor(x);
    y_max=ceil(y);
    y_min=floor(y);
    if x_min > 0 && x_max <= grid_size && y_min > 0 && y_max <= grid_size    
        for x2=1:2
            for y2=1:2
               if x2==1 && y2 ==1
                 synapse_weights(y_min,x_min)= ...
                 synapse_weights(y_min,x_min)-z*.5* ...
                 (1-mod(x,1)+1-mod(y,1))/2;
               end
               if x2==2 && y2 ==1
                 synapse_weights(y_min,x_max)= ...
                 synapse_weights(y_min,x_max)-z*.5* ...
                 (mod(x,1)+1-mod(y,1))/2;
               end
               if x2==1 && y2 ==2
                 synapse_weights(y_max,x_min)= ...
                 synapse_weights(y_max,x_min)-z*.5* ...
                 (1-mod(x,1)+mod(y,1))/2;
               end
               if x2==2 && y2 ==2
                 synapse_weights(y_max,x_max)= ...
                 synapse_weights(y_max,x_max)-z*.5* ...
                 (mod(x,1)+mod(y,1))/2;
               end
            end
        end
    end    
end