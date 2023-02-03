% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
use_hopper_data=1; % access hopper data locally
local_run=1; % local run number
hopper_run=5; % hopper run number
save_gridscore_file=0; % save gridscore to file
fdr_prefix="gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
restrict_time=0;%6733000;%4328000;%1360000;%500000; % limit time plotted. 0 for no restriction; in 20ms bins
run_on_hopper=0; % supercomputer run options: run from hopper's system  
smaller_spk_ticks=2; % choose trajectory plot tick size. 2 for extra small.
% select neuron to plot
sel_nrn=210;%290;%497;%860;%810;%300;%1250;%410;%820;%516;%1228;%690;

heat_map = gridscore_sim(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix, ...
    hopper_run,save_gridscore_file,restrict_time,sel_nrn,smaller_spk_ticks);