# find firing rate distribution for simulation results
# this code allows for firing rate results measured after
# rate map smoothing and occupancy normalization

# settings
touch ./firing_rate_records.txt
echo "" > ./firing_rate_records.txt # clear file
export fdr_prefix="gc_can_" # folder name prefix
export run_on_hopper=0 # run from hopper's system 
export local_run=1 # local run number
export use_hopper_data=0 # access hopper data locally
export hopper_run=1 # hopper run number
export save_gridscore_file=0; # save gridscore to file
export p1=0;
export p2=0;
export preloaded_spk_reader=0;
export sel_nrn=1;
export save_plot=0; # save rate map plot
export save_traj_plot=0;
export save_firingrate_file=1; # save firing rate to file

find_fr(){
	cd gridscore &&
	matlab -nodisplay -r "gridscore_sim_function $p1 $p2 $local_run $run_on_hopper \
$use_hopper_data $fdr_prefix $hopper_run $save_gridscore_file $preloaded_spk_reader \
$sel_nrn $save_plot $save_traj_plot $save_firingrate_file; exit" &&
	cd ..
}

for i in {1..3} 
do
	export sel_nrn=$i;
	find_fr
	export preloaded_spk_reader=1;
done