# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.

# select params
export param1_vals="csv_files/6-003-1_paramset.csv"
export param2_vals=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../general_params.cpp\"";
#export param_pattern1=" \"(.*MEC_LII_Stellate, )(\\d+.*\\d*)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)\""
#export param_pattern1=" \"(.*)(MEC_LII_Stellate, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f,\\D*0.0f, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f, 0.0f, [-]?\\d+[.]\\d*f, 0.0f,\\D*[-]?\\d+[.]\\d*f, 0.0f, 1[)];)(.*)\"";
export param_pattern1=" \"(.*)(sim.setNeuronParameters\\(MEC_LII_Stellate, )(.*)\"";
#export param_pattern2=" \"(.*0.0f, 0.004f, 0.0f, )(\\d+.*\\d*)(f, 0.0f, 7.85f, 0.0f, -52.68f, 0.0f.*)\""
export param_pattern2=" \"(.*)(dir_to_gc_wt = \\d+[.]?\\d*)(.*)\""
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
	#./rebuild.sh &&
	cd scripts/param_explore/ &&

	# generate results reports
	cd ../gridscore/ &&
	#matlab -nodisplay -r "gridscore_sim ; exit" &&
	cd ../param_explore/
}

# run all param combinations
while IFS="," read -r p0 p1 p2 p3 p4 p5 p6 p7 p8 p9
do
for j in ${param2_vals[@]}; do
	# param 1 change
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=" \"sim.setNeuronParameters(MEC_LII_Stellate, $p5""f, 0.0f, $p1""f, 0.0f, $p6""f, 0.0f, $p7""f,|
                                0.0f, $p2""f, 0.0f, $p3""f, 0.0f, $p8""f, 0.0f, $p9""f, 0.0f,|
                                $p4""f, 0.0f, 1);\"" &&
	chg_prm &&
	# param 2 change
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern2 &&
	export value_change=" \"        double dir_to_gc_wt = \""$j"\;" &&
	chg_prm &&
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done < $param1_vals