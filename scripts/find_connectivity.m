% find connectivity

thresh=.001;%.002;

%weights=readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_1/scripts/generate_params/synapse_weights.csv');
%weights=readmatrix('/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/gc_can_1/data/synapse_weights.csv');
weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/backup/weight_gen/lrg_fields_med_fr_1_and_2/synapse_weights.csv');
%tot_conn=find(weights>=.thresh);

grc_layer=size(weights,2);

ind_conn=[];
for i=1:length(weights)
	ind_conn=[ind_conn;length(find(weights(i,:)>=thresh))];
end

min_conn=min(ind_conn);
max_conn=max(ind_conn);
avg_conn=mean(ind_conn);
std_conn=std(ind_conn);

fprintf("avg:%.2f%% min:%.2f%% max:%.2f%% std:%.2f%%\n",avg_conn/grc_layer*100,min_conn/grc_layer*100,max_conn/grc_layer*100,std_conn/grc_layer*100);
