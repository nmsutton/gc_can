# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.
# This version is for tsodyks-markram params
# Note: the target line to be changed with regex must be converted to 1 line not
# multiple lines.

# select params
export param1_vals=(0.1655 0.2063 0.2471 0.2880 0.3288)
export param2_vals=(14.7014 25.4180 36.1346 46.8512 57.5678)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPu\\()(\\d+[.]?\\d*)(,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauU\\()(\\d+[.]*\\d*)(,.*)\"";
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
	command=$make_am$run_am$param_file$param_pattern$value_change
	eval $command
}

run_sim(){
	# run CARLsim
	cd ../.. &&
	./rebuild.sh &&
	cd scripts/param_explore/ &&

	# generate results reports
	cd ../gridscore/ &&
	matlab -nodisplay -r "gridscore_sim $p1 $p2; exit" &&
	cd ../param_explore/
}

# run all param combinations
for i in ${param1_vals[@]}; do
for j in ${param2_vals[@]}; do
	# param 1 change
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=" \"$i\"" &&
	export p1=$i;
	chg_prm &&
	# param 2 change
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern2 &&
	export value_change=" \"$j\"" &&
	export p2=$j;
	chg_prm &&
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done