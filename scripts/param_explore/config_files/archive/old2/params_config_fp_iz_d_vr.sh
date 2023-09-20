# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-50.0 -35.0 -20.0 -5.0 3.0 25.0 40.0)
p2_v=(-10.0000 -26.6667 -35.0 -43.3333 -58.53 -63.064175 -67.59835)
p3_v=(-39.52 -11.3733 -14.52 -6.1867 9.01 13.544175 18.07835)
p4_v=(-33.52 -5.3733 -8.52 -0.1867 15.01 19.544175 24.07835)
p5_v=(21.48 38.1467 46.48 54.8133 70.01 74.544175 79.07835)
p1_p="\"D\""
p2_p="\"VR\""
p3_p="\"VMIN\""
p4_p="\"VT\""
p5_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"