# parameter exploration settings

# select params
export run_on_supcomp=0 # run from supercomputer's system 
export supcomp_run=1 # supercomputer run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(7.0 9.0 11.0 13.0 15.01 17.0 19.0 21.0 23.0)
p2_v=(62.0 64.0 66.0 68.0 70.01 72.0 74.0 76.0 78.0)
p1_p="\"VT\""
p2_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"
