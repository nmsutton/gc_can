% weight design plotting and stats

selection="custom_tiled";
%selection="full_tiled";
weights_type=["custom_tiled","full_tiled"];
x_size_in = 50;%60;
x_size = 40;
x_srt = ((x_size_in-x_size)/2)+1;%6;%6;%8;%30;%8;%31;%8;
y_srt = ((x_size_in-x_size)/2);%5;%5;%7;%17;%7;%30;%7; 
x_srt = 31;
y_srt = 30;
% x_srt = 18;
% y_srt = 5;
create_plot = 1;
report_stats = 0;
use_nowp = 0; % select to use some non-wrapping centroids
grc_layer = x_size*x_size;
in_layer = x_size_in*x_size_in;
cent_x=[]; cent_y=[]; 
x_srt_stats=x_srt; % starting position for stat reporting
y_srt_stats=y_srt;

% select centroids
%     cent_x=[0];
% 	  cent_y=[0];
%     cent_x=[0, -8,  8];
%     cent_y=[0, -12, 12];
%     cent_x=[0, 6, 6];
% 	  cent_y=[0, -12, 12];
%     cent_x=[0, -8,  8, 6,   6];
%     cent_y=[0, -12, 12, 12, -12]; 
%     cent_x=[0, -8,   6,   6, 14, 36, -14];
%     cent_y=[0, -12, 12, -12,  0, 11,   0];    
%     cent_x=[0, -8,   6,   6, 14, 36, -14, -8,  -20];
%     cent_y=[0, -12, 12, -12,  0, 11,   0, 12,  -12];    
%     cent_x=[0, -8,   6,   6, 14, 36, -14, -8];
%     cent_y=[0, -12, 12, -12,  0, 11,   0, 12];
%     cent_x=[0, -8,  8, 6,   6, 14, -14, 36];
%     cent_y=[0, -12, 12, 12, -12, 0,   0, 11];
%     cent_x=[0, -8,  8, 6,   6,  14, -14, -8];
%     cent_y=[0, -12, 12, 12, -12,  0,   0, 12];
%     cent_x=[0, -7,  7, -7, 7];
%     cent_y=[0, -12, 12, 12, -12];
%     cent_x=[0,  -8,  8,   6, -6, 14, -14];
%     cent_y=[0, -12, 12, -12, 12,  0,   0];
%     cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22];
%     cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12];
%     cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22,  20, 20];
%     cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12, -12, 12];
%     cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22, 28, -28];
%     cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12,  0,   0];
%     cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, 22];
%     cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12];
% cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22,  22, 22, -28, 28];
% cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12, -12, 12,   0,  0];
% cent_x=[0, -20,  20]; 
% cent_y=[0, -10, -10];
% cent_x=[0, -20,  20, -20,  20]; 
% cent_y=[0, -10, -10,  10,  10];
% cent_x=[0,  12, -12, 24, -24, -18,  -6,   6,  18, -18,   6, -6, 18, 0,  12, -12, 24, -24,   0,  12, -12,  24, -24];
% cent_y=[0,   0,   0,  0,   0, -10, -10, -10, -10,  10,  10, 10, 10, 20, 20,  20, 20,  20, -20, -20, -20, -20, -20];
% cent_x=[0,  12, -12, 24, -24,  -6,   6,   6, -6, 0,  12, -12, 24, -24,   0,  12, -12];
% cent_y=[0,   0,   0,  0,   0, -10, -10,  10,  10, 20, 20,  20, 20,  20, -20, -20, -20];
%     cent_x=[0,  -7,  7];
% 	cent_y=[0, -11, 11];
% cent_x=[0,  11, -11, 22, -22,  -7,   7,   7, -7, 0,  11, -11, 22, -22,   0,  11, -11];
% cent_y=[0,   0,   0,  0,   0, -11, -11,  11,  11, 22, 22,  22, 22,  22, -22, -22, -22];
% cent_x=[0, -14, 14, -28, 28,  7, -7,-21,  7,   -7, -21,  0, 14, -14,  0,   14, -14];
% cent_y=[0,   0,  0, 0, 0, 11, 11, 11, -11, -11, -11, 22, 22,  22, -22, -22, -22];
% cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22,  22, 22, -28, 28];
% cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12, -12, 12,   0,  0];
% cent_x=[0,  -8,  8,   6, -6, 14, -14];
% cent_y=[0, -12, 12, -12, 12,  0,   0];
% cent_x=[0, 14, -14, -28, 28, 8, -6, -20, 22, -34, 36,   6,  -8, -22,  20, 34,  36];
% cent_y=[0,  0,   0,   0,  0, 12, 12,  12, 12, 12, 12, -12, -12, -12, -12, -12, -12];
% cent_x=[0, 14, -14, -28, 28, 7, -7, -21, 21, -35, 35,   7,  -7, -21,  21, 35,  35];
% cent_y=[0,  0,   0,   0,  0, 12, 12,  12, 12, 12, 12, -12, -12, -12, -12, -12, -12];
% cent_x=[0, 14, -14, -28, 28, 8, -6, -22, 22, -36, 36,   6,  -8, -22,  22, 36,  36];
% cent_y=[0,  0,   0,   0,  0, 12, 12,  12, 12, 12, 12, -12, -12, -12, -12, -12, -12];
% cent_x=[0, -2,   2, -14, 14];
% cent_y=[0, -10, 10,  -4,  4];
% cent_x=[0, 0,   0, -14, 14, -14, 14, 0, -26, 26];
% cent_y=[0, -10, 10,  -6,  6, 6, -6, 20, -18, 22];
% cent_x=[0, -2,   2, -14, 14, -12, 12, -4, -16, 16];
% cent_y=[0, -10, 10,  -4,  4, 8, -8, -20, -14, 14];
% cent_x=[0,  0,   0, -14, 14, -14, 14, 0, -26, 26, -14, 14, -14, 14];
% cent_y=[0, -10, 10,  -6,  6, 6, -6, 20, -18, 22, 16, 16, -16, -16];
% cent_x=[0,  12, -12, 24, -24, -18,  -6,   6,  18, -18,   6, -6, 18];
% cent_y=[0,   0,   0,  0,   0, -10, -10, -10, -10,  10,  10, 10, 10];
% cent_x=[0,  12, -12, 24, -24, -18,  -6,   6,  18, -18,   6, -6, 18,  0];
% cent_y=[0,   0,   0,  0,   0, -10, -10, -10, -10,  10,  10, 10, 10, 20];
% cent_x=[0,  12, -12, 24, -24, -18,  -6,   6,  18, -18,   6, -6, 18,  0, -12, 12];
% cent_y=[0,   0,   0,  0,   0, -10, -10, -10, -10,  10,  10, 10, 10, 20,  20, 20];
% cent_x=[0,  12, -12, 24, -24, -18,  -6,   6,  18, -18,   6, -6, 18,  0, -12, 12, -24];
% cent_y=[0,   0,   0,  0,   0, -10, -10, -10, -10,  10,  10, 10, 10, 20,  20, 20, 20];
% cent_x=[0,  12, -12, 24, -18,  -6,   6, -18,   6, -6, 12, 0, -12];
% cent_y=[0,   0,   0,  0, -10, -10, -10,  10,  10, 10, 20, 20, 20];
% cent_x=[0,  12, -12,  -6,   6,  6, -6, 12, 0, -12,  12,   0, -12];
% cent_y=[0,   0,   0, -10, -10, 10, 10, 20, 20, 20, -20, -20, -20];
% cent_x=[0,  -8,  8,   6, -6, 14, -14, -22, -22,  22, 22, -28, 28];
% cent_y=[0, -12, 12, -12, 12,  0,   0, -12,  12, -12, 12,   0,  0];
% cent_x=[0, -8,  8];
% cent_y=[0, -12, 12];
% cent_x=[0, -6,  6];
% cent_y=[0, -10, 10];
cent_x=[0, -6,  6, 6, -6, 12, -12];
cent_y=[0, -10, 10, -10, 10, 0, 0];
% cent_x=[0, -8,  8, -6,   6, -14, 14];
% cent_y=[0, -12, 12, 12, -12, 0, 0]; 

% centroids with no wrapping params
cent_x_nowp=[-8,  -8,  14, -14, 28, -28, 20,  20, 34, 34]; 
cent_y_nowp=[12, -12,  0,   0,  0,   0, 12, -12, 12, -12];

if selection == weights_type(1)    
    if report_stats==1
        total_cents=find_stats(x_size, x_size_in, cent_x, cent_y, ...
            x_srt_stats, y_srt_stats);
    end
    
    % add more centroids for neural layer wrap around effect
    [cent_x,cent_y]=add_cents(cent_x, cent_y, x_size, x_size_in, ...
        x_srt, y_srt, 1, 0);

    % add centroids with no wrapping
    if use_nowp
        for i=1:length(cent_x_nowp)
            if cent_x_nowp(i)+x_srt>0 && cent_x_nowp(i)+x_srt<=x_size_in ...
            && cent_y_nowp(i)+y_srt>0 && cent_y_nowp(i)+y_srt<=x_size_in
            cent_x=[cent_x,cent_x_nowp(i)+x_srt];
            cent_y=[cent_y,cent_y_nowp(i)+y_srt];
            end
        end
    end
end

if selection == weights_type(2)
    x_sft = 62;
    y_sft = 59;
    x_srt = -x_sft+x_srt;
    y_srt = -y_sft+y_srt;
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

% plotting
plot_cent=zeros(x_size, x_size);
for i=1:length(cent_x)
	cent_i=(cent_y(i)*x_size_in)+cent_x(i);
    if cent_i > 0 && cent_i < in_layer
	    plot_cent=plot_cent+reshape(comb_syn_wts(cent_i,:),x_size,x_size);
        %fprintf("i:%d x:%d y:%d\n",cent_i,cent_x(i),cent_y(i));
    end
end
if create_plot==1 imagesc(plot_cent); end

% report stats
fprintf("centroids number: %d\ncentroids: ",length(cent_x));
for i=1:length(cent_x)
    fprintf("(%d,",cent_x(i));
    fprintf("%d) ",cent_y(i));
end
fprintf("\n");
if report_stats==1
    total_cents=find_stats(x_size, x_size_in, cent_x, cent_y, x_srt, y_srt);
    min_conn=min(total_cents);
    max_conn=max(total_cents);
    avg_conn=mean(total_cents);
    std_conn=std(total_cents);
    fprintf("avg:%.2f/%d min:%.2f max:%.2f std:%.2f\n",avg_conn,in_layer,min_conn,max_conn,std_conn);
    fprintf("avg:%.2f%% min:%.2f%% max:%.2f%% std:%.2f%%\n",avg_conn/in_layer*100,min_conn/in_layer*100,max_conn/in_layer*100,std_conn/in_layer*100);
end

function [cent_x,cent_y]=add_cents(cent_x, cent_y, x_size, x_size_in, ...
    x_srt, y_srt, x, y)
    grc_i = ((y+y_srt)*x_size_in)+x+x_srt-1; 
    grc_pd = get_pd(grc_i, x_size);

    % add starting positions to centroids
    for i=1:length(cent_x)
	    cent_x(i)=cent_x(i)+x_srt;
	    cent_y(i)=cent_y(i)+y_srt;
    end

    % based on pd, adjust centroids
	for i=1:length(cent_x)
		if 	   grc_pd == 0   cent_y(i) = cent_y(i) - 2;
        elseif grc_pd == 90  cent_x(i) = cent_x(i) + 2;
        elseif grc_pd == 180 cent_y(i) = cent_y(i) + 2;
        elseif grc_pd == 270 cent_x(i) = cent_x(i) - 2;
        end
    end

	cent_size=length(cent_x);
	for i=1:cent_size
		for j=1:9
			for k=1:9
				new_x=cent_x(i)+((-x_size*2)+(x_size*k));
				new_y=cent_y(i)+((-x_size*2)+(x_size*j));
				if (cent_x(i) == new_x && cent_y(i) == new_y) %{ skip %} ; end
				elseif new_x>=0 && new_x<x_size_in ...
				    && new_y>=0 && new_y<x_size_in
				    cent_x=[cent_x,new_x];
					cent_y=[cent_y,new_y];
				end
			end
		end
	end
end

function total_cents=find_stats(x_size, x_size_in, cent_x_stats, ...
    cent_y_stats, x_srt_stats, y_srt_stats)
    total_cents=[];
    for y=0:(x_size-1)
        for x=0:(x_size-1)
            x_srt=x+x_srt_stats; y_srt=y+y_srt_stats; % add starting positions to centroids
            cent_x=cent_x_stats; cent_y=cent_y_stats; % make local copy of centroids specific to a given starting position
            
            % add more centroids for neural layer wrap around effect
            [cent_x,cent_y]=add_cents(cent_x, cent_y, x_size, x_size_in, ...
                                      x_srt, y_srt, x, y);

            % filter cents
            cent_x_filt=[]; cent_y_filt=[];
            for ci=1:length(cent_x)
                if cent_x(ci)>0 && cent_x(ci)<=x_size_in ...
                && cent_y(ci)>0 && cent_y(ci)<=x_size_in
                    cent_x_filt=[cent_x_filt; cent_x(ci)];
                    cent_y_filt=[cent_y_filt; cent_y(ci)];
                    %disp(length(cent_x_filt));
                end
            end
            total_cents=[total_cents;length(cent_x_filt)];
            %total_cents=[total_cents;length(cent_x)];
        end
    end
end

function pd=get_pd(i, x_axis_size)
    pd = 0;
	x = mod(i,x_axis_size);
	y = i / x_axis_size;

	if mod(y,2) == 0
		if mod(x,2) == 0 pd = 90;
        else pd = 270; end
    else
		if mod(x,2) == 0 pd = 180;
        else pd = 0; end
    end
end