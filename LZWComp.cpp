/** Encode and decode files using LZW method
 *
 *
 * */
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "LZWComp.h"
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>


using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;


//initialization of characters
LZWComp::LZWComp(string filename) {
    this->filename=filename;
    string a[] = {"A", "B", "C", "Ç", "D", "E", "F", "G", "Ð" , "H", "I", "Ý",  "J", "K", "L", "M", "N", "O", "Ö", "P", "Q", "R", "S", "Þ", "T",
                  "_", "U", "Ü","V", "W", "X", "Y", "Z", " ", "a", "b", "c", "ç", "d", "e", "f", "g", "ð" , "h", "ý", "i", "j", "k", "l", "m",
                  "n", "o", "ö", "p", "q", "r", "s", "þ", "t", "u", "ü","v", "w", "x", "y", "z", "#", "£", "!", "&", "$", "/", "(", ")",
                  "=", "?", "-", ">" , "'", "^", "+", "%", "{", "[", "]", "}","*","0","1","2","3","4","5","6","7","8","9"};


    {
        int n = sizeof(a) / sizeof(a[0]);
        for (int i = 0; i < n; i++) {
            directory.insert(a[i]);
        }
    }
}

void LZWComp::compress() {
    system("Color 8F");
    cout << "encrypting your file in a second" << endl;
    sleep(1);
    FILE* input_file = fopen(filename.c_str(), "r");
    string outfilename = filename.substr(0, filename.size()-4) + ".LZW";
    out_file.open(outfilename);

    char ch;
    string s ="";
    while(!feof(input_file)) {
            ch = getc(input_file);
            if (directory.ispresent(s+ch)) //dictionary contains s+ch
                {
               s = s + ch;
            } else {
                out_file << directory.getindex(s) << ",";//encode s to output file
                directory.insert(s+ch); //add s+ch to dictionary
                s = ch;
            }
        }
//encode s to output file;
    out_file.close();
    directory.exportHash(filename);
    cout << "Done!";
}


void LZWComp::decompress() {
    directory.importHash(filename);
    system("Color 84");
    cout << "decrypting your file in a second" << endl;
    sleep(1);

    FILE* input_file = fopen(filename.c_str(), "r");

    char comma;
    int commacount = 0;
    //count the commas to set a bound for loops
    while (!feof(input_file)) {
        comma = getc(input_file);
        if (comma == ',') {
            commacount++;
        }
    }

    FILE* input_file1 = fopen(filename.c_str(), "r");
    string outfilename = filename.substr(0, filename.size()-4) + ".txt";
    out_file.open(outfilename);

    char chin, chin1, ch;
    string temp, temp1, entry, entry0;
    int prevcode, currcode;

    int i = 0;
     for(chin = getc(input_file1);chin != ',' && i < commacount;chin = getc(input_file1)) {
         temp = temp + chin;
     }
    i++;

     prevcode = atoi( temp.c_str() ); //read in a code;
     temp = "";

    entry0 = directory.getValue(prevcode);
    out_file << entry0;  //decode/output prevcode;

    while (!feof(input_file1)) {
        for(chin1 = getc(input_file1);chin1 != ',' && i < commacount;chin1 = getc(input_file1) ) {
            temp1 = temp1 + chin1;
        }
        i++;

        currcode = atoi( temp1.c_str() );
        temp1 = "";

        entry = directory.getValue(currcode); //translation of currcode from dictionary;
        out_file << entry; //output entry;

        ch = entry[0];
        directory.insert(((directory.getValue(prevcode))+ch));
        prevcode = currcode; //terminate if bound is reached
        if (i == commacount)
            break;
     }
    out_file.close();  //close the file
    cout << "Done!";
}




