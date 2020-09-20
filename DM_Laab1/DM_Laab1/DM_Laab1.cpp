// DM_Laab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

int cardinalityOfBag(int* bag, int lenOfTuple)
{
    int sum = 0;
    while (lenOfTuple--)
    {
        sum += bag[lenOfTuple];
    }

    return sum;
}

int* unionOfBags(int* bag1, int* bag2, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = max(bag1[i], bag2[i]);
    }
    

    cout1Array(result, lenOfTuple);
    return result;
}

multiSet classUnionOfBags(multiSet bag1, multiSet bag2)
{
    multiSet result(bag1.weights, bag1.len);
    for (int i = 0; i < bag1.len; i++)
    {
        result[i] = max(bag1[i], bag2[i]);
    }

    result.out();
    return result;
}

int* intersection(int* bag1, int* bag2, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = min(bag1[i], bag2[i]);
    }

    cout1Array(result, lenOfTuple);
    return result;
}

int* complementation(int* bag, int* weights, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = weights[i] - bag[i];
    }

    cout1Array(result, lenOfTuple);
    return result;
}

int* difference(int* bag1, int* bag2, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = (bag1[i] < bag2[i]) ? 0 : bag1[i] - bag2[i];
    }

    cout1Array(result, lenOfTuple);
    return result;
}

int* summ(int* bag1, int* bag2, int* weights, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = (bag1[i] + bag2[i] > weights[i]) ? weights[i] : bag1[i] + bag2[i];
    }

    cout1Array(result, lenOfTuple);
    return result;
}

int* symmetricDifference(int* bag1, int* bag2, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = (bag1[i] < bag2[i]) ? bag2[i] - bag1[i] : bag1[i] - bag2[i];
    }

    cout1Array(result, lenOfTuple);
    return result;
}

int* product(int* bag1, int* bag2, int* weights, int lenOfTuple)
{
    int* result = new int[lenOfTuple];
    for (int i = 0; i < lenOfTuple; i++)
    {
        result[i] = (bag1[i] * bag2[i] > weights[i]) ? weights[i] : bag1[i] * bag2[i];
    }

    cout1Array(result, lenOfTuple);
    return result;
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


int main()
{
    int lenOfTuple = 0;

    cout << "Input lenght of tuples: ";
    cin >> lenOfTuple;

    int* weights = new int [lenOfTuple];
    cout << "Input "<< lenOfTuple <<" weights (it must be >= 2) : ";
    for (int i = 0; i < lenOfTuple; ++i)
        cin >> weights[i];

    int tupleCount = productOfArrayElements(weights, lenOfTuple);
    int** storage = new int* [tupleCount];
    for (int i = 0; i < tupleCount; ++i)
        storage[i] = new int[lenOfTuple];

    storage = genGrayCode(weights, lenOfTuple);
    cout2Array(storage, tupleCount, lenOfTuple);

    int n1 = 0, n2 = 0;
    cout << "Input number of the first and the second bags: ";
    cin >> n1 >> n2;
    int* bag1 = storage[n1 - 1];
    int* bag2 = storage[n2 - 1];
    multiSet mm1(storage[n1 - 1], weights, lenOfTuple);
    multiSet mm2(storage[n2 - 1], weights, lenOfTuple);

    bool quit = false;
    
    
    while (!quit)
    {
        printf_s("Choose operation. Press 1-9 to choose operation, n to choose new set and Esc to quit.\n1: Union of sets.\n2: Intersection of sets.\n3: Sum of sets\n4: Set 1 - Set 2.\n5: Set 2 - Set 1.\n");
        printf_s("6: Symmetric difference of sets.\n7 : Complement of set 1.\n8 : Complement of set 2.\n9: Product of sets.\nn: Choose new sets.\nEsc: Quit program.\n\n> ");

        char in = _getch();
        switch (in)
        {
            case '1':
            {
                cout << "Union of bags.\n\n";
                unionOfBags(bag1, bag2, lenOfTuple);
                mm1.unionMM(mm2).out();
                break;
            }
            case '2':
            {
                cout << "Intersection of bags.\n\n";
                intersection(bag1, bag2, lenOfTuple);
                mm1.intersectionMM(mm2).out();
                break;
            }
            case '3':
            {
                cout << "Sum of bags.\n\n";
                summ(bag1, bag2, weights, lenOfTuple);
                break;
            }
            case '4':
            {
                cout << "Bag 1 - bag 2.\n\n";
                difference(bag1, bag2, lenOfTuple);
                break;
            }
            case '5':
            {
                cout << "Bags 2 - bag 1.\n\n";
                difference(bag2, bag1, lenOfTuple);
                break;
            }
            case '6':
            {
                cout << "Symmetric Difference of bags.\n\n";
                symmetricDifference(bag1, bag2, lenOfTuple);
                break;
            }
            case '7':
            {
                cout << "Complement of bag 1.\n\n";
                complementation(bag1, weights, lenOfTuple);
                break;
            }
            case '8':
            {
                cout << "Complement of bag 2.\n\n";
                complementation(bag2, weights, lenOfTuple);
                break;
            }
            case '9':
            {
                cout << "Product of bags.\n\n";
                product(bag1, bag2, weights, lenOfTuple);
                break;
            }
            case 'n': 
            {
                cout << "Input number of two new sets: \n\n";
                cin >> n1 >> n2;
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
                cout << "Invalid input!\n";
                break;
            }
        }
    };
}
