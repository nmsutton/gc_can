% alternative version of generate weights
% this script generates a synaptic_weights matrix
% which can be run in the main generate weights script
%
% references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point
% https://stackoverflow.com/questions/19343863/find-new-coordinate-x-y-given-x-y-theta-and-velocity
% https://www.omnicalculator.com/math/right-triangle-side-angle#:~:text=If%20you%20have%20an%20angle,side%20adjacent%20to%20the%20angle.
% https://www.mathworks.com/matlabcentral/answers/122454-doulbe-the-size-of-all-elements-in-a-matrix
% https://www.mathworks.com/matlabcentral/answers/323483-how-to-rotate-points-on-2d-coordinate-systems

% run options
limited_fields=1; % create inhibition pattern that targets limited fields

grid_size = 120.0;
grid_size_target = 30; % target grid size for neuron weights
synapse_weights=ones(grid_size);
% field params
if limited_fields
    p1=20;%.68;
    p2=2;p3=2;
    p4=15;%8; % bump width
    p5=p3;p6=p4;p7=0.20;
    p8=30;%.135;
    p9=2;p10=2;p11=2;p12=p4;p13=p11;p14=p11;p15=p12;p16=1.08;
    p17=0.0058;
    p=[p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17];
else
    p1=20;%.68;
    p2=2;p3=2;
    p4=30; % bump width
    p5=p3;p6=p4;p7=1;
    p8=0.0058; % y-intercept shift
    p=[p1,p2,p3,p4,p5,p6,p7,p8];
end
high_weight=0.00681312463724531; % highest inhib synapse weight
rect=1; % rectify weights to high weight when reaching threshold
rect_thresh=0.001;
% tile spacing control
cx_sft=-40;%-29; % x-axis shift
cy_sft=-3;%-27; % y-axis shift
y_tiles=12;%4;%25;
x_tiles=17;%4;%15; % x-axis tiling
y_t_space=10.54;%13.5;%10.54; % spacing of tiling along y-axis
x_t_space=14;%14.4;%12;%10; % spacing of tiling along x-axis
s_mult = 1;%1.15;%1.3;%1.15;%1.3; % spacing multipler
f_area = 9;%4;%5;%6; % sqrt of area each field contributes values to
stag_x=0;%x_t_space/2; % x-axis tile stagger distance
stag_y=0; % y-axis tile stagger distance
x_wrap=0; % wrap around values on x-axis
y_wrap=0; % wrap around values on y-axis
% rotations
a=0;%10;%90-18.435;%90-18; % angle of movement
a=a/360 * pi*2; % convert to radians
% limited fields params
seven_fields=1; % choose between 7 or 4 field in initial shape
centx = []; centy = []; % x- and y-axis values of centroids
center_x = 46; center_y = 46;
select_cent=[3,4,5];%[1,2,3];%[1,4,7];%[3,4,5];% centroid indicies to duplicate

cx=0; cy=0; % init feild centers
tempx=[]; tempy=[];
if limited_fields==1
    po2=[x_wrap,y_wrap,cx_sft,cy_sft,y_t_space,a,y_tiles,stag_x,stag_y,grid_size,grid_size_target,f_area];
    synapse_weights=zeros(grid_size);
    [centx,centy]=init_hex(centx,centy,center_x,center_y,x_t_space,y_t_space,s_mult,seven_fields);
    [centx,centy]=rot_hex(centx,centy,a,center_x,center_y);
    [centx,centy]=dup_cent(centx,centy,select_cent);
    synapse_weights=feilds_from_cents(po2,grid_size,p,synapse_weights,centx,centy);
else
    for i=1:x_tiles
        po2=[x_wrap,y_wrap,cx_sft,cy_sft,y_t_space,a,y_tiles,stag_x,stag_y,grid_size,grid_size_target,f_area];
        [synapse_weights,tempx,tempy]=tile_rot(po2,grid_size,p,synapse_weights,tempx,tempy);
        cx_sft=cx_sft+x_t_space; % x-axis shifts
    end
end

synapse_weights_crop=crop_weights(po2,synapse_weights);
[synapse_weights,synapse_weights_crop]=rescale(synapse_weights, ...
    synapse_weights_crop,high_weight,rect,rect_thresh);
plt = imagesc(synapse_weights_crop);

function [centx, centy]=init_hex(centx,centy,center_x,center_y,x_t_space,y_t_space,s_mult,seven_fields)
    m=s_mult;
    % initial hexagon
    if seven_fields
        centx=[centx, center_x-((x_t_space/2)*m)];
        centy=[centy, center_y-(y_t_space*m)];
        centx=[centx, center_x+((x_t_space/2)*m)];
        centy=[centy, center_y-(y_t_space*m)];
    end
        centx=[centx, center_x-(x_t_space*m)];
        centy=[centy, center_y];    
        centx=[centx, center_x];
        centy=[centy, center_y];    
        centx=[centx, center_x+(x_t_space*m)];
        centy=[centy, center_y];    
    if seven_fields
        centx=[centx, center_x-((x_t_space/2)*m)];
        centy=[centy, center_y+(y_t_space*m)];
        centx=[centx, center_x+((x_t_space/2)*m)];
        centy=[centy, center_y+(y_t_space*m)];           
    end
end

function [centx,centy]=rot_hex(centx,centy,a,center_x,center_y)
    a=(a/(pi*2))*360; % convert from radian to angle
    R = [cosd(a) -sind(a); sind(a) cosd(a)];
    for i=1:length(centx)
        % rotate around center point
        x=centx(i)-center_x;
        y=centy(i)-center_y;
        point = [x y]';
        rotpoint = R*point;
        centx(i)=rotpoint(1)+center_x;
        centy(i)=rotpoint(2)+center_y;
    end
end

function [centx,centy]=dup_cent(centx,centy,select_cent)
    for i=1:length(select_cent)
        i2=select_cent(i);
        centx=[centx,centx(i2)];
        centy=[centy,centy(i2)-30];
    end
    for i=1:length(select_cent)
        i2=select_cent(i);
        centx=[centx,centx(i2)];
        centy=[centy,centy(i2)+30];
    end
end

function [synapse_weights,synapse_weights_crop]=rescale(synapse_weights, ...
          synapse_weights_crop,high_weight,rect,rect_thresh)
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
    % rectify all weights above a threshold
    if rect
        synapse_weights_crop(find(synapse_weights_crop(:)>rect_thresh))=high_weight;
        synapse_weights(find(synapse_weights(:)>rect_thresh))=high_weight;
    end
end

function synapse_weights=feilds_from_cents(po2,grid_size,p,synapse_weights,centx,centy)
    x_wrap=po2(1);y_wrap=po2(2);grid_size_target=po2(11);fa=po2(12);
    % generate fields from centroids
    for i=1:length(centx)
        for j=1:(grid_size_target)^2
            % x,y for field values calc
            y=floor((j-1)/grid_size_target) - (grid_size_target/2);
            x=mod((j-1),grid_size_target) - (grid_size_target/2);
            %y2=floor(y);x2=floor(x); % make whole numbers for indices  
            y2=y;x2=x;
            %z=field(x2,y2,p);
            z=cent_surr(x2,y2,p);
            % x,y for 2d plane position calc
            y3=centy(i)+y2; x3=centx(i)+x2;
            %y3=floor(y3);x3=floor(x3);
            if square_dist(x2,y2,fa)
            %if circle_dist(x2,y2,fa)
                if x3 > 0 && y3 > 0 && x3 < grid_size && y3 < grid_size
                    %synapse_weights(y3,x3)=synapse_weights(y3,x3)+z;
                    synapse_weights=add_weight(synapse_weights,x3,y3,z,grid_size);
                    max_v=0.03;
                    %tempx=[tempx x];tempy=[tempy y];
                end
            end 
        end
    end
end

