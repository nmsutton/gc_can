# param expoloration params

# select params
export paramexp_type=" \"tm\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_tm_" # folder name prefix
export run_on_hopper=1 # run from hopper's system 
export local_run=1 # local run number
export use_hopper_data=0 # access hopper data locally
export hopper_run=1 # hopper run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(1.7049 2.6078 3.0845 4.4136 5.3165 6.2193 7.1222 8.0251 8.9280)
export param2_vals=(0.0970 0.4607 0.8245 1.1882 1.5519 1.9156 2.2793 2.6431 3.0068)
export param3_vals=(1.7049 2.6078 3.0845 4.4136 5.3165 6.2193 7.1222 8.0251 8.9280)
export param4_vals=(0.0970 0.4607 0.8245 1.1882 1.5519 1.9156 2.2793 2.6431 3.0068)
export param5_vals=(1.7049 2.6078 3.0845 4.4136 5.3165 6.2193 7.1222 8.0251 8.9280)
export param6_vals=(0.0970 0.4607 0.8245 1.1882 1.5519 1.9156 2.2793 2.6431 3.0068)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../general_params.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern2=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern4=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern6=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
