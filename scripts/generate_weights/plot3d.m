% reference: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf

% params
show_plot = 1;
write_to_file = 1;
create_matrix = 1;

output_filename = "synapse_weights.cpp";
if write_to_file
	output_file = fopen(output_filename,'w');
end
grid_size = 30.0;
iter = 3; % iterations to run function
x_shift = 28;%15.0;
y_shift = 28;%15.0;
p1=.68;p2=2;p3=2;p4=70;p5=p3;p6=p4;p7=0.19;
p8=.135;p9=2;p10=2;p11=2;p12=70;p13=p11;p14=p11;p15=p12;p16=1.08;p17=0.0055;
p=[p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17];
synapse_weights=[];
po=[show_plot,write_to_file,create_matrix,output_file,grid_size,iter];

% plot
if show_plot
	[X,Y] = meshgrid(1:1:grid_size);
	Z=[];
	for x=1:grid_size
		for y=1:grid_size
			z=cent_surr_tile(x,y,x_shift,y_shift,p,po);
			Z = [z, Z];
		end
	end
	Z = reshape(Z,30,30);
	surf(X,Y,Z);
	shading interp
	axis tight
end

% write to file and create matrix
if write_to_file || create_matrix
	%{
	for x=1:grid_size
		for y=1:grid_size
			z=cent_surr_tile(x,y,x_shift,y_shift,p,po);
			if write_to_file
				fprintf(output_file,'%f',z);
				if x ~= grid_size && y ~= grid_size
					fprintf(output_file,',');
				end
			end
			if create_matrix
				synapse_weights = [z, synapse_weights];
			end
		end
	end	
	%}
	synapse_weights=nrn_syn_wts(x,y,x_shift,y_shift,p,po,synapse_weights);
end
if create_matrix
	synapse_weights = reshape(synapse_weights,30,30);
end

if write_to_file
	fclose(output_file);
end

function synapse_weights=nrn_syn_wts(x,y,x_shift,y_shift,p,po,synapse_weights);
	% generate all synapse weights for one neuron

	write_to_file=po(2);create_matrix=po(3);output_file=po(4);
   	grid_size=po(5);iter=po(6);

	for x=1:grid_size
		for y=1:grid_size
			z=cent_surr_tile(x,y,x_shift,y_shift,p,po)
			if write_to_file
				fprintf(output_file,'%f',z);
				if x ~= grid_size && y ~= grid_size
					fprintf(output_file,',');
				end
			end
			if create_matrix
				synapse_weights = [z, synapse_weights];
			end
		end
	end	
end

function z=cent_surr_tile(x,y,x_shift,y_shift,p,po)
	% tiles center-surround distributions
	% generate <inter> number of tiled center surround functions
	% for the synaptic weight distribution

	grid_size=po(5);iter=po(6);
	z=0;
	for i=0:(iter-1)
		for j=0:(iter-1)
			x_shift2 = (-grid_size+i*grid_size)+x_shift;
			y_shift2 = (-grid_size+j*grid_size)+y_shift;
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
			pd = 'd';
		else 
			pd = 'r';
        end
    else
		if (mod(x,2) == 0)
			pd = 'l';
        else
			pd = 'u';	
        end
    end
end