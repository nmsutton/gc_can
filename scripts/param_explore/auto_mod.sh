# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.

# select params
export param1_vals=(0 32 64 96 128)
export param2_vals=(0 2.9225 5.8450 8.7675 11.6900)
export param_file1=" \"../../generate_config_state2.cpp\"";
export param_file2=" \"../../generate_config_state2.cpp\"";
export param_pattern1=" \"(.*MEC_LII_Stellate, )(\\d+.*\\d*)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)\""
export param_pattern2=" \"(.*0.0f, 0.004f, 0.0f, )(\\d+.*\\d*)(f, 0.0f, 7.85f, 0.0f, -52.68f, 0.0f.*)\""
# general settings
touch ./output/param_records.txt
echo "" > ./output/param_records.txt # clear file
export make_clean_am="rm auto_mod_params"
export make_am="g++ -Wall -g -std=c++11 auto_mod_params.cpp -o auto_mod_params"
export run_am=" && ./auto_mod_params"
export space=" "
export comma=","
export date_format="date +%H-%M-%S_%m-%d-%Y"

chg_prm(){
	# change params
	command=$make_clean_am
	eval $command;
	command=$make_am$run_am$param_file$param_pattern$value_change
	eval $command;
}

run_sim(){
	# run CARLsim
	cd ../..
	#./rebuild.sh
	cd scripts/param_explore/

	# generate results reports
	cd ../gridscore/
	#matlab -nodisplay -r "gridscore_sim ; exit"
	cd ../param_explore/
}

# run all param combinations
for i in ${param1_vals[@]}; do
for j in ${param2_vals[@]}; do
	# param 1 change
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=$space$i &&
	chg_prm &&
	# param 2 change
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern2 &&
	export value_change=$space$j &&
	chg_prm &&
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done