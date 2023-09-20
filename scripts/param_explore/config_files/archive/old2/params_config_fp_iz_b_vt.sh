# izhikevich model firing pattern parameter exploration parameters
# VT and B. Value ranges were selected based on the original json
# file and HCO listed IZ values for MEC LII Stellate

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.0000 3.8333 7.6667 11.5000 15.0000 19.1667 23.0000)
p2_v=(0.0000 3.1667 6.3333 9.5000 11.6900 15.8333 19.0000)
p1_p="\"VT\""
p2_p="\"B\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"