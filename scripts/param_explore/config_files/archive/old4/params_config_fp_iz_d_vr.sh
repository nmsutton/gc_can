# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-60.0000 -42.5000 -25.0000 -7.5000 10.0000 27.5000 45.0000 62.5000 80.0000)
p2_v=(-64.5300 -63.0300 -61.5300 -60.0300 -58.5300 -57.0300 -55.5300 -54.0300 -52.5300)
p3_v=(15.0100 13.5100 12.0100 10.5100 9.0100 7.5100 6.0100 4.5100 3.0100)
p4_v=(21.0100 19.5100 18.0100 16.5100 15.0100 13.5100 12.0100 10.5100 9.0100)
p5_v=(76.0100 74.5100 73.0100 71.5100 70.0100 68.5100 67.0100 65.5100 64.0100)
p1_p="\"D\""
p2_p="\"VR\""
p3_p="\"VMIN\""
p4_p="\"VT\""
p5_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"