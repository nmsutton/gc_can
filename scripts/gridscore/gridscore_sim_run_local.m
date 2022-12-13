% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
save_gridscore_file=0; % save gridscore to file
local_run=1; % local run number
% supercomputer run options:
run_on_hopper=0; % run from hopper's system 
use_hopper_data=0; % access hopper data locally
hopper_run=1; % hopper run number
fdr_prefix=""; % folder name prefix for hopper run 
% fdr_prefix="" for gc_can and fdr_prefix="param_explore_iz_" for iz pe

gridscore_sim(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file);