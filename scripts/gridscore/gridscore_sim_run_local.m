% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
use_hopper_data=1; % access hopper data locally
local_run=2; % local run number
save_gridscore_file=0; % save gridscore to file
% supercomputer run options:
hopper_run=3; % hopper run number
run_on_hopper=0; % run from hopper's system 
fdr_prefix=""; % folder name prefix for hopper run 
% fdr_prefix="" for gc_can and fdr_prefix="param_explore_iz_" for iz pe

heat_map = gridscore_sim(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file);