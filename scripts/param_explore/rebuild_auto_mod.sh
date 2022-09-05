# note: c++11 is needed due to some regex functions

rm auto_mod_params
#g++ -Wall -Werror -g -std=c++11 auto_mod_params.cpp -o auto_mod_params && ./auto_mod_params
g++ -Wall -g -std=c++11 auto_mod_params.cpp -o auto_mod_params && ./auto_mod_params
