# Parameter exploration of firing pattern fits to Izhikevich parameters
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.

# params
# Note: set number of vals in for statement {1..<count>} below

# params
source ./config_files/params_config_fp_iz.sh
# general settings
curr_dir=$PWD
if [ "$run_on_hopper" == "1" ]; then
	base_folder="/home/nsutton2/git/Time/";
else
	base_folder="/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/Time/";
fi
ea_input_filepath="$base_folder$input_path";
ea_filepath="$base_folder";
ea_results_filepath="$base_folder$output_path";
ea_file_run="nohup ./startEAbatch.sh &> /dev/null"
pat1="s/"
pat2=" : \[-*[[:digit:]]\+.*[[:digit:]]*, -*[[:digit:]]\+.*[[:digit:]]*\]\,/"
pat3=" : ["
pat4="],/g"
results_file="./output/param_records_ea_iz.txt"
touch $results_file
echo "" > $results_file # clear file

run_ea(){
	cd $ea_filepath
	command=$ea_file_run
	eval $command
	cd $curr_dir

	tail -n 2 $ea_results_filepath >> $results_file # save results
	#echo "" >> $results_file # newline
}

for i in {0..8} 
do
for j in {0..8} 
do
	# update params
	sed -i "$pat1${p1_p}$pat2${p1_p}$pat3${p1_v[$i]}, ${p1_v[$i]}$pat4" $ea_input_filepath
	sed -i "$pat1${p2_p}$pat2${p2_p}$pat3${p2_v[$j]}, ${p2_v[$j]}$pat4" $ea_input_filepath

	run_ea

	echo "processed $i $j";
done
done