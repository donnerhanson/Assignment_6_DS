//
//  main.cpp
//  SortingAlgorithms
//
//  Created by Donner Hanson on 5/7/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <cstdint> // include this header for uint64_t
using std::string;
using namespace std;
#include "DynamicArray.h"

//const string FILE_NAME = "doubles.txt";
//const double DBL_MAX = 1000.56;

const string BS = "BubbleSort";
const string MS = "MergeSort";
const string IS = "InsertionSort";
const string SS = "SelectionSort";
const string QS = "QuickSort";

void
CheckSort(DynamicArray<double> &);
void
printResults(string sortType, DynamicArray<double>& arr, std::chrono::high_resolution_clock::time_point timeOne, std::chrono::high_resolution_clock::time_point timeTwo, string beginTimeDate, string endTimeDate)
{
    long long int duration = std::chrono::duration_cast<std::chrono::microseconds>( timeTwo - timeOne ).count();
    cout << sortType << ":\nBegin: " << beginTimeDate << "\nEnd: " << endTimeDate << "\nTime in microseconds: " << duration << "\n\n";
}
//https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
string return_current_time_and_date()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    long in_time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X %Z");
    return ss.str();
}
double StringToDouble(string &str)
{
    double number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}
int StringToInt(string &str)
{
    int number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}
bool checkForDouble(std::string const& s) {
    std::istringstream ss(s);
    double d;
    return (ss >> d) && (ss >> std::ws).eof();
}
bool checkForInt(std::string const& s) {
    std::istringstream ss(s);
    int d;
    return (ss >> d) && (ss >> std::ws).eof();
}
int main(int argc, const char * argv[]) {
    
//    std::random_device rd;
//    std::mt19937 mt(rd());
//    std::uniform_real_distribution<double>dist(1.1, DBL_MAX);
    try{
        if (argc < 2)
        {
            throw Error("Too few arguments...\n Expected <FileName.txt> parameter\nExiting...");
        }
        if (argc > 2)
        {
            throw Error("Too many arguments...\n Expected <FileName.txt> parameter\nExiting...\n");
        }
        string fileName (argv[1]);
    DynamicArray <double> arr;

//    for (int i(0); i < NUM_ENTRIES; ++i)
//         arr.insert(dist(mt));
    
    
    std::fstream inDoubles( fileName, std::ios::in);
    if( !inDoubles.is_open() )
    {
        throw Error("File not found...\nExiting...\n");
    }
    else if( inDoubles.is_open() )
    {
        string strNum;
        double num;
        bool firstLine(true);
        int numItems = 0;
        int count = 0;
        while (inDoubles >> strNum)
        {
            if (firstLine && checkForInt(strNum))
            {
                numItems = StringToInt(strNum);
                cout << "Number of Items to sort: " << strNum << "\n\n";
                firstLine = false;
            }
            else if (checkForDouble(strNum))
            {
                num = StringToDouble(strNum);
                arr.insert(num);
                count++;
            }
            if (numItems == count)
            {
                break;
            }
        }
        if (numItems != count)
        {
            inDoubles.close();
            throw Error("Reached end of file before specified number of items to sort...\nPlease adjust number of items to sort and restart program...\n");
        }
        cout << "File Read Successful...\n\n";
        inDoubles.close();
    }
    // 46 528 380
    // 196 166 869


    cout << "Initial Array Filled...\n";
    cout << "Copy 1...\n";
    DynamicArray<double> arrTwo(arr);
    cout << "Copy 2...\n";
    DynamicArray<double> arrThree(arr);
    cout << "Copy 3...\n";
    DynamicArray<double> arrFour(arr);
    cout << "Copy 4...\n\n";
    DynamicArray<double> arrFive(arr);


    string beginTimeDate = return_current_time_and_date();
    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    arr.bubbleSort();
    std::chrono::high_resolution_clock::time_point EndTime = std::chrono::high_resolution_clock::now();
    string endTimeDate = return_current_time_and_date();
    //CheckSort(arr);
    printResults(BS, arr, beginTime, EndTime, beginTimeDate, endTimeDate);


    beginTimeDate = return_current_time_and_date();
    beginTime = std::chrono::high_resolution_clock::now();
    arrTwo.selectionSort();
    EndTime = std::chrono::high_resolution_clock::now();
    endTimeDate = return_current_time_and_date();
    //CheckSort(arrTwo);
    //cout << "SelectionSort:\n" << arrTwo << "\n\n";
    printResults(SS, arrTwo, beginTime, EndTime, beginTimeDate, endTimeDate);

    beginTimeDate = return_current_time_and_date();
    beginTime = std::chrono::high_resolution_clock::now();
    arrThree.InsertionSort();
    EndTime = std::chrono::high_resolution_clock::now();
    endTimeDate = return_current_time_and_date();
    printResults(IS, arrThree, beginTime, EndTime, beginTimeDate, endTimeDate);

    beginTimeDate = return_current_time_and_date();
    beginTime = std::chrono::high_resolution_clock::now();
    arrFour.MergeSort(0, arrFour.Size()-1);
    EndTime = std::chrono::high_resolution_clock::now();
    endTimeDate = return_current_time_and_date();
    printResults(MS, arrFour, beginTime, EndTime, beginTimeDate, endTimeDate);

    beginTimeDate = return_current_time_and_date();
    beginTime = std::chrono::high_resolution_clock::now();
 arrFive.quickSort(0, arrFive.Size()-1);
    EndTime = std::chrono::high_resolution_clock::now();
    endTimeDate = return_current_time_and_date();
    printResults(QS, arrFive, beginTime, EndTime, beginTimeDate, endTimeDate);
//
//cout << arr << "\n\n";
//    cout << arrTwo << "\n\n";
//    cout << arrThree << "\n\n";
//    cout << arrFour << "\n\n";
//    cout << arrFive << "\n\n";
//    CheckSort(arrFive);
//    cout << "QuickSort:\n" << arrFive << "\n\n";
    return 0;
    }
    catch(Error &e)
    {
        cout << e.what();
        return EXIT_FAILURE;
    }
}
void
CheckSort(DynamicArray<double> &arr)
{
    double temp(-1.0);
    double curr;
    for (int i(0); i < arr.Size() ; i++)
    {
        curr = arr.at(i);
        if (temp < curr)
        {
            temp = curr;
        }
        else
        {
            cout << "sorting error\n";
        }
    }
}
