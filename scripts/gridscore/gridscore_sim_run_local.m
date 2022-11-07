% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
save_gridscore_file=0; % save gridscore to file
% supercomputer run options:
run_on_hopper=0; % run from hopper's system 
use_hopper_data=0; % access hopper data locally
fdr_prefix="param_explore_tm_"; % folder name prefix for hopper run
hopper_run=1; % hopper run number

gridscore_sim(p1,p2,run_on_hopper,use_hopper_data,fdr_prefix,hopper_run,save_gridscore_file);