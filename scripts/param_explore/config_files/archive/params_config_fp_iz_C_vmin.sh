# parameter exploration settings

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(30.0000 47.5000 65.0000 82.5000 100.0000 118.0000 135.0000 152.5000 170.0000)
p2_v=(1.7800 4.1238 6.4675 9.0100 11.1550 13.4988 15.8425 18.1862 20.5300)
p1_p="\"CM\""
p2_p="\"VMIN\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"