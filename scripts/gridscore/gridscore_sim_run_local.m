% run from local pc and create gridscore, trajectory plot, and rate map plot
cd ..
initOAT
cd gridscore
preloaded_spk_reader=0; % save time of loading spike reader by using prior loaded one
if preloaded_spk_reader==0 && ~exist('keep_vars','var') clear all; preloaded_spk_reader=0; end; clear keep_vars;
use_hopper_data=0; % access hopper data locally
if ~exist('local_run','var')
local_run=1; % local run number
end;
hopper_run=4; % hopper run number
fdr_prefix="gc_can_";%"gc_can_"; % folder name prefix for hopper run. "gc_can_" for main dir; "param_explore_iz_" for iz pe.
if ~exist('restrict_time','var')
restrict_time=000;%6733000;%4328000;%1360000;%500000; % limit time plotted. 0 for no restriction; in 20ms bins
end; run_on_hopper=0; % supercomputer run options: run from hopper's system  
plot_spikes = 1; % turn off spike plotting when only movement trajectory is desired to be plotted
sel_nrn=1288;%1187;%506;%606;%1116;%748;%300;%318;%281;%894;%658;%638;%912;%606;%300;%300;%293;%673;%1135;%1052;%1130;%1240;%1319;%1156;%1197;%1187;%506;%1187;%1288;%1187;%506;%711;%868;%483;%1288;%1194;%1288;%1185;%1288;%711;%300;%1225;%817;%1410;%708;%668;%788;%711;%1185;%1187;%1185;%1188;%1180;%1188;%1193;%1188;%1188;%1268;%711;%1268;%711;%711;%792;%789;%711;%327;%405;%786;%405;%822;%409;%190;%794;%205;%795;%868;%1305;%483;%728;%700;%500;%483;%458;%1135;%978;%1135;%1135;%1096;%1096;%1136;%653;%592;%591;%506;%655;%506;%978;%979;%506;%430;%1288;%1164;%1045;%1053;%1164;%1045;%506;%1045;%1185;%140;%730;%1288;%506;%1288;%1290;%1288;%506;%810;%1288;%1288;%1215;%1230;%1420;%1570;%1185;%1381;%1185;%506;%506;%593;%1381;%1381;%979;%506;%979;%506;%1381;%455;%1287;%670;%669;%1248;%669;%1288;%1286;%493;%979;%1185;%506;%979;%506;%1225;%506;%976;%388;%493;%976;%493;%400;%600;%400;%900;%506;%450;%506;%507;%967;%1577;%706;%493;%1325;%1017;%493;%1577;%600;%646;%535;%1577;%493;%693;%810;%493;%492;%455;%493;%454;%1577;%1542;%17;%1577;%970;%810;%1577;%970;%1035;%1577;%1592;%1578;%19;%17;%1577;%16;%546;%18;%296;%260;%182;%388;%265;%182;%792;%711;%670;%273;%222;%510;%469;%715;%338;%290;%715;%600;%868;%825;%240;%825;%715;%835;%615;%410;%388;%387;%347;%348;%110;%210;%262;%454;%454;%453;%455;%591;%629;%547;%629;%494;%290;%393;%243;%358;%338;%210;%290;%497;%860;%810;%300;%1250;%410;%820;%516;%1228;%690; % select neuron to plot
smaller_spk_ticks=1;%5;%1; % choose trajectory plot tick size. 2 for extra small.
p1=0; p2=0; % param explore parameter for file naming
save_gridscore_file=0; % save gridscore to file
save_plot=0;
save_traj_plot=0;
save_firingrate_file=0;
if ~exist('run_real_recordings','var') run_real_recordings=0; end % run parameters for real recordings
if ~exist('plot_subsect','var') plot_subsect=1; end % plot only subsection of total data. this is set by the plot_size variable.
if ~exist('grid_size','var') grid_size=40; end % sqrt of grid size
if ~exist('plot_size','var') plot_size=31; end % sqrt of plot size
if ~exist('alt_data','var') alt_data=0; end % if new animal data from 08/01/23 is used

gridscore_sim