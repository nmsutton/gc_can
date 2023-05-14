% references: https://www.mathworks.com/matlabcentral/answers/180778-plotting-a-3d-gaussian-function-using-surf
% https://www.mathworks.com/help/symbolic/rotation-matrix-and-transformation-matrix.html
% https://www.mathworks.com/matlabcentral/answers/430093-rotation-about-a-point

% run options
sample_matrix = 0;
write_to_csv = 1; % needed for running on supercomputer
write_to_cpp = 0; % alternative file for running locally (not supercomputer)
only_show_plot_preview = 0;
show_3d_plot = 0;

% params
csv_filename = "synapse_weights.csv";
cpp_filename = "synapse_weights.cpp";
output_cpp = 0; output_csv = 0; % these are always init as 0
if write_to_csv output_csv = fopen(csv_filename,'w'); end
if write_to_cpp output_cpp = fopen(cpp_filename,'w'); end
grid_size_ref = 50;%60;%44; % reference grid size to position shift the center-surround distro for each neuron
grid_size_target = 40;%42;%40;%36;%42; % target grid size for neuron weights
total_nrns = grid_size_ref^2;%(grid_size_target^2);%35;%(grid_size^2);% total neurons
if only_show_plot_preview total_nrns = 3; end
grid_size = grid_size_ref*3;%90;
iter = 13; % iterations to run cent-surr function. i.e., number of tiled cent-surr dist. along an axis. e.g., value 5 creates 5x5 cent-surr circles in the weights plot.
start_x_shift = (grid_size/2) - 24;%29;%24;%5;%24;%19;%26;%6;%26;%19;%20;%19;%17;%44;%20;%50;%44;%- 44;%1;%28; -2 = 2 down
start_y_shift = (grid_size/2) - 24;%29;%24;%5;%24;%19;%26;%6;%26;%19;%20;%19;%17;%44;%20;%50;%44;%- 44;%1;%-4;%28; +2 = 2 left
if only_show_plot_preview start_x_shift = (grid_size/2) - 4; end
if only_show_plot_preview start_y_shift = (grid_size/2) - 4; end
rescale_weights = 1; % rescale weights to match highval
shift_down = 1; % apply subtraction to all weight values to shift them down
filter_lowval = 1; % avoid creating weights below this value
highval = 0.00681312463724531;
syn_wgt_shift = 0.001275510204;
lowval_thres = 0.0;%0.0;%0.004;%0.0;%0.001;
conversion_mult = 114.7*1.574395603;
r_s=0.8*.9;%1;%1.1;%1;%.9;%.8;%.8;%1.01;%1.05;%1.1;%0.9;%1.1;%1;%10/42;%20/42;%1; % ring scale
p1=.54;%.6;%.68;%.54;%.5;%.54;%.68;%.54;%.58;%.62;%.68;%10;%20;%.68;%20;%20;%.68;
p2=2;p3=2;
% center size
p4=r_s*52*1.2;%*38*1.6;%*180;%38*1.6;%200;%190;%160;%130;%90;%r_s*52;%35;%45;%52;%40;%70;%130;%38;%*2.5*1.3;%.55;%.7;%4;%2;%2;%2.5;%2;%*1.4;%1.344;%*2.7*(14/20);%1.4;%*.5; 
% center size
p8=r_s*.135*1.02;%*0.135;%*210;%0.135;%230;%220;%190;%160;%70;%r_s*.135*1.02;%r_s*.135*1.07;%1;%.87;%.135*.9;%1;%.97;%.99;%.11;%.13;%.12;%.14;%.12;%.22;%.2;%.25;%.135; 
% surround size
p7=r_s*0.19;%*0.15;%*0.5;%0.15;%0.13;%0.15;%.3;%0.15;%r_s*0.19;%0.18;%0.19;%0.183;%0.19;%0.2;%0.2;%*1.1*.97;%1.04;%1.05;%1.15;%1;%4;%.7;%.9;%.7;%0.174*1.4;%*2.4*(14/20);%1.4;%*.75;%0.15; 
% surround size
p16=r_s*1.08*.95;%0.81;%*0.3;%0.81;%0.3;%1.08*.95*r_s;%1.08*1.03;%1.03;%.95;%1;%.97;%.99;%0.81;%*1.1*.97;%1.04;%1.05;%1.15;%1;%4;%.7;%.9;%.7;%0.9396*1.4*.9;%*3*(14/20);%1.4;%*.75;%0.81; 
p5=p3;p6=p4;p9=2;p10=2;p11=2;p12=p4;p13=p11;p14=p11;p15=p12;p17=0.0058;
p=[p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17];
tiling_fraction=0.33333333333*1;%1.04*(40/42)*(40/44);%(126/120);%1;%(42/30);%1.05;%*1.04;%0.1;%0.33333333333;%1;%0.33;%0.5; % fraction of standard tiling distance between bumps
po=[show_3d_plot,write_to_cpp,sample_matrix,output_cpp,grid_size,iter,tiling_fraction, ...
    grid_size_target,start_x_shift,start_y_shift,grid_size_ref];
comb_syn_wts=[];
[X,Y] = meshgrid(1:1:grid_size);
Z=zeros(grid_size);
% rotation variables
a=0;%125; % angle
a=a/360 * pi*2; % convert to radians
Rz = [cos(a) -sin(a) 0; sin(a) cos(a) 0; 0 0 1]; % rotate along Z axis. See references for other axis code if wanted.

% plot
if show_3d_plot
	synapse_weights = nrn_syn_wts(start_x_shift,start_y_shift,highval,p,po);
	%[synapse_weights2, synapse_weights3]=rotate_weights(po,Rz,synapse_weights);
	synapse_weights2=reshape(synapse_weights,grid_size,grid_size);
	[X,Y] = meshgrid(1:1:grid_size_target);
	Z = synapse_weights(990,:);
	surf(X,Y,Z);
	shading interp
	axis tight
    view(2) % 2d plot instead of 3d
