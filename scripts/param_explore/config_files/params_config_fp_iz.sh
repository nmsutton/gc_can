# izhikevich model firing pattern parameter exploration parameters

# select params
export run_on_supcomp=0 # run from supercomputer's system 
export supcomp_run=1 # supercomputer run number
# Note: set number of vals in for statement {1..<count>} below
p1_v=(-60.0000 -42.5000 -25.0000 -7.5000 10.0000 27.5000 45.0000 62.5000 80.0000)
p2_v=(-66.5300 -64.0300 -61.5300 -59.0300 -56.5300 -54.0300 -51.5300 -49.0300 -46.5300)
p3_v=(17.0100 14.5100 12.0100 9.5100 7.0100 4.5100 2.0100 -0.4900 -2.9900)
p4_v=(23.0100 20.5100 18.0100 15.5100 13.0100 10.5100 8.0100 5.5100 3.0100)
p5_v=(78.0100 75.5100 73.0100 70.5100 68.0100 65.5100 63.0100 60.5100 58.0100)
p1_p="\"D\""
p2_p="\"VR\""
p3_p="\"VMIN\""
p4_p="\"VT\""
p5_p="\"VPEAK\""
input_path="input/11/3a/6-019-1.json"
output_path="output/11/3a/6-019-1/local/job.0.Full"