//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : FileHandler.hpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : interface to open/close file in read safely
//================================================================

#ifndef FileHandler_hpp
#define FileHandler_hpp

#include <fstream>
#include <iostream>
#include <string>

#include "Error.h"


using namespace std;


class FileHandler{
public:
    ~FileHandler(){};
    bool SafeOpenForRead(ifstream& inFile, string fileName);
    bool fileIsBlank(ifstream& inFile);
    bool isNotWS(const string &str);
    void Close();
    ifstream* getReadFile()
    {
        return file;
    }
    ofstream* getOutFile()
    {
        return ofile;
    }
private:
    ifstream* file;
    ofstream* ofile;
    // for returning a value to outside queue
    int a;
};

#endif /* FileHandler_hpp */
