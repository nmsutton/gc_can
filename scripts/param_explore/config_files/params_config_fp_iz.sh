# izhikevich model firing pattern parameter exploration parameters

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(0.120 0.220 0.320 0.420 0.520 0.620 0.720 0.820 0.920 1.020 1.120)
p2_v=(0.0000 0.0010 0.0020 0.0030 0.0040 0.0050 0.0060 0.0070 0.0080 0.0090 0.0100)
p1_p="\"K\""
p2_p="\"A\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"