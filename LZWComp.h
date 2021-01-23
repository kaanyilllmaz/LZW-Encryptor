//
// Created by Kaan on 15.01.2021.
//

#ifndef LZW_LZWCOMP_H
#define LZW_LZWCOMP_H

#include <iostream>
#include <string>
#include <fstream>
#include "DoubleHash.cpp"


using namespace std;

class LZWComp {
public:
    LZWComp(string filename);
    void compress();
    void decompress();
    DoubleHash directory;
    ofstream out_file;
    string filename;
};
#endif //LZW_LZWCOMP_H
