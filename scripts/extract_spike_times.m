%% 
%% This script extract a specific time period of spikes
%% and saves them to a file.
%%

run_on_supercomp=1; % select to run on the supercomputer
if run_on_supercomp==1
    output_file='/scratch/nsutton2/gc_sim/sel_spks_1hr.csv';
    curr_dir=pwd;
    cd /home/nsutton2/git/OAT_CS4/
    initOAT
    cd(curr_dir)
    addpath /home/nsutton2/git/CMBHOME_github/ 
elseif run_on_supercomp==0
    output_file='sel_spks.csv';
    initOAT
    addpath /comp_neuro/Software/Github/CMBHOME_github/
end

SR = SpikeReader('../results/spk_MEC_LII_Stellate.dat', false, 'silent');
spikes = SR.readSpikes(1);
start_t = 3600000;%30000;%8180000;%30000;
end_t = start_t+306000;%1000;%305000;
spk_sel = spikes(start_t:end_t,:);
writematrix(spk_sel,output_file,'Delimiter','comma');
