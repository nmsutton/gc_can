% find connectivity

thresh=.002;

weights=readmatrix('/mnt/StorageDrive/General/comp_neuro/gmu/research/simulation/code/holger_data/medium_fields_weights/weights.csv');
%tot_conn=find(weights>=.thresh);

ind_conn=[];
for i=1:length(weights)
	ind_conn=[ind_conn;length(find(weights(i,:)>=thresh))];
end

min_conn=min(ind_conn);
max_conn=max(ind_conn);
avg_conn=mean(ind_conn);

fprintf("avg:%.2f%% min:%.2f%% max:%.2f%%\n",avg_conn/length(weights)*100,min_conn/length(weights)*100,max_conn/length(weights)*100);
