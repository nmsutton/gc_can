% view weight design options

weights_type=["custom_tiled","full_tiled"];
%selection="full_tiled";
selection="custom_tiled";

x_size_in = 60;
x_size = 40;

if selection == weights_type(1)
    use_nowp = 1; % select to use some non-wrapping centroids
    x_srt = 31;%30;%8;%31;%8;
    y_srt = 30;%17;%7;%30;%7;  
    cent_x=[];
    cent_y=[]; 
%     cent_x=[0, -8, 8];
% 	  cent_y=[0, -12, 12];
%     cent_x=[0, -8,   6,   6, 14, 36, -14];
%     cent_y=[0, -12, 12, -12,  0, 11,   0];    
%     cent_x=[0, -8,   6,   6, 14, 36, -14, -8,  -20];
%     cent_y=[0, -12, 12, -12,  0, 11,   0, 12,  -12];    
    cent_x=[0, -8,   6,   6, 14, 36, -14, -8];
    cent_y=[0, -12, 12, -12,  0, 11,   0, 12]; 
    cent_x_nowp=[0, 14, -14]; % centroid with no wrapping
    cent_y_nowp=[-24, -24, -24];
    
    % add starting positions to centroids
    for i=1:length(cent_x)
	    cent_x(i)=cent_x(i)+x_srt;
	    cent_y(i)=cent_y(i)+y_srt;
    end
    
    % add more centroids for neural layer wrap around effect
    [cent_x,cent_y]=add_cents(cent_x, cent_y, x_size, x_size_in);

    % add centroids with no wrapping
    if use_nowp
        for i=1:length(cent_x_nowp)
            cent_x=[cent_x,cent_x_nowp(i)+x_srt];
            cent_y=[cent_y,cent_y_nowp(i)+y_srt];
        end
    end
end

if selection == weights_type(2)
    x_sft = 62;
    y_sft = 59;
    x_srt = -x_sft+8;
    y_srt = -y_sft+7;
    ring_size=14;
    tiling_scale=1.7;
    spacing_scale=0.333;
    x_tiles=20;
    y_tiles=20;
    cent_x=[];
    cent_y=[];

    for i=1:y_tiles
        for j=1:x_tiles
            new_x=floor(i*((ring_size)*tiling_scale*spacing_scale))+x_srt;
            new_y=floor(j*((ring_size)*tiling_scale))+y_srt;
            if mod(i,2) == 0 new_y = floor(new_y - (((ring_size)*tiling_scale)/2)); end
            if new_x>0 && new_x<=x_size_in && new_y>0 && new_y<=x_size_in 
	            cent_x=[cent_x;new_x];
	            cent_y=[cent_y;new_y];
	        end
        end
    end
end

plot_cent=zeros(x_size, x_size);

for i=1:length(cent_x)
	cent_i=(cent_y(i)*x_size_in)+cent_x(i);
	cent_i=wrap_around(cent_i, x_size_in);
    %disp(cent_i);
	plot_cent=[plot_cent+reshape(comb_syn_wts(cent_i,:),x_size,x_size)];
end
imagesc(plot_cent);

function cent_i=wrap_around(cent_i, x_size_in)
	if cent_i < 1 cent_i = cent_i + (x_size_in*x_size_in); end
	if cent_i >= (x_size_in*x_size_in) cent_i = cent_i - (x_size_in*x_size_in); end
end

function [cent_x,cent_y]=add_cents(cent_x, cent_y, x_size, x_size_in)
	cent_size=length(cent_x);
	for i=1:cent_size
		for j=1:3
			for k=1:3
				new_x=cent_x(i)+(-x_size+(x_size*k));
				new_y=cent_y(i)+(-x_size+(x_size*j));
				if (j == 1 && k == 1) %{ skip %} ; end
				elseif new_x>=0 && new_x<x_size_in && ...
				       new_y>=0 && new_y<x_size_in
				    cent_x=[cent_x,new_x];
					cent_y=[cent_y,new_y];
				end
			end
		end
	end
end