function [synapse_weights,tempx,tempy]=tile_rot(po2,grid_size,p,synapse_weights,tempx,tempy)
    cx=0;cy=0;x_wrap=po2(1);y_wrap=po2(2);cx_sft=po2(3);cy_sft=po2(4);y_t_space=po2(5);a=po2(6);
    y_tiles=po2(7);grid_size_target=po2(11);fa=po2(12);stag_x=po2(8);stag_y=po2(9);

    for i=1:y_tiles+1
        x_cent = cx+cx_sft; % x centroid
        y_cent = cy+cy_sft; % y centroid
        if mod((i-1),2)==0 x_cent=x_cent+stag_x; y_cent=y_cent+stag_y; end  % stagger x and y        
        for j=1:(grid_size_target*1)^2 % assume (grid_size_target)^2 covers enough area for field values
            % x,y for field values calc
            y=floor((j-1)/grid_size_target) - ((grid_size_target*1)/2);
            x=mod((j-1),grid_size_target) - ((grid_size_target*1)/2);
            y2=floor(y);x2=floor(x); % make whole numbers for indices                   
            %y2=y;x2=x;
            z=field(x2,y2,p);
            % x,y for 2d plane position calc
            y3=y_cent-y2; x3=x_cent-x2;
            y3=floor(y3);x3=floor(x3);
            [x3,y3]=wrap_around(x_wrap,y_wrap,x3,y3,grid_size);
            if square_dist(x2,y2,fa)
            %if circle_dist(x,y,fa)
                %synapse_weights=add_weight(synapse_weights,x3,y3,z,grid_size);
                if x3 > 0 && y3 > 0 && x3 < grid_size && y3 < grid_size
                    synapse_weights(y3,x3)=-z;
                    tempx=[tempx x];tempy=[tempy y];
                end
            end               
        end
        cx=cos(a)*y_t_space+cx; cy=sin(a)*y_t_space+cy;        
        %tempx=[tempx x_cent];tempy=[tempy y_cent]; 
    end
end

function [x,y]=wrap_around(x_wrap,y_wrap,x,y,grid_size)
    if x_wrap && x > grid_size x=grid_size-x; end
    if x_wrap && x < 1 x=grid_size+x; end
    if y_wrap && y > grid_size y=grid_size-y; end
    if y_wrap && y < 1 y=grid_size+y; end
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

function z=field(x,y,p)
    p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);
    z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4)-(y.^p5/p6)))*p7)-p8; % gaussian function
    %fprintf("%d %d %d\n",x,y,z);
    if z < 0 z = 0; end % negative values rectifier
end

function boolean=square_dist(x,y,fa)
    % measure square shaped distance from circle center
    boolean = false;
    if x > (-1*fa) && x < fa && y > (-1*fa) && y < fa boolean = true; end   
end

function boolean=circle_dist(x,y,fa)
    % measure distance from circle center
    boolean = false;
    ed=sqrt((0-y)^2+(0-x)^2); % euclidean dist
    if ed <= fa boolean = true; end        
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
                 synapse_weights(y_min,x_min)+z*.5* ...
                 (1-mod(x,1)+1-mod(y,1))/2;
               end
               if x2==2 && y2 ==1
                 synapse_weights(y_min,x_max)= ...
                 synapse_weights(y_min,x_max)+z*.5* ...
                 (mod(x,1)+1-mod(y,1))/2;
               end
               if x2==1 && y2 ==2
                 synapse_weights(y_max,x_min)= ...
                 synapse_weights(y_max,x_min)+z*.5* ...
                 (1-mod(x,1)+mod(y,1))/2;
               end
               if x2==2 && y2 ==2
                 synapse_weights(y_max,x_max)= ...
                 synapse_weights(y_max,x_max)+z*.5* ...
                 (mod(x,1)+mod(y,1))/2;
               end
            end
        end
    end    
end

function z=cent_surr(x,y,p)
    % center-surround function
    p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);p9=p(9);
    p10=p(10);p11=p(11);p12=p(12);p13=p(13);p14=p(14);p15=p(15);p16=p(16);p17=p(17);
    % difference of gaussians function creates the center-surround
    z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4) ...
        -(y.^p5/p6)))*p7-(p8/sqrt(p9*pi) ...
        .*exp(-(p10*x.^p11/p12)-(p13*y.^p14/p15)))*p16)-p17;
    if z < 0
        z = 0; % negative values rectifier
    end
end