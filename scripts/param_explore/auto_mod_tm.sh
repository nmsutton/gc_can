# Automatically modify simulation parameter settings for parameter explorations
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.
# This version is for tsodyks-markram params
# Note: the target line to be changed with regex must be converted to 1 line not
# multiple lines.

# select params
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(123.6932 277.4218 431.1504 584.8790 738.6077)
export param2_vals=(6.6322 5.7332 4.8342 3.9351 3.0361)
export param3_vals=(118.9779 270.4092 421.8405 573.2718 724.7031)
export param4_vals=(6.2055 5.3594 4.5134 3.6673 2.8213)
export param5_vals=(106.1875 264.1745 422.1616 580.1487 738.1358)
export param6_vals=(5.4674 4.7403 4.0133 3.2862 2.5592)
export param7_vals=(385.3961 532.6420 679.8879 827.1337 974.3796)
export param8_vals=(8.8387 7.6411 6.4435 5.2458 4.0482)
export param9_vals=(401.7326 536.6648 671.5969 806.5291 941.4612)
export param10_vals=(9.1373 7.8868 6.6362 5.3856 4.1350)
export param11_vals=(374.8724 488.9898 603.1072 717.2246 831.3420)
export param12_vals=(10.0216 8.6470 7.2724 5.8979 4.5233)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtdAMPA\\()(\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtdAMPA\\()(\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtdAMPA\\()(\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern7=" \"(.*sim.setSTP\\(EC_LII_Axo_Axonic, MEC_LII_Stellate, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern8=" \"(.*sim.setSTP\\(EC_LII_Axo_Axonic, MEC_LII_Stellate, true,.*STPtdGABAa\\()(\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern9=" \"(.*sim.setSTP\\(MEC_LII_Basket, MEC_LII_Stellate, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern10=" \"(.*sim.setSTP\\(MEC_LII_Basket, MEC_LII_Stellate, true,.*STPtdGABAa\\()(\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern11=" \"(.*sim.setSTP\\(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true,.*STPtauX\\()(\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern12=" \"(.*sim.setSTP\\(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true,.*STPtdGABAa\\()(\\d+[.]*\\d*)(f?,.*)\"";
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
	#echo $command
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
	#echo "run sim"
}

# run all param combinations
for i in {0..4} 
do
for j in {0..4} 
do
	# param change
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
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern7 &&
	export value_change=" \"${param7_vals[$i]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern9 &&	
	export value_change=" \"${param9_vals[$i]}\"" &&
	chg_prm &&	
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern11 &&	
	export value_change=" \"${param11_vals[$i]}\"" &&
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
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern8 &&
	export value_change=" \"${param8_vals[$j]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern10 &&
	export value_change=" \"${param10_vals[$j]}\"" &&
	chg_prm &&
	export param_file=$param_file1 &&
	export param_pattern=$param_pattern12 &&
	export value_change=" \"${param12_vals[$j]}\"" &&
	chg_prm &&
	# save params
	curr_time=$($date_format) &&
	echo $curr_time$comma$i$comma$j >> ./output/param_records.txt &&
	# run simulation
	run_sim
done
done