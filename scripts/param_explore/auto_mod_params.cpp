/*
    References: htlines://www.tutorialspoint.com/Read-whole-ASCII-file-into-Cplusplus-std-string
    htlines://cplusplus.com/reference/regex/regex_match/
    htlines://www.tutorialspoint.com/how-to-read-a-text-file-with-cplusplus
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

string dtos(double x)
{
  ostringstream ss;
  ss << x;
  return ss.str();
}

string alter_value(string line, regex param_pattern, double val_chg) {
    ostringstream new_line;
    smatch pattern_match;
    double val_dbl;
    string val_str;

    if (regex_match (line,param_pattern)) {
        cout << line << "\n";
        regex_match (line,pattern_match,param_pattern);
        val_dbl = stod(pattern_match[2]);
        val_dbl = val_dbl + val_chg;
        val_str = dtos(val_dbl);
        new_line << "[" << pattern_match[1] << val_str << pattern_match[3] << "] \n";
    }

    return new_line.str();
}

int main()
{
    fstream file;
    regex param_pattern("(.*MEC_LII_Stellate, )(\\d+.\\d+)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)");
    smatch pattern_match;
    file.open("../../generate_config_state.cpp",ios::in); //open a file to perform read operation using file object
    double val_dbl;
    string val_str;
    string line;
    string new_line;
    double val_chg = 10;

    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            new_line = alter_value(line, param_pattern, val_chg);
            cout << new_line;
        }
    }

    file.close(); //close the file object.   

    return 0;
}