# parameter exploration settings

# select params
export paramexp_type=" \"iz\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_iz_" # folder name prefix
export local_run=1 # local run number
export run_on_supcomp=1 # run from supercomputer's system 
export use_supcomp_data=0 # access supercomputer data on a local computer
export supcomp_run=1 # supercomputer run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(0.1000 0.3333 0.62 1.0000 1.3333 1.6667 2.0000)
export param2_vals=(0.0020 0.0050 0.1680 0.2510 0.3340 0.4170 0.5000)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";
export param_pattern2=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";
