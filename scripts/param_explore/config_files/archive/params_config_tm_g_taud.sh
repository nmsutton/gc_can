# parameter exploration settings

# select params
export paramexp_type=" \"tm\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_tm_" # folder name prefix
export run_on_supcomp=1 # run from supercomputer's system 
export local_run=1 # local run number
export use_supcomp_data=0 # access supercomputer data on a local computer
export supcomp_run=1 # supercomputer run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(1.7049 2.4168 3.0845 3.8406 4.5525 5.2643 5.9762 6.6881 7.4000)
export param2_vals=(0.0970 0.4099 0.7228 1.0501 1.3485 1.6614 1.9743 2.2871 2.6000)
export param3_vals=(1.7049 2.4168 3.0845 3.8406 4.5525 5.2643 5.9762 6.6881 7.4000)
export param4_vals=(0.0970 0.4099 0.7228 1.0501 1.3485 1.6614 1.9743 2.2871 2.6000)
export param5_vals=(1.7049 2.4168 3.0845 3.8406 4.5525 5.2643 5.9762 6.6881 7.4000)
export param6_vals=(0.0970 0.4099 0.7228 1.0501 1.3485 1.6614 1.9743 2.2871 2.6000)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../general_params.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern2=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern4=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtdAMPA\\()([-]?\\d+[.]*\\d*)(f?,.*)\"";
export param_pattern6=" \".*(double grc_to_in_g_fast = )([-]?\\d+[.]*\\d*)(.*)\"";
