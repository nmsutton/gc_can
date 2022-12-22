# izhikevich model firing pattern parameter exploration parameters
# VT and B. Value ranges were selected based on the original json
# file and HCO listed IZ values for MEC LII Stellate

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-45.0000 -33.7500 -22.5000 -11.2500 0.0)
p2_v=(0.0 12.5000 25.0000 37.5000 50.0000)
p1_p="\"VT\""
p2_p="\"B\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"