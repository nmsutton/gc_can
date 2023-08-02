%clear all;
addpath /comp_neuro/Software/Github/CMBHOME_github/
time_convert=1/0.02; % 1/<sampling_rate_in_ms>
Xs=[];Ys=[];spk_t=[];spk_x=[];spk_y=[];
fprintf("Using T:%d C:%d\n",tetrodes(file_number),cells(file_number));

% load file
load(filenames(file_number));

% load epoch
if alt_data==0
    root.epoch=lightON;
end

% load cell
root.cel = [tetrodes(file_number),cells(file_number)];

% find number of epochs
epochs_num=size(root.x(:));
epochs_num=epochs_num(1);

if alt_data==0
    % extract x, y, spk
    for i=1:epochs_num
        Xs=[Xs;root.x{i,:}];
        Ys=[Ys;root.y{i,:}];
        spk_x=[spk_x;root.cel_x{i,:}];
        spk_y=[spk_y;root.cel_y{i,:}];
        spk_t=[spk_t;root.cel_ts{i,:}];
    end
else
    Xs=root.x;
    Ys=root.y;
    spk_x=root.cel_x{1,:};
    spk_y=root.cel_y{1,:};
    spk_t=root.cel_ts{1,:};
end

% convert to ms where 1 unit = 20ms
spk_t=spk_t*time_convert;