# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.
# This version is for tsodyks-markram params
# Note: the target line to be changed with regex must be converted to 1 line not
# multiple lines.

# select params
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(0.1514 0.1967 0.2420 0.2874 0.3327)
export param2_vals=(20.0590 29.7855 39.5121 49.2386 58.9651)
export param3_vals=(0.1655 0.2063 0.2471 0.2880 0.3288)
export param4_vals=(14.7014 25.4180 36.1346 46.8512 57.5678)
export param5_vals=(0.1511 0.2049 0.2587 0.3125 0.3663)
export param6_vals=(12.7364 30.8289 48.9213 67.0138 85.1063)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPu\\()(\\d+[.]?\\d*)(,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauU\\()(\\d+[.]*\\d*)(,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPu\\()(\\d+[.]?\\d*)(,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauU\\()(\\d+[.]*\\d*)(,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPu\\()(\\d+[.]?\\d*)(,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauU\\()(\\d+[.]*\\d*)(,.*)\"";
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
	#matlab -nodisplay -r "gridscore_sim $p1 $p2; exit" &&
	cd ../param_explore/
}

# run all param combinations
#for i in ${param1_vals[@]}; do
#for j in ${param2_vals[@]}; do
for i in {0..4} 
do
for j in {0..4} 
do
	# param change
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern1 &&
	export value_change=" \"${param1_vals[$i]}\"" &&
	export p1=$i;
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
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern2 &&
	export value_change=" \"${param2_vals[$j]}\"" &&
	export p2=$j;
	chg_prm &&
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern4 &&
	export value_change=" \"${param4_vals[$j]}\"" &&
	chg_prm &&
	export param_file=$param_file2 &&
	export param_pattern=$param_pattern6 &&
	export value_change=" \"${param6_vals[$j]}\"" &&
	chg_prm &&	
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done