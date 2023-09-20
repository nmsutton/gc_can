# param expoloration params

# select params
export paramexp_type=" \"iz\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_iz_" # folder name prefix
export local_run=2 # local run number
export run_on_hopper=0 # run from hopper's system 
export use_hopper_data=0 # access hopper data locally
export hopper_run=2 # hopper run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(-65.0 -50.0 -35.0 -20.0 -5.0 3.0 25.0 40.0 55.0)
export param2_vals=(-28.5001 -25.7293 -22.9584 -20.1876 -17.4168 -14.6459 -11.8751 -9.1042 -6.3334)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";
export param_pattern2=" \"(.*sim.setNeuronParameters\\(MEC_LII_Stellate, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, [-]?\\d+[.]?\\d*f?, )([-]?\\d+[.]?\\d*)(.*)\"";