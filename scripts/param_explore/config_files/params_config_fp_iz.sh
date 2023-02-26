# izhikevich model firing pattern parameter exploration parameters
# This is for K and A params

# select params
export run_on_hopper=0 # run from hopper's system 
export hopper_run=1 # hopper run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-48.0000 -48.6000 -49.2000 -49.8000 -50.4000 -51.0000 -51.6000 -52.2000 -52.8000 -53.4000 -54.0000)
p2_v=(-20.0 -32.0 -44.0 -56.0 -68.0 -80.0 -92.0 -104.0 -116.0 -128.0 -140.0)
p1_p="\"VMIN\""
p2_p="\"D\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"