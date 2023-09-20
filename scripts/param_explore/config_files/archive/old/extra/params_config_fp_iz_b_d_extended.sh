# izhikevich model firing pattern parameter exploration parameters
# VT and B. Value ranges were selected based on the original json
# file and HCO listed IZ values for MEC LII Stellate

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-25.0000   -9.3750    6.2500   21.8750   37.5000   53.1250   68.7500   84.3750 100.0000)
p2_v=(-40.0000  -33.7500  -27.5000  -21.2500  -15.0000   -8.7500   -2.5000    3.7500 10.000)
p1_p="\"D\""
p2_p="\"B\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"