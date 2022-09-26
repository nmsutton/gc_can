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
    ostringstream new_line, tmp_text;
    smatch pattern_match;
    string origfile_text, newfile_text, line, line2, line3, line_str;
    fstream file;
    //bool match_found = false;
    int line_counter = 0;
    int match_line_num = 0;

    // read in file
    file.open(filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            new_line.str(""); // clear new line
            new_line.clear();
            new_line << line3 << line2 << line;
            line_str = new_line.str();
            //cout << line_str << "\n";
            //line_str = "sim.setNeuronParameters(MEC_LII_Stellate, 428.000000f, 0.0f, 2.04779049691647f, 0.0f, -59.1602652733878f, 0.0f, -43.2037684644403f,                                0.0f, 0.00753435323967846f, 0.0f, 88.8077035167208f, 0.0f, 11.8258859484417f, 0.0f, -49.616427055121f, 0.0f,                                 452.0f, 0.0f, 1);";
            if (regex_match (line,param_pattern)) {
                //cout<<"\nmatch\n";
                //cout<<pattern_match[2]<<"\n";
                //regex r2("[|]");
                //val_chg = regex_replace(val_chg,r2,"\n");
                newfile_text=newfile_text+val_chg+"\n";
                //cout<<val_chg;
                match_line_num=line_counter;
                //cout<<match_line_num;
            }        
            else if (match_line_num==0 || (line_counter!=match_line_num+1 && line_counter!=match_line_num+2)) {
                newfile_text=newfile_text+line+"\n";
            }    
            line3=line2;
            line2=line;
            line_counter++;
        }
    }
    file.close(); //close the file object.
    
    // search and replace
    /*cout << origfile_text.size() << "\n";
    regex param_pattern2(".*test.*"); 
    //cout << origfile_text;
    if (regex_match (origfile_text,param_pattern)) {
        //regex_match (origfile_text,pattern_match,param_pattern);
    }
    if (regex_match (origfile_text,param_pattern)) {
        cout<<"\nmatch\n";
    }
    else {
        //cout<<"\n"<<origfile_text<<"\n";
    }*/
    /*tmp_text << pattern_match[1] << val_chg << pattern_match[3] << "\n";
    newfile_text = tmp_text.str();*/
    //cout << newfile_text;
    //if (newfile_text.size() > 10) {
        //cout << newfile_text;
        //cout << newfile_text.size();
    //}

    if (newfile_text.size() > 10) { //(newfile_text != "") {
        fstream file2;
        string filepath2 = "../../general_config_state_test.cpp";
        file2.open(filepath2,ios::out); //open a file to perform read operation using file object
        file2 << newfile_text;    
        file2.close();
    }
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