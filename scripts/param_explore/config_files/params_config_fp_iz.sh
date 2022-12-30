# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.12 0.42 0.62 0.72 0.92)
p2_v=(0.001 0.003 0.005 0.007 0.01)
p1_p="\"K\""
p2_p="\"A\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"