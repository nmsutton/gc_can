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
                regex_match (line,pattern_match,param_pattern);
                val_dbl = stod(pattern_match[2]);
                //val_dbl = val_dbl + val_chg;
                val_dbl = val_chg;
                val_str = to_string(val_dbl);
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
    file2.open(filepath,ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;    
    file2.close();
}

int main(int argc, char** argv)
{
    /*
        Change parameter file's values based on input from command line arguments

    */
    if (argc != 4) {
        cout<<"Usage: auto_mod_params <param_file> <param_pattern> <value_change>\n\n";
        cout<<"3 command line arguments are needed for running this program. For example:\n";
        cout<<"auto_mod_params \"../../generate_config_state2.cpp\" \\\n";
        cout<<"\"(.*MEC_LII_Stellate, )(\\d+.*\\d*)(f, 0.0f, 0.98f, 0.0f, -58.53f, 0.0f, -43.52f.*)\" \\\n";
        cout<<"-25\n";
    }
    else {
        string filepath = argv[1];
        regex param_pattern((string) argv[2]);
        double val_chg = stod(argv[3]);
        alter_value(param_pattern, val_chg, filepath);     
    }

    return 0;
}