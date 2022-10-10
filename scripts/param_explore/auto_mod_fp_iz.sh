# Parameter exploration of firing pattern fits to Izhikevich parameters
# Use matlab's linspace (e.g., linspace(0,128,5)) to find param ranges.

# params
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.120 0.220 0.320 0.420 0.520 0.620 0.720 0.820 0.920 1.020 1.120)
p2_v=(0.0000 0.0010 0.0020 0.0030 0.0040 0.0050 0.0060 0.0070 0.0080 0.0090 0.0100)
p1_p="\"K\""
p2_p="\"A\""
curr_dir=$PWD
ea_input_filepath="/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/Time/input/11/3a/6-019-1.json"
ea_filepath="/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/Time/"
ea_file_run="nohup ./startEAbatch.sh &> /dev/null"
ea_results_filepath="/home/nmsutton/Dropbox/CompNeuro/gmu/research/sim_project/code/Time/output/11/3a/6-019-1/local/job.0.Full"
pat1="s/"
pat2=" : [[[:digit:]]\+\.[[:digit:]]\+, [[:digit:]]\+\.[[:digit:]]\+\]\,/"
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

for i in {0..10} 
do
for j in {0..10} 
do
	# update params
	sed -i "$pat1${p1_p}$pat2${p1_p}$pat3${p1_v[$i]}, ${p1_v[$i]}$pat4" $ea_input_filepath
	sed -i "$pat1${p2_p}$pat2${p2_p}$pat3${p2_v[$j]}, ${p2_v[$j]}$pat4" $ea_input_filepath

	run_ea

	echo "processed $i $j";
done
done