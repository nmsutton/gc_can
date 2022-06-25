% references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point

% run options
show_plot = 0;
write_to_file = 0;
sample_matrix = 1;

% params
output_filename = "synapse_weights.cpp";
output_file = 0;
if write_to_file
	output_file = fopen(output_filename,'w');
end
grid_size = 90.0;
grid_size_target = 30; % target grid size for neuron weights
total_nrns = (grid_size^2);%35;%(grid_size^2);% total neurons
iter = 5; % iterations to run cent-surr function. i.e., number of tiled cent-surr dist. along an axis. e.g., value 5 creates 5x5 cent-surr circles in the weights plot.
start_x_shift = grid_size/2 + 1;%1;%28;
start_y_shift = grid_size/2 + 1;%1;%-4;%28;
p1=.68;p2=2;p3=2;p4=30;p5=p3;p6=p4;p7=0.20;
p8=.135;p9=2;p10=2;p11=2;p12=30;p13=p11;p14=p11;p15=p12;p16=1.08;p17=0.0058;
p=[p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17];
tiling_fraction=0.2;%0.5; % fraction of standard tiling distance between bumps
po=[show_plot,write_to_file,sample_matrix,output_file,grid_size,iter,tiling_fraction];
comb_syn_wts=[];
[X,Y] = meshgrid(1:1:grid_size);
Z=zeros(grid_size);
% rotation variables
a=45; % angle
a=a/360 * pi*2; % convert to radians
Rx = [1 0 0; 0 cos(a) -sin(a); 0 sin(a) cos(a)];
Ry = [cos(a) 0 sin(a); 0 1 0; -sin(a) 0 cos(a)];
Rz = [cos(a) -sin(a) 0; sin(a) cos(a) 0; 0 0 1];

% plot
if show_plot
	for x=1:grid_size
		for y=1:grid_size
			z=cent_surr_tile(x,y,start_x_shift,start_y_shift,p,po);
			Z = [z, Z];
		end
	end
	Z = reshape(Z,grid_size,grid_size);
	surf(X,Y,Z);
	shading interp
	axis tight
    view(2) % 2d plot instead of 3d
end

% write to file and create matrix
if write_to_file
	for i=0:(total_nrns-1)
		pdx = mod(i,grid_size);
		pdy = floor(i/grid_size);
		pd=get_pd(pdx,pdy);
		x_pd_bias = 0;
		y_pd_bias = 0;
		if pd=='u'
			y_pd_bias=2;
		elseif pd=='d'
			y_pd_bias=-2;
		elseif pd=='l'
			x_pd_bias=2;%1;
		elseif pd=='r'
			x_pd_bias=-2;%-1;
		end
		y_shift=start_x_shift+pdy+x_pd_bias; % x and y values are intentially flipped
		x_shift=start_y_shift+pdx+y_pd_bias; % here for an orientation fix

		synapse_weights=nrn_syn_wts(x_shift,y_shift,p,po);
		comb_syn_wts=[comb_syn_wts; synapse_weights];

		if (mod(i,grid_size*3)==0)
			fprintf("%.3g%% completed\n",i/total_nrns*100);
		end
	end
	disp("writing to file");
	fprintf(output_file,'static const vector<vector<double>> mex_hat{{');
	for i=0:(total_nrns-1)
		for j=1:length(comb_syn_wts)
			fprintf(output_file,'%f',comb_syn_wts(i+1,j));
			if j ~= length(comb_syn_wts)
				fprintf(output_file,',');
			end
		end
		if i ~= (total_nrns-1)
			fprintf(output_file,'},\n{');
		end	
		if (mod(i,grid_size*3)==0)
			fprintf("%.3g%% completed\n",i/total_nrns*100);
		end
	end
	fprintf(output_file,'}};');
end
if sample_matrix
	po(2)=0; % turn off file writing for sample
	synapse_weights = nrn_syn_wts(start_x_shift,start_y_shift,p,po);
	synapse_weights = reshape(synapse_weights,grid_size,grid_size);
    synapse_weights2 = zeros(grid_size);
    for y=1:grid_size
        for x=1:grid_size
            i=((y-1)*grid_size)+x;
            z=synapse_weights(i); 
            center_of_rot=grid_size/2;
            r_x_shift = x - center_of_rot;
            r_y_shift = y - center_of_rot;         
            rv = Rz*[r_x_shift;r_y_shift;z];
            rv(1)=rv(1)+center_of_rot;
            rv(2)=rv(2)+center_of_rot;
            X(i)=rv(1);Y(i)=rv(2);Z(i)=rv(3);
            if floor(rv(1)) > 0 && floor(rv(1)) < grid_size && ...
               floor(rv(2)) > 0 && floor(rv(2)) < grid_size
            	synapse_weights2(floor(rv(1)),floor(rv(2)))=rv(3);
        	end
        end
    end
    target_offset = grid_size_target/grid_size*grid_size;
    synapse_weights3=zeros(grid_size_target);
    for y=1:grid_size_target
        for x=1:grid_size_target
        	x2 = target_offset + x;
        	y2 = target_offset + y;
        	i=((y2-1)*grid_size)+x2; % larger grid index
        	i2=((y-1)*grid_size_target)+x; % target smaller grid index
        	synapse_weights3(i2)=synapse_weights2(i);
        end
    end
end

if write_to_file
	fclose(output_file);
end

function synapse_weights=nrn_syn_wts(x_shift,y_shift,p,po,synapse_weights);
	% generate all synapse weights for one neuron

   	grid_size=po(5);iter=po(6);synapse_weights=[];
	for y=1:grid_size
		for x=1:grid_size
			z=cent_surr_tile(x,y,x_shift,y_shift,p,po);
			synapse_weights = [synapse_weights,z];
		end
	end	
end

function z=cent_surr_tile(x,y,x_shift,y_shift,p,po)
	% tiles center-surround distributions
	% generate <inter> number of tiled center surround functions
	% for the synaptic weight distribution

	grid_size=po(5);iter=po(6);tf=po(7);z=0;
	for i=0:(iter-1)
		for j=0:(iter-1)
            tv=(iter-1)/2; % tiling variable
			x_shift2 = (-(grid_size*tv*tf)+i*(grid_size*tf))+x_shift;
			y_shift2 = (-(grid_size*tv*tf)+j*(grid_size*tf))+y_shift;
			z=z+cent_surr(x,y,x_shift2,y_shift2,p);
		end
	end
end

function z=cent_surr(x,y,x_shift,y_shift,p)
	% center-surround function
	x=(x-x_shift);
	y=(y-y_shift);
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

function pd = get_pd(x, y)
    % find neuron preferred direction
	if (mod(y,2) == 0)
		if (mod(x,2) == 0)
			pd = 'l';
		else 
			pd = 'r';
        end
    else
		if (mod(x,2) == 0)
			pd = 'u';
        else
			pd = 'd';	
        end
    end
end