% references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point

% params
output_filename = "ext_dir_initial.cpp";
output_file = fopen(output_filename,'w');
grid_size = 90.0;
grid_size_target = 30; % target grid size for neuron weights
iter = 13; % iterations to run cent-surr function. i.e., number of tiled cent-surr dist. along an axis. e.g., value 5 creates 5x5 cent-surr circles in the weights plot.
start_x_shift = (grid_size/2) - 48; %- 44;%1;%28; -2 = 2 down
start_y_shift = (grid_size/2) + 52; %- 44;%1;%-4;%28; +2 = 2 left
p1=.68;p2=2;p3=2;p4=20;p5=p3;p6=p4;
p7=0.1; % bump width
p8=0.0058; % y-intercept shift
htf = .25;%0.28; % horizonal tiling factor
vtf = .45;%0.4; % vertical tiling factor
tiling_fraction=0.3;%0.24;%0.29;%0.33333333333;%0.1;%0.33333333333;%1;%0.33;%0.5; % fraction of standard tiling distance between bumps
fsf = 60/0.0212; % firing scaling factor
p=[p1,p2,p3,p4,p5,p6,p7,p8,fsf];
po=[1,1,1,output_file,grid_size,iter,tiling_fraction, ...
    grid_size_target,start_x_shift,start_y_shift,htf,vtf,fsf];
% rotation variables
a=350; % angle
a=a/360 * pi*2; % convert to radians
Rz = [cos(a) -sin(a) 0; sin(a) cos(a) 0; 0 0 1]; % rotate along Z axis. See references for other axis code if wanted.

% write to file and create matrix
ext_dir_initial=nrn_syn_wts(start_x_shift,start_y_shift,p,po);
ext_dir_initial2=rotate_weights(po,Rz,ext_dir_initial);
ext_dir_initial3=shift_weights(po,1,ext_dir_initial2);
ext_dir_initial4=crop_weights(po,ext_dir_initial3);
ext_dir_initial5=reshape(ext_dir_initial4,1,grid_size_target^2);
fprintf(output_file,'vector<float> ext_dir_initial{{');
for i=1:length(ext_dir_initial5)
	fprintf(output_file,'%f',ext_dir_initial5(i));
	if i ~= length(ext_dir_initial5)
		fprintf(output_file,',');
	end
end
fprintf(output_file,'}};');
imagesc(ext_dir_initial4);
fclose(output_file);
disp("processing completed");

function ext_dir_initial2=rotate_weights(po,Rz,ext_dir_initial)
	% apply rotation to synapse weights matrix

	grid_size=po(5);grid_size_target=po(8);

	% create rotation
	ext_dir_initial = reshape(ext_dir_initial,grid_size,grid_size);
    ext_dir_initial2 = zeros(grid_size);
    for y=1:grid_size
        for x=1:grid_size
            i=((y-1)*grid_size)+x;
            z=ext_dir_initial(i); 
            center_of_rot=grid_size/2;
            r_x_shift = x - center_of_rot;
            r_y_shift = y - center_of_rot;         
            rv = Rz*[r_x_shift;r_y_shift;z];
            rv(1)=rv(1)+center_of_rot;
            rv(2)=rv(2)+center_of_rot;
            X(i)=rv(1);Y(i)=rv(2);Z(i)=rv(3);
        	%% convert fractions to whole number indicies and values
        	%% split values across indicies according to their fractions        	
       	    x_max=ceil(rv(1));
       	    x_min=floor(rv(1));
       	    y_max=ceil(rv(2));
       	    y_min=floor(rv(2));
        	for x2=1:2
        		for y2=1:2
	        		if x_min > 0 && x_max <= grid_size && ...
	               	   y_min > 0 && y_max <= grid_size
	               	   if x2==1 && y2 ==1
	               	   	 ext_dir_initial2(x_min,y_min)= ...
	               	   	 ext_dir_initial2(x_min,y_min)+rv(3)*.5* ...
	               	   	 (1-mod(rv(1),1)+1-mod(rv(2),1))/2;
	               	   end
	               	   if x2==2 && y2 ==1
	               	   	 ext_dir_initial2(x_max,y_min)= ...
	               	   	 ext_dir_initial2(x_max,y_min)+rv(3)*.5* ...
	               	   	 (mod(rv(1),1)+1-mod(rv(2),1))/2;
	               	   end
	               	   if x2==1 && y2 ==2
	               	   	 ext_dir_initial2(x_min,y_max)= ...
	               	   	 ext_dir_initial2(x_min,y_max)+rv(3)*.5* ...
	               	   	 (1-mod(rv(1),1)+mod(rv(2),1))/2;
	               	   end
	               	   if x2==2 && y2 ==2
	               	   	 ext_dir_initial2(x_max,y_max)= ...
	               	   	 ext_dir_initial2(x_max,y_max)+rv(3)*.5* ...
	               	   	 (mod(rv(1),1)+mod(rv(2),1))/2;
	               	   end
	               	end
	            end
        	end        	
        end
    end
