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
export param1_vals=(19.4502 27.0677 34.6852 42.3026 49.9201)
export param2_vals=(0.1972 0.2246 0.2520 0.2793 0.3067)
export param3_vals=(19.4502 27.0677 34.6852 42.3026 49.9201)
export param4_vals=(0.1972 0.2246 0.2520 0.2793 0.3067)
export param5_vals=(19.4502 27.0677 34.6852 42.3026 49.9201)
export param6_vals=(0.1972 0.2246 0.2520 0.2793 0.3067)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPu\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
