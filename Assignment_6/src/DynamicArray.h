//
//  DynamicArray.h
//  SortingAlgorithms
//
//  Created by Donner Hanson on 5/7/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef DynamicArray_h
#define DynamicArray_h


#include <iostream>
using std::cout;
#include "Error.h"


const int MAX_S = 10;

template <typename T>
class DynamicArray
{
    friend std::ostream& operator<<( std::ostream& o, const DynamicArray& t )
    {
        for (int i(0); i < t.numElems; i++)
        {
            o << t.internalArray[i] << " ";
        }
        return o;
    }
public:
    DynamicArray()
    {
        sizeOfArr = MAX_S;
        internalArray = new T[sizeOfArr];
        numElems = 0;
        
    }
    
    // Destructor
    ~DynamicArray()
    {
        delete [] internalArray;
    }
    
    // copy constructor
    DynamicArray(const DynamicArray<T>& source )
    {
        internalArray = new T[source.sizeOfArr];
        sizeOfArr = source.sizeOfArr;
        numElems = source.numElems;
        for (int i(0); i < sizeOfArr; i++)
        {
            internalArray[i] = source.internalArray[i];
            
        }
        
    }
    
    // assignment operator
    void operator = (const DynamicArray<T> &source)
    {
        delete [] internalArray;
        internalArray = new T[source.sizeOfArr];
        sizeOfArr = source.sizeOfArr;
        numElems = source.numElems;
        for (int i(0); i < numElems; i++)
        {
            internalArray[i] = source.internalArray[i];
        }
        
    }
    
    void makeDoubleLarger()
    {
        int copySize = sizeOfArr + sizeOfArr;
        T* copyArr = new T[copySize];
        
        for (int i(0); i < numElems; i++)
        {
            T tempNum = internalArray[i];
            copyArr[i] = tempNum;
        }
        
        T* temp = copyArr;
        copyArr = internalArray;
        internalArray = temp;
        
        delete [] copyArr;
        sizeOfArr = copySize;
    }
    T& at(const int index)
    {
        return internalArray[index];
    }
    void insert(const T input)
    {
        
        if( numElems > sizeOfArr - 1 )
        {
            makeDoubleLarger();
        }
        internalArray[numElems++] = input;
    }
    
    // for direct access - manipulation
    T &operator[](const int i)
    {
        numElems++;
        if( i > sizeOfArr - 1 )
        {
            makeDoubleLarger();
        }
        return internalArray[i];
    }
    
    // for constant object - reading only
    T const &operator[](const int i) const
    {
        if( i > sizeOfArr - 1 )
        {
            throw Error("Out Of range\n");
        }
        return internalArray[i];
    }
    
    
    void PrintArr()
    {
        for(int i(0);i < numElems; i++)
        {
            cout << internalArray[i] << " ";
            if (i > 0 && (i % 10) == 0)
            {
                cout << "\n";
            }
        }
        cout << "\n";
    }

    void bubbleSort()
    {
        int i, j;
        for (i = 0; i < numElems; i++)
            
            // Last i elements are already in place
            for (j = 0; j < numElems - i - 1; j++)
                if (internalArray[j] > internalArray[j+1])
                    swapValue(&internalArray[j], &internalArray[j+1]);
    }
    
    void selectionSort()
    {
        int i,j, minIndex;
        for (i = 0; i < numElems - 1; i++)
        {
            minIndex = i;
            for (j = i + 1; j < numElems; j++)
                if (internalArray[j] < internalArray[minIndex])
                    minIndex = j;
            if (minIndex != i)
            {
                swapValue(&internalArray[i], &internalArray[minIndex]);
            }
        }
    }
    
    void InsertionSort()
    {
        for (int j(1); j < numElems; ++j) // j is the marker
        {
            double temp = internalArray[j]; // store the marked item
            int k = j; // where to start shifting
            while (k > 0 && internalArray[k - 1] >= temp) // while the thing to the left is larger, shift
            {
                internalArray[k] = internalArray[k-1];
                --k;
            }
            internalArray[k] = temp; // put marked item in the correct location
        }
    }
    
    void MergeSort(int lowestIndex, int highestIndex)
    {
        int middleIndex;
        if (lowestIndex < highestIndex)
        {
            
            middleIndex = (lowestIndex+highestIndex)/2;
            MergeSort(lowestIndex, middleIndex);
            MergeSort(middleIndex + 1, highestIndex);
            Merge(lowestIndex, highestIndex);
        }
    }
    
    void Merge(int lowestIndex, int highestIndex)
    {
        int i,j,k,m,n = highestIndex-lowestIndex + 1; // size of smaller array
        T* arrTemp = new T[n]; // temp array
        k = 0;
        
        m = (lowestIndex + highestIndex)/2;
        // copy lower half to arrTemp
        for (i = lowestIndex; i <= m; i++)
            arrTemp[k++] = internalArray[i];
        //copy the upper half into the arrayTemp in opposite order
        for (j = highestIndex; j >= m + 1; j--)
            arrTemp[k++] = internalArray[j];
        
        i = 0; j = n - 1; k = lowestIndex;
        // copy back next greatest element at each time
        // until i and j cross
        while (i<=j)
        {
            if (arrTemp[i]<= arrTemp[j])
                internalArray[k++] = arrTemp[i++];
            else
                internalArray[k++] = arrTemp[j--];
        }
        delete [] arrTemp;
    }
    
    
    // https://www.geeksforgeeks.org/cpp-program-for-quicksort/
    /* This function takes last element as pivot, places
     the pivot element at its correct position in sorted
     array, and places all smaller (smaller than pivot)
     to left of pivot and all greater elements to right
     of pivot */
    int partition ( int low, int high)
    {
        T pivot = internalArray[high];    // pivot
        int i = (low - 1);  // Index of smaller element
        
        for (int j = low; j <= high- 1; j++)
        {
            // If current element is smaller than or
            // equal to pivot
            if (internalArray[j] <= pivot)
            {
                i++;    // increment index of smaller element
                swapValue(&internalArray[i], &internalArray[j]);
            }
        }
        swapValue(&internalArray[i + 1], &internalArray[high]);
        return (i + 1);
    }
    
    /* The main function that implements QuickSort
     arr[] --> Array to be sorted,
     low  --> Starting index,
     high  --> Ending index */
    void quickSort( int low, int high)
    {
        if (low < high)
        {
            /* pi is partitioning index, arr[p] is now
             at right place */
            int pi = partition(low, high);
            
            // Separately sort elements before
            // partition and after partition
            quickSort( low, pi - 1);
            quickSort( pi + 1, high);
        }
    }
    
    int Size() const
    {
        return numElems;
    }
    
private:
    T* internalArray;
    int sizeOfArr;
    int numElems;
    
    
    void swapValue(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }
};

#endif /* DynamicArray_h */
