# parameter exploration settings

# select params
export paramexp_type=" \"tm\""; # choose iz (izhikevich) or tm (tsodyks-markram) parameters exploration
export fdr_prefix="param_explore_tm_" # folder name prefix
export run_on_supcomp=1 # run from supercomputer's system 
export local_run=2 # local run number
export use_supcomp_data=0 # access supercomputer data on a local computer
export supcomp_run=2 # supercomputer run number
export save_gridscore_file=1; # save gridscore to file
# Note: set number of vals in for statement {1..<count>} below
export param1_vals=(0.1094 0.1408 0.1672 0.1973 0.2349 0.2663 0.3066839824 0.3291 0.3605)
export param2_vals=(2.7046 10.7368 18.7690 26.8012 34.8334 42.8655 49.9201 58.9299 66.9621)
export param3_vals=(0.1094 0.1408 0.1672 0.1973 0.2349 0.2663 0.3066839824 0.3291 0.3605)
export param4_vals=(2.7046 10.7368 18.7690 26.8012 34.8334 42.8655 49.9201 58.9299 66.9621)
export param5_vals=(0.1094 0.1408 0.1672 0.1973 0.2349 0.2663 0.3066839824 0.3291 0.3605)
export param6_vals=(2.7046 10.7368 18.7690 26.8012 34.8334 42.8655 49.9201 58.9299 66.9621)
export param_file1=" \"../../generate_config_state.cpp\"";
export param_file2=" \"../../generate_config_state.cpp\"";
export param_pattern1=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPu\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern2=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Axo_Axonic, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern3=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPu\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern4=" \"(.*sim.setSTP\\(MEC_LII_Stellate, MEC_LII_Basket, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern5=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPu\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
export param_pattern6=" \"(.*sim.setSTP\\(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true,.*STPtauU\\()([-]?\\d+[.]?\\d*)(f?,.*)\"";
