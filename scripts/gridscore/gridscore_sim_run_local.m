% run from local pc and create gridscore, trajectory plot, and rate map plot

% general run options
p1=0; % param explore parameter for file naming
p2=0; % param explore parameter for file naming
use_hopper_data=1; % access hopper data locally
local_run=1; % local run number
hopper_run=3; % hopper run number
save_gridscore_file=0; % save gridscore to file
fdr_prefix="gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
restrict_time=0;%6733000;%4328000;%1360000;%500000; % limit time plotted. 0 for no restriction; in 20ms bins
run_on_hopper=0; % supercomputer run options: run from hopper's system  
smaller_spk_ticks=1; % choose trajectory plot tick size. 2 for extra small.
preloaded_spk_reader=1; % save time of loading spike reader by using prior loaded one
% select neuron to plot
sel_nrn=17;%17;%1577;%16;%546;%18;%296;%260;%182;%388;%265;%182;%792;%711;%670;%273;%222;%510;%469;%715;%338;%290;%715;%600;%868;%825;%240;%825;%715;%835;%615;%410;%388;%387;%347;%348;%110;%210;%262;%454;%454;%453;%455;%591;%629;%547;%629;%494;%290;%393;%243;%358;%338;%210;%290;%497;%860;%810;%300;%1250;%410;%820;%516;%1228;%690;

gridscore_sim