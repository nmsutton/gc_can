# parameter exploration settings

# select params
export paramexp_type=" \"iz\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_iz_" # folder name prefix
export local_run=1 # local run number
export run_on_hopper=1 # run from hopper's system 
export use_hopper_data=0 # access hopper data locally
export hopper_run=1 # hopper run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(30.0000 47.5000 65.0000 82.5000 100.0000 118.0000 135.0000 152.5000 170.0000)
export param2_vals=(-56.7500 -54.4062 -52.0625 -49.52 -47.3750 -45.0312 -42.6875 -40.3438 -38.0000)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, )([-]?\\d+[.]?\\d*)(.*)\"";
export param_pattern2=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";