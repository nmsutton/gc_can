/*
    Author: Nate Sutton, 2022

    References:
    https://stackoverflow.com/questions/3383817/limit-floating-point-precision
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <regex>
#include <math.h>

using namespace std;

double set_prec(double value, double precision)
{
    return (floor((value * pow(10, precision) + 0.5)) / pow(10, precision)); 
}

string to_string2(double x)
{
  ostringstream ss;
  ss << x;
  return ss.str();
}

void process_scores(regex score_pattern, double threshold, string input_filepath, 
    string output_filepath) {
    string origfile_text, newfile_text, line;
    string fit_score="";
    fstream file;
    bool thresh_found = false;
    smatch sm;
    //regex space = R"\s+";

    file.open(input_filepath,ios::in); //open a file to perform read operation using file object
    if (file.is_open()){ //checking whether the file is open
        while(getline(file, line)){ //read data from file object and put it into string.
            if (regex_match(line,sm,score_pattern) && (stod(sm[1]) > threshold*2)) {
                //fit_score = (string) sm[1]; // full fitness score
                fit_score = to_string2(set_prec(stod(sm[1]),4)); // shortened score
                thresh_found = true;
            }        
            else if (thresh_found == true) {
                line = regex_replace(line, regex("\\s"), "\t ");
                newfile_text=newfile_text+line+" "+fit_score+"\n";
                thresh_found = false;
            }    
        }
    }
    file.close(); //close the file object.

    fstream file2;
    file2.open(output_filepath,ios::out); //open a file to perform read operation using file object
    file2 << newfile_text;    
    file2.close();
}

int main(int argc, char** argv)
{
    /*
        Extract parameters that fit a fitness score threshold
    */
    string input_filepath = "output/param_records_ea_iz.txt";
    string output_filepath = "output/param_records_ea_iz_thresh.txt";
    regex score_pattern("Fitness: ([-]?\\d+[.]?\\d*)");
    double threshold = -3.9981555938720703;

    process_scores(score_pattern, threshold, input_filepath, output_filepath);

    cout << "completed\n";

    return 0;
}