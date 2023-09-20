# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(5.0000   54.1667  118.0000  152.5000  201.6667  250.8333  300.0000)
p2_v=(50.0000   58.3333   66.6667   70.0100   83.3333   91.6667  100.0000)
p1_p="\"CM\""
p2_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"