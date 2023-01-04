% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
use_hopper_data=0; % access hopper data locally
local_run=4; % local run number
hopper_run=3; % hopper run number
save_gridscore_file=0; % save gridscore to file
fdr_prefix="gc_can_"; % folder name prefix for hopper run. fdr_prefix="" for gc_can. fdr_prefix="param_explore_iz_" for iz pe
run_on_hopper=0; % supercomputer run options: run from hopper's system  

heat_map = gridscore_sim(p1,p2,local_run,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file);