# param expoloration params

# select params
export paramexp_type=" \"tm\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_tm_" # folder name prefix
export run_on_hopper=0 # run from hopper's system 
export local_run=1 # local run number
export use_hopper_data=0 # access hopper data locally
export hopper_run=1 # hopper run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(18.7673 26.7995 34.8317 42.8639 50.8961)
export param2_vals=(0.1631 0.1990 0.2349 0.2708 0.3067)
export param3_vals=(17.2937 25.4503 33.6069 41.7635 49.9201)
export param4_vals=(0.1671 0.2027 0.2383 0.2739 0.3095)
export param5_vals=(19.4502 32.3958 45.3414 58.287 71.2326)
export param6_vals=(0.1972 0.2352 0.2732 0.3112 0.3492)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
