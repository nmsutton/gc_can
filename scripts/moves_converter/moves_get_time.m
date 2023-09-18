%
% report time in experiment
%
clear all;
CMBHome_path = "/comp_neuro/Software/Github/CMBHOME_github/";
addpath(CMBHome_path);
load filenames;
load tetrodes;
load cells;
file_number=15;
load(filenames(file_number));
root.cel = [tetrodes(file_number),cells(file_number)];
ts_per_sec=50; % timesteps per second
ms_per_ts=20; % milliseconds per timestep
ms_per_s=1000; % milliseconds per second
alt_data = 0; % use data from new experiments received on 08/01/23
if alt_data==0
    root.epoch=lightON;
end
num_of_sections=length(root.ts);

time=0;
if alt_data==0
    for i=1:num_of_sections
        time=time+(length(root.ts{i,1})/ts_per_sec);
    end
else
    time=(length(root.ts)*ms_per_ts)/ms_per_s;
end
fprintf("Time in ms: %.0f\n",time*ms_per_s);