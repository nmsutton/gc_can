# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.01 37.5000 75.0000 118.0000 150.0000 187.5000 225.0000 262.5000 300.0000)
p2_v=(0.0 1.8750 3.7500 5.6250 7.5000 9.3750 11.2500 13.1250 15.0000)
p1_p="\"CM\""
p2_p="\"VMIN\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"