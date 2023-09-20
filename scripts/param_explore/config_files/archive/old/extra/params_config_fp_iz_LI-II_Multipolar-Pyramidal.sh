# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.37 0.37 0.37 0.37 0.37)
p2_v=(0.001 0.001 0.001 0.001 0.001)
p1_p="\"K\""
p2_p="\"A\""
input_path="input/11/5/6-008-1_custom.json"
output_path="output/11/5/6-008-1/local/job.0.Full"