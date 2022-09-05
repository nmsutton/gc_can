# note: c++11 is needed due to some regex functions

rm auto_mod_params
#g++ -Wall -Werror -g -std=c++11 auto_mod_params.cpp -o auto_mod_params && ./auto_mod_params
g++ -Wall -g -std=c++11 auto_mod_params.cpp -o auto_mod_params && ./auto_mod_params \
"../../generate_config_state2.cpp" \
"(.*MEC_LII_Stellate, )(\\d+.*\\d*)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)" \
"-6"
