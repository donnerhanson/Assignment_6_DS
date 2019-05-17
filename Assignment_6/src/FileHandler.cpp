//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : FileHandler.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : functions to open/close file in read safely
//================================================================

#include <iostream>
#include <fstream>
#include <string>


#include "Error.h"
#include "FileHandler.hpp"

using namespace std;



bool FileHandler::SafeOpenForRead(ifstream& inFile, string fileName)
{
    try{
        inFile.open(fileName, ios::in);
        if(inFile.is_open())
        {
            // uncomment below to show filename and success during runtime
            //cout << "File: <" << fileName << "> opened successfully...\n";
            file = &inFile;
            return true;
        }
        inFile.close();
        //throw Error ("File Not Found\n");
        return false;
    }
    catch(Error &e)
    {
        throw e;
    }
}

bool FileHandler::fileIsBlank(ifstream& inFile)
{
    return inFile.peek() == ifstream::traits_type::eof();
}

bool FileHandler::isNotWS(const string &str)
{
    return str.find_first_not_of(' ') != string::npos;
}

void FileHandler::Close()
{
    file->close();
}