end

% write to file and create matrix
if write_to_csv || write_to_cpp
	synapse_weights=nrn_syn_wts(start_x_shift,start_y_shift,highval,p,po);
	for i=0:(total_nrns-1)
		synapse_weights2=reshape(synapse_weights,grid_size,grid_size);
		synapse_weights3=shift_weights(po,i,synapse_weights2);
		synapse_weights4=crop_weights(po,synapse_weights3);
		comb_syn_wts=[comb_syn_wts; reshape(synapse_weights4,1,grid_size_target^2)];

		if (mod(i,grid_size_target*3)==0)
			fprintf("%.3g%% completed\n",i/total_nrns*100);
		end
	end
	if rescale_weights == 1
		weight_scale = highval/max(max(comb_syn_wts)); % difference between target highval and original matrix highval
		comb_syn_wts = comb_syn_wts * weight_scale; % multiplier scale
        if shift_down == 1
            comb_syn_wts = comb_syn_wts - syn_wgt_shift; % subtraction shift
        end
        if filter_lowval == 1
            comb_syn_wts(find(comb_syn_wts<lowval_thres))=0; % non-negative rectifier
        end
        comb_syn_wts = comb_syn_wts * conversion_mult; % conversion for g constant
    end
	disp("writing to file");
	if output_cpp fprintf(output_cpp,'static const vector<vector<double>> mex_hat{{'); end
	for i=0:(total_nrns-1)
		for j=1:size(comb_syn_wts,2)
			if output_cpp fprintf(output_cpp,'%f',comb_syn_wts(i+1,j)); end
            if output_csv fprintf(output_csv,'%f',comb_syn_wts(i+1,j)); end
			if j ~= size(comb_syn_wts,2)
				if output_cpp fprintf(output_cpp,','); end
                if output_csv fprintf(output_csv,','); end
			end
		end
		if i ~= (total_nrns-1)
			if output_cpp fprintf(output_cpp,'},\n{'); end
            if output_csv fprintf(output_csv,'\n'); end
		end	
		if (mod(i,grid_size_target*3)==0)
			fprintf("%.3g%% completed\n",i/total_nrns*100);
		end
	end
	if output_cpp fprintf(output_cpp,'}};'); end
    if only_show_plot_preview
        imagesc(reshape(comb_syn_wts(1,1:end),grid_size_target,grid_size_target));
    end
end
if sample_matrix
	po(2)=0; % turn off file writing for sample
    start_y_shift = start_y_shift + 4;
    start_x_shift = start_x_shift - 1;
	synapse_weights2=reshape(synapse_weights,grid_size,grid_size);
	synapse_weights3=shift_weights(po,1,synapse_weights2);
	synapse_weights4=crop_weights(po,synapse_weights3);
    imagesc(synapse_weights4);
end

if write_to_csv fclose(output_csv); end
if write_to_cpp fclose(output_cpp); end

function synapse_weights3=shift_weights(po,i,synapse_weights2)
	% apply pd-based shifting to synapse weights matrix

	grid_size=po(5);grid_size_target=po(8);synapse_weights3=zeros((44*3),grid_size);
	start_x_shift=po(9);start_y_shift=po(10);grid_size_ref=po(11);

	pdx = mod(i,grid_size_ref);
	pdy = floor(i/grid_size_ref);
	y_shift=pdy; % x and y values are intentially flipped
	x_shift=pdx; % here for an orientation fix

	%grid_size2=44*3;
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
		
		synapse_weights3(x2,y2)=synapse_weights2(x,y);
	end
end

function synapse_weights4=crop_weights(po,synapse_weights3)
	% apply rotation to synapse weights matrix

	grid_size=po(5);grid_size_target=po(8);synapse_weights4=zeros(grid_size_target);

    %% crop larger distribution into smaller target sized one
    target_offset = (grid_size-grid_size_target)/2;
    for y=1:grid_size_target
        for x=1:grid_size_target
        	x2 = target_offset + x;
        	y2 = target_offset + y;
        	synapse_weights4(x,y)=synapse_weights3(x2,y2);
        end
    end
end

function synapse_weights=nrn_syn_wts(x_shift,y_shift,highval,p,po,synapse_weights);
	% generate all synapse weights for one neuron

   	grid_size=po(5);iter=po(6);synapse_weights=[];
	for y=1:grid_size
		for x=1:grid_size
			z=0;
			for i=0:(iter-1)
				for j=0:(iter-1)
					z=z+cent_surr(x,y,x_shift,y_shift,highval,p);
				end
			end
			synapse_weights = [synapse_weights,z];
		end
	end	
end

function z=cent_surr(x,y,x_shift,y_shift,highval,p)
	% center-surround function
	x=(x-x_shift);
	y=(y-y_shift);
	p1=p(1);p2=p(2);p3=p(3);p4=p(4);p5=p(5);p6=p(6);p7=p(7);p8=p(8);p9=p(9);
	p10=p(10);p11=p(11);p12=p(12);p13=p(13);p14=p(14);p15=p(15);p16=p(16);p17=p(17);
	% difference of gaussians function creates the center-surround
	z=((p1/sqrt(p2*pi).*exp(-(x.^p3/p4) ...
		-(y.^p5/p6)))*p7-(p8/sqrt(p9*pi) ...
		.*exp(-(p10*x.^p11/p12)-(p13*y.^p14/p15)))*p16)-p17;
    z=z*.035;
    if z < 0
        z = 0;
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