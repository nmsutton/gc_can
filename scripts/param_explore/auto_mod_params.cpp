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

void alter_value_iz(regex param_pattern, string val_chg, string filepath) {
    /*
        This function detects and replaces a 3-line IZ params text segment.
    */

    ostringstream new_line;
    smatch pattern_match;
    string origfile_text, newfile_text, line;
    fstream file;
    int line_counter = 0;
    int match_line_num = 0;

    file.open(filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            if (regex_match (line,param_pattern)) {
                newfile_text=newfile_text+val_chg+"\n";
                match_line_num=line_counter;
            }        
            else if (match_line_num==0 || 
                (line_counter!=match_line_num+1 && line_counter!=match_line_num+2)) {
                newfile_text=newfile_text+line+"\n";
            }    
            line_counter++;
        }
    }
    file.close(); //close the file object.

    fstream file2;
    string filepath2 = "../../general_config_state_test.cpp";
    file2.open(filepath2,ios::out); //open a file to perform read operation using file object
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
        string iz_pattern = ".*setNeuronParameters.*";
        regex iz_test(iz_pattern);
        smatch iz_match;

        string filepath = argv[1];
        regex param_pattern((string) argv[2]);
        if (regex_match (argv[3],iz_test)) {
            // process iz file
            string val_chg = (string) argv[3];
            //cout<<"\n"<<(string) argv[2]<<"\n";
            alter_value_iz(param_pattern, val_chg, filepath);
        }
        else {
            // process input param value
            double val_chg = stod(argv[3]);
            alter_value(param_pattern, val_chg, filepath);     
        }
    }

    return 0;
}