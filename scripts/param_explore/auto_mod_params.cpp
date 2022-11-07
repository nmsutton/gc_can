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

void alter_value(regex param_pattern, string val_chg, string filepath) {
    string origfile_text, newfile_text, line;
    fstream file;

    file.open(filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            if (regex_match (line,param_pattern)) {
                newfile_text=newfile_text+val_chg+"\n";
            }        
            else {
                newfile_text=newfile_text+line+"\n";
            }    
        }
    }
    file.close(); //close the file object.

    fstream file2;
    //string filepath2 = "../../general_params_test.cpp";
    file2.open(filepath,ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;    
    file2.close();
}

void alter_value_indiv(regex param_pattern, string val_chg, string filepath) {
    // alter individual value in line not whole line at a time

    string origfile_text, newfile_text, line;
    fstream file;
    smatch sm;

    file.open(filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            if (regex_match (line,param_pattern)) {
                regex_match(line,sm,param_pattern);
                newfile_text=newfile_text+sm[1].str()+val_chg+sm[3].str()+"\n";
                //cout << sm[1].str()+val_chg+sm[3].str() << "\n";
            }        
            else {
                newfile_text=newfile_text+line+"\n";
            }    
        }
    }
    file.close(); //close the file object.

    fstream file2;
    //string filepath2 = "../../generate_config_state_test.cpp";
    file2.open(filepath,ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;    
    file2.close();
}

int main(int argc, char** argv)
{
    /*
        Change parameter file's values based on input from command line arguments

    */
    if (argc != 5) {
        cout<<"Usage: auto_mod_params <paramexp_type> <param_file> <param_pattern> <value_change>\n\n";
        cout<<"4 command line arguments are needed for running this program.\n";
    }
    else {
        string paramexp_type = argv[1];
        string filepath = argv[2];
        regex param_pattern((string) argv[3]);
        string val_chg = (string) argv[4];        

        // process input param value
        if (paramexp_type=="iz" || paramexp_type=="tm") {
            alter_value_indiv(param_pattern, val_chg, filepath);
        }
        else {
            alter_value(param_pattern, val_chg, filepath);     
        }
    }

    return 0;
}