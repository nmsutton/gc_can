# izhikevich model firing pattern parameter exploration parameters
# VT and B. Value ranges were selected based on the original json
# file and HCO listed IZ values for MEC LII Stellate

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-65.0 -50.0 -35.0 -20.0 -5.0 3.0 25.0 40.0 55.0)
p2_v=(-3.1667 0.0000 3.1667 6.3333 9.5000 11.6900 15.8333 19.0000 22.1667)
p1_p="\"D\""
p2_p="\"B\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"