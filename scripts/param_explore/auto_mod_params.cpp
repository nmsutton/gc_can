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

void alter_value(regex param_pattern, double val_chg, string filepath) {
    ostringstream new_line;
    smatch pattern_match;
    double val_dbl;
    string val_str, newfile_text, line;
    fstream file;

    file.open(filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            new_line.str(""); // clear new line
            new_line.clear();
            if (regex_match (line,param_pattern)) {
                //cout << line << "\n";
                regex_match (line,pattern_match,param_pattern);
                val_dbl = stod(pattern_match[2]);
                val_dbl = val_dbl + val_chg;
                val_str = dtos(val_dbl);
                new_line << pattern_match[1] << val_str << pattern_match[3] << "\n";
            }
            else {
                new_line << line << "\n";
            }
            newfile_text = newfile_text + new_line.str();
        }
    }
    file.close(); //close the file object.

    fstream file2;
    file2.open("../../generate_config_state2.cpp",ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;
    file2.close();
}

int main()
{
    fstream file;
    string filepath = "../../generate_config_state.cpp";
    string line, newfile_text;

    /*
    regex param_pattern("(.*MEC_LII_Stellate, )(\\d+.\\d+)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)");
    file.open(filepath,ios::in); //open a file to perform read operation using file object
    double val_chg = 20;
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            newfile_text = newfile_text + alter_value(line, param_pattern, val_chg);
        }
    }
    file.close(); //close the file object. 

    fstream file2;
    file2.open("../../generate_config_state2.cpp",ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;
    file2.close(); 
    */
    regex param_pattern("(.*MEC_LII_Stellate, )(\\d+.\\d+)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)");
    double val_chg = 25;
    alter_value(param_pattern, val_chg, filepath);     

    return 0;
}