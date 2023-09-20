# param expoloration params

# select params
export paramexp_type=" \"iz\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_iz_" # folder name prefix
export local_run=1 # local run number
export run_on_hopper=0 # run from hopper's system 
export use_hopper_data=0 # access hopper data locally
export hopper_run=1 # hopper run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(-10.0000 -26.6667 -35.0 -43.3333 -58.53 -63.064175 -67.59835)
export param2_vals=(-50.0 -35.0 -20.0 -5.0 3.0 25.0 40.0)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";
export param_pattern2=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";