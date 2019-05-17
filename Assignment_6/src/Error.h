//================================================================
// Author      : Donner Hanson
// Date        : 04/23/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty BST DataBase
// File Name   : Error.h
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Custom runtime error class
//================================================================
#ifndef Error_h
#define Error_h

#include <stdexcept>
#include <string>
using namespace std;

class Error : public runtime_error
{
public:
    Error() : runtime_error("Something Bad Happened..."){}
    Error(string msg):runtime_error(msg.c_str()){}
private:
    
};

#endif /* Error_h */

