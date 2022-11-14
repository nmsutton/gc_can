# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.
# This version is for Izhikevich params
# Note: the target line to be changed with regex must be converted to 1 line not
# multiple lines.

# params
source ./config_files/params_config_iz.sh
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
}

run_sim(){
	# run CARLsim
	cd ../.. &&
	./rebuild.sh &&
	cd scripts/param_explore/ &&

	# generate results reports
	cd ../gridscore/ &&
	matlab -nodisplay -r "gridscore_sim $p1 $p2 $run_on_hopper $use_hopper_data $fdr_prefix $hopper_run $save_gridscore_file; exit" &&
	cd ../param_explore/
}

# run all param combinations
for i in {0..4} 
do
for j in {0..4} 
do
	# param change
	echo "processing p1: $i; p2: $j";
	export p1=$i &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=" \"${param1_vals[$i]}\"" &&
	chg_prm &&
	# param change
	export p2=$j &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern2 &&
	export value_change=" \"${param2_vals[$j]}\"" &&
	chg_prm &&
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done