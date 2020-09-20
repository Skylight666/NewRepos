#include <QtWidgets>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <conio.h>
#include <ctype.h>

#include "multiset.h"

using namespace std;

int rho(int x)
{
    return x % 2 ? 0 : rho(x / 2) + 1;
}

int productOfArrayElements(int* array, int len)
{
    int prd = 1;
    while (len--)
    {
        prd *= array[len];
    }

    return prd;
}

void cout1Array(int* array, int len)
{
    for (int j = 0; j < len; ++j)
        cout << array[j];
    cout << endl;
}

void cout2Array(int** array, int rows, int cols)
{
    int number = 1;
    for (int i = 0; i < rows; ++i)
    {
        cout << number++ << ". "; //равнение по правому краю?
        for (int j = 0; j < cols; ++j)
            cout << array[i][j];
        cout << endl;
    }
}

int** genGrayCode(int* m, int lenOfTuple)
{
    int tupleCount = productOfArrayElements(m, lenOfTuple);

    int** storage = new int* [tupleCount];
    for (int i = 0; i < tupleCount; ++i)
        storage[i] = new int[lenOfTuple];

    int* a = new int[lenOfTuple];
    int* f = new int[lenOfTuple + 1];
    int* o = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; ++i)
    {
        a[i] = 0;
        o[i] = 1;
        f[i] = lenOfTuple - i;
    }
    f[lenOfTuple] = 0;

    int j = 0, numOfTuple = 0;
    do 
    {
        for (int k = 0; k < lenOfTuple; ++k)
        {
            storage[numOfTuple][k] = a[k]; //??? std::copy
        }
        ++numOfTuple;

        j = f[lenOfTuple];
        f[lenOfTuple] = 0;

        a[lenOfTuple - j - 1] += o[lenOfTuple - j - 1];
        if (a[lenOfTuple - j - 1] == 0 || a[lenOfTuple - j - 1] == m[lenOfTuple - j - 1] - 1)
        {
            o[lenOfTuple - j - 1] *= (-1);
            f[lenOfTuple - j] = f[lenOfTuple - j - 1];
            f[lenOfTuple - j - 1] = j + 1;
        }
    } while (j != lenOfTuple);

    return storage;
}

int getUIntValue(int min = 0)
{
    while (true)
    {
        int a;
        cin >> a;

        if (cin.fail() || a < min)
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Incorrect input, try again: ";
        }
        else
            return a;
    }
}

int main()
{
    unsigned int lenOfTuple = 0;

    cout << "Input lenght of tuples: ";
    lenOfTuple = getUIntValue();

    int* weights = new int [lenOfTuple];
    cout << "Input "<< lenOfTuple <<" weights (it must be >= 2) : ";
    for (int i = 0; i < lenOfTuple; ++i)
        weights[i] = getUIntValue(2);

    int tupleCount = productOfArrayElements(weights, lenOfTuple);
    int** storage = new int* [tupleCount];
    for (int i = 0; i < tupleCount; ++i)
        storage[i] = new int[lenOfTuple];

    storage = genGrayCode(weights, lenOfTuple);
    cout2Array(storage, tupleCount, lenOfTuple);

    int n1 = 0, n2 = 0;
    cout << "Input number of the first and the second bags: ";
    n1 = getUIntValue(1);
    n2 = getUIntValue(1);
    multiSet mm1(storage[n1 - 1], weights, lenOfTuple);
    multiSet mm2(storage[n2 - 1], weights, lenOfTuple);

    bool quit = false;
    
    
    while (!quit)
    {
        cout << "Choose operation. Press 1-9 to choose operation, n to choose new set and Esc to quit." <<\
            "1: Union of sets." << endl <<\
            "2: Intersection of sets." << endl << \
            "3: Sum of sets" << endl << \
            "4: Set 1 - Set 2." << endl << \
            "5: Set 2 - Set 1." << endl << \
            "6: Symmetric difference of sets." << endl << \
            "7 : Complement of set 1." << endl << \
            "8 : Complement of set 2." << endl << \
            "9: Product of sets." << endl << \
            "n: Choose new sets." << endl << \
            "Esc: Quit program." << endl << endl;

        char in = _getch();
        switch (in)
        {
            case '1':
            {
                cout << "Union of bags." << endl << endl;
                mm1.unionMM(mm2).out();
                break;
            }
            case '2':
            {
                cout << "Intersection of bags." << endl << endl;
                mm1.intersectionMM(mm2).out();
                break;
            }
            case '3':
            {
                cout << "Sum of bags." << endl << endl;                
                mm1.sumMM(mm2).out();
                break;
            }
            case '4':
            {
                cout << "Bag 1 - bag 2." << endl << endl;
                mm1.differenceMM(mm2).out();
                break;
            }
            case '5':
            {
                cout << "Bags 2 - bag 1." << endl << endl;
                mm2.differenceMM(mm1).out();
                break;
            }
            case '6':
            {
                cout << "Symmetric Difference of bags." << endl << endl;
                mm1.symmetricDifferenceMM(mm2).out();
                break;
            }
            case '7':
            {
                cout << "Complement of bag 1." << endl << endl;
                mm1.complementationMM().out();
                break;
            }
            case '8':
            {
                cout << "Complement of bag 2." << endl << endl;
                mm2.complementationMM().out();
                break;
            }
            case '9':
            {
                cout << "Product of bags." << endl << endl;
                mm1.productMM(mm2).out();
                break;
            }
            case 'n': 
            {
                cout << "Input number of two new sets: " << endl << endl;
                n1 = getUIntValue(1);
                n2 = getUIntValue(1);
                mm1.array = storage[n1 - 1];
                mm2.array = storage[n2 - 1];
                break; 
            }
            case 27:
            {
                cout << "Quit." << endl;
                quit = 1;
                break;
            }
            default:
            {
                cout << "Invalid input!" << endl;
                break;
            }
        }
    };
}
