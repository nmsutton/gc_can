% find connectivity

thresh=.000001;%.001;%.002;

% sml_fields_low_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/sml_fields_low_fr/proj_dir/gc_can_5/data/synapse_weights.csv');
% sml_fields_med_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/sml_fields_med_fr/proj_dir/gc_can_7/data/synapse_weights.csv');
% sml_fields_high_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/sml_fields_high_fr/proj_dir/gc_can_5/data/synapse_weights.csv');
% med_fields_low_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/med_fields_low_fr/proj_dir/gc_can_2/data/synapse_weights.csv');
% med_fields_med_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/med_fields_med_fr/proj_dir/med_fields/gc_can_1/data/synapse_weights.csv');
% med_fields_high_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/med_fields_high_fr/proj_dir/gc_can_6/data/synapse_weights.csv');
% lrg_fields_low_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/lrg_fields_low_fr/proj_dir/gc_can_2/data/synapse_weights.csv');
% lrg_fields_med_fr
weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/lrg_fields_med_fr_1/proj_dir/gc_can_7/data/synapse_weights.csv');
% lrg_fields_high_fr
% weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/firing_rates_analyses/lrg_fields_high_fr_1/proj_dir/data/synapse_weights.csv');
% local file
% weights=readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_1/data/synapse_weights.csv');

grc_layer=size(weights,2);

%%%% GrC connections per IN %%%%

ind_conn=[];
for i=1:length(weights(:,1))
	ind_conn=[ind_conn;length(find(weights(i,:)>=thresh))];
end

min_conn=min(ind_conn);
max_conn=max(ind_conn);
avg_conn=mean(ind_conn);
std_conn=std(ind_conn);

fprintf("GrC connections per IN\n");
fprintf("avg:%.2f%% min:%.2f%% max:%.2f%% std:%.2f%% \navg_cnt:%.0f min_cnt:%.0f max_cnt:%.0f std_cnt:%.0f\n",avg_conn/grc_layer*100,min_conn/grc_layer*100,max_conn/grc_layer*100,std_conn/grc_layer*100,avg_conn,min_conn,max_conn,std_conn);

%%%% IN connections per GrC %%%%

ind_conn=[];
for i=1:length(weights(1,:))
	ind_conn=[ind_conn;length(find(weights(:,i)>=thresh))];
end

min_conn=min(ind_conn);
max_conn=max(ind_conn);
avg_conn=mean(ind_conn);
std_conn=std(ind_conn);

fprintf("IN connections per GrC\n");
fprintf("avg:%.2f%% min:%.2f%% max:%.2f%% std:%.2f%% \navg_cnt:%.0f min_cnt:%.0f max_cnt:%.0f std_cnt:%.0f\n",avg_conn/grc_layer*100,min_conn/grc_layer*100,max_conn/grc_layer*100,std_conn/grc_layer*100,avg_conn,min_conn,max_conn,std_conn);