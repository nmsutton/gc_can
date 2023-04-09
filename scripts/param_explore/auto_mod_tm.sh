# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.
# This version is for Tsodyks-Markram params
# Note: the target line to be changed with regex must be converted to 1 line not
# multiple lines.

# params
source ./config_files/params_config_tm.sh
# general settings
touch ./output/param_records.txt
echo "" > ./output/param_records.txt # clear file
export make_clean_am="rm auto_mod_params"
export make_am="g++ -Wall -g -std=c++11 auto_mod_params.cpp -o auto_mod_params"
export run_am=" && ./auto_mod_params"
export space=" "
export comma=","
export semicol=";"
export date_format="date +%H-%M-%S_%m-%d-%Y"
module load matlab # load matlab on remote computer

chg_prm(){
	# change params
	command=$make_clean_am
	eval $command
	command=$make_am$run_am$paramexp_type$param_file$param_pattern$value_change
	eval $command
	#echo $command
}

run_sim(){
	# run CARLsim
	export curr_dir=$PWD;
	if [ $run_on_hopper == 0 ]; then
		command="cd ../../../../.build/projects/$fdr_prefix$local_run/"
	else
		command="cd ../../../../.build/projects/$fdr_prefix$hopper_run/"
	fi
	eval $command &&
	./rebuild.sh &&
	command="cd $curr_dir" &&
	eval $command &&

	# generate results reports
	cd ../gridscore/ &&
	matlab -nodisplay -r "gridscore_sim_function $p1 $p2 $local_run $run_on_hopper $use_hopper_data $fdr_prefix $hopper_run $save_gridscore_file; exit" &&
	cd ../param_explore/
	#echo "run sim"
}

# run all param combinations
for i in {0..8} 
do
for j in {0..8} 
do
	# param change	
	echo "processing p1: $i; p2: $j";
	export p1=$i &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=" \"${param1_vals[$i]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern3 &&	
	export value_change=" \"${param3_vals[$i]}\"" &&
	chg_prm &&	
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern5 &&	
	export value_change=" \"${param5_vals[$i]}\"" &&
	chg_prm &&		
	# param change
	export p2=$j &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern2 &&
	export value_change=" \"${param2_vals[$j]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern4 &&
	export value_change=" \"${param4_vals[$j]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern6 &&
	export value_change=" \"${param6_vals[$j]}\"" &&
	chg_prm &&	
	# save record of params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done
