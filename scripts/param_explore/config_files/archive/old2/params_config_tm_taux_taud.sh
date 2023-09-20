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
export param1_vals=(0.1 64.0261 167.6862 271.3463 375.0064 478.6665 582.3266 685.9867 789.6468)
export param2_vals=(2.1912 2.6378 3.0844 3.5310 3.9775 4.4241 4.8707 5.3173 5.7639)
export param3_vals=(0.1 64.0261 167.6862 271.3463 375.0064 478.6665 582.3266 685.9867 789.6468)
export param4_vals=(2.1912 2.6378 3.0844 3.5310 3.9775 4.4241 4.8707 5.3173 5.7639)
export param5_vals=(0.1 64.0261 167.6862 271.3463 375.0064 478.6665 582.3266 685.9867 789.6468)
export param6_vals=(2.1912 2.6378 3.0844 3.5310 3.9775 4.4241 4.8707 5.3173 5.7639)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauX\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauX\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauX\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