end

function ext_dir_initial3=shift_weights(po,i,ext_dir_initial2)
	% apply shifting to synapse weights matrix

	grid_size=po(5);grid_size_target=po(8);ext_dir_initial3=zeros(grid_size);
	start_x_shift=po(9);start_y_shift=po(10);

	x_shift = mod(i,grid_size_target);
	y_shift = floor(i/grid_size_target);

	ti = (grid_size^2)-1;
	for i2=0:ti
		x = mod(i2,grid_size)+1;
		y = floor(i2/grid_size)+1;
		x2 = x + x_shift;
		y2 = y + y_shift;
		if x2 > ti
			x2 = x2 - ti;
		elseif x2 < 1
			x2 = x2 + ti;
		end
		if y2 > ti
			y2 = y2 - ti;
		elseif y2 < 1
			y2 = y2 + ti;
		end
		ext_dir_initial3(x2,y2)=ext_dir_initial2(x,y);
	end
end

function ext_dir_initial4=crop_weights(po,ext_dir_initial3)
	% apply rotation to synapse weights matrix

	grid_size=po(5);grid_size_target=po(8);ext_dir_initial4=zeros(grid_size_target);

    %% crop larger distribution into smaller target sized one
    target_offset = (grid_size-grid_size_target)/2;
    for y=1:grid_size_target
        for x=1:grid_size_target
        	x2 = target_offset + x;
        	y2 = target_offset + y;
        	ext_dir_initial4(x,y)=ext_dir_initial3(x2,y2);
        end
    end
end

function ext_dir_initial=nrn_syn_wts(x_shift,y_shift,p,po,ext_dir_initial);
	% generate all synapse weights for one neuron

   	grid_size=po(5);iter=po(6);ext_dir_initial=[];
	for y=1:grid_size
		for x=1:grid_size
			z=field_tile(x,y,x_shift,y_shift,p,po);
			ext_dir_initial = [ext_dir_initial,z];
		end
	end	
end

function z=field_tile(x,y,x_shift,y_shift,p,po)
	% tiles bump distributions
	% generate <inter> number of tiled bump functions

	grid_size=po(5);grid_size_target=po(8);iter=po(6);tf=po(7);z=0;
	htf=po(11);vtf=po(12);
	for i=0:(iter-1)
		for j=0:(iter-1)
            tv=(iter-1)/2; % tiling variable
			x_shift2 = (-(grid_size*tv*tf)+i*(grid_size*tf))+x_shift;
			y_shift2 = (-(grid_size*tv*tf)+j*(grid_size*tf))+y_shift;
			
			y_shift2 = y_shift2*htf;
			if mod(j,2) ~= 0
				x_shift2 = x_shift2 + grid_size_target*vtf;
			end
			
			z=z+field(x,y,x_shift2,y_shift2,p);
		end
	end
end

function z=field(x,y,x_shift,y_shift,p)
	% firing bumps function
	x=(x-x_shift);
	y=(y-y_shift);
	p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);fsf=p(9);
	% gaussian function
	z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4) ...
		-(y.^p5/p6)))*p7)-p8;
	z=z*fsf; % scaling factor
	if z < 0
		z = 0; % negative values rectifier
	end
end