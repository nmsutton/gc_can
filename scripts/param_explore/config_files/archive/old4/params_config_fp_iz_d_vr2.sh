# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-60.0000 -42.5000 -25.0000 -7.5000 10.0000 27.5000 45.0000 62.5000 80.0000)
p2_v=(-66.5300 -64.5300 -62.5300 -60.5300 -58.5300 -56.5300 -54.5300 -52.5300 -50.5300)
p3_v=(17.0100 15.0100 13.0100 11.0100 9.0100 7.0100 5.0100 3.0100 1.0100)
p4_v=(23.0100 21.0100 19.0100 17.0100 15.0100 13.0100 11.0100 9.0100 7.0100)
p5_v=(78.0100 76.0100 74.0100 72.0100 70.0100 68.0100 66.0100 64.0100 62.0100)
p1_p="\"D\""
p2_p="\"VR\""
p3_p="\"VMIN\""
p4_p="\"VT\""
p5_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"