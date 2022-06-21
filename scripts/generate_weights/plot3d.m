% reference: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf

% params
show_plot = 1;
write_to_file = 1;
create_matrix = 1;

output_filename = "synapse_weights.cpp";
grid_size = 30.0;
iter = 3; % iterations to run function
x_shift = 28;%15.0;
y_shift = 30;%15.0;
p1=.68;p2=2;p3=2;p4=70;p5=p3;p6=p4;p7=0.19;
p8=.135;p9=2;p10=2;p11=2;p12=70;p13=p11;p14=p11;p15=p12;p16=1.08;p17=0.0055;
synapse_weights=[];

% plot
if show_plot
	[X,Y] = meshgrid(1:1:grid_size);
	Z=[];
	for x=1:grid_size
		for y=1:grid_size
			z=0;
			for i=0:(iter-1)
				for j=0:(iter-1)
					x_shift2 = (-grid_size+i*grid_size)+x_shift;
					y_shift2 = (-grid_size+j*grid_size)+y_shift;
					z=z+cent_surr(x,y,x_shift2,y_shift2,p1,p2,p3,p4,p5, ...
					        p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17);
				end
			end
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
	if write_to_file
		output_file = fopen(output_filename,'w');
	end
	for x=1:grid_size
		for y=1:grid_size
			z=0;
			for i=0:(iter-1)
				for j=0:(iter-1)
					x_shift2 = (-grid_size+i*grid_size)+x_shift;
					y_shift2 = (-grid_size+j*grid_size)+y_shift;
					z=z+cent_surr(x,y,x_shift2,y_shift2,p1,p2,p3,p4,p5, ...
					        p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17);
				end
			end
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
	if write_to_file
		fclose(output_file);
	end
end
if create_matrix
	synapse_weights = reshape(synapse_weights,30,30);
end

function z=cent_surr(x,y,x_shift,y_shift,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11, ...
					 p12,p13,p14,p15,p16,p17)
	% center-surround function
	x=(x-x_shift);
	y=(y-y_shift);
	z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4) ...
		-(y.^p5/p6)))*p7-(p8/sqrt(p9*pi) ...
		.*exp(-(p10*x.^p11/p12)-(p13*y.^p14/p15)))*p16)-p17;
	%z = x;
	if z < 0
		z = 0;
	end
	%z=((3.4/sqrt(3*3.14)) * exp(-(6*x2.^2)-(6*y2.^2)/30))*4;
	%x2=(x+x_shift);
	%y2=(y+y_shift);
	%z=z+((3.4/sqrt(3*3.14)) * exp(-(6*x2.^2)-(6*y2.^2)/30))*4;
end