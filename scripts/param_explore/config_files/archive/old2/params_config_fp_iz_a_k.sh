# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-0.3333 0.0000 0.3333 0.6200 1.0000 1.3333 1.6667 2.0000 2.3333)
p2_v=(-0.0810 0.0020 0.0050 0.1680 0.2510 0.3340 0.4170 0.5000 0.5830)
p1_p="\"K\""
p2_p="\"A\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"