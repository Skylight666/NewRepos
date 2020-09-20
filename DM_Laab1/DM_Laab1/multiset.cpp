#include <iostream>
#include <cstdio>
#include <math.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

#include "multiset.h"

multiSet::multiSet(int* array, int* weights, int len)
{
	(*this).array = array;
	(*this).weights = weights;
	(*this).len = len;
}

multiSet::multiSet(int* weights, int len)
{
	(*this).array = new int[len];
	(*this).weights = weights;
	(*this).len = len;
}

int& multiSet::operator[] (int i)
{
	return (*this).array[i];
}

void multiSet::out()
{
	for (int j = 0; j < (*this).len; ++j)
		cout << (*this).array[j];
	cout << endl;
}

int multiSet::cardinalityMM()
{
	int sum = 0;
	for (int i = 0; i < (*this).len; i++)
	{
		sum += (*this)[i];
	}

	return sum;
}

multiSet multiSet::unionMM(multiSet bag2)
{
	multiSet result((*this).weights, (*this).len);
	for (int i = 0; i < (*this).len; i++)
	{
		result[i] = max((*this)[i], bag2[i]);
	}

	return result;
}

multiSet multiSet::intersectionMM(multiSet bag2)
{
	multiSet result((*this).weights, (*this).len);
	for (int i = 0; i < (*this).len; i++)
	{
		result[i] = min((*this)[i], bag2[i]);
	}

	return result;
}

multiSet multiSet::complementationMM()
{
    multiSet result((*this).weights, (*this).len);
    for (int i = 0; i < (*this).len; i++)
    {
        result[i] = (*this).weights[i] - (*this)[i];
    }
    
    return result;
}

multiSet multiSet::differenceMM(multiSet bag2)
{
    multiSet result((*this).weights, (*this).len);
    for (int i = 0; i < (*this).len; i++)
    {
        result[i] = ((*this)[i] < bag2[i]) ? 0 : (*this)[i] - bag2[i];
    }
   
    return result;
}

multiSet multiSet::sumMM(multiSet bag2)
{
    multiSet result((*this).weights, (*this).len);
    for (int i = 0; i < (*this).len; i++)
    {
        result[i] = ((*this)[i] + bag2[i] > (*this).weights[i]) ? (*this).weights[i] : (*this)[i] + bag2[i];
    }
  
    return result;
}

multiSet multiSet::symmetricDifferenceMM(multiSet bag2)
{
    multiSet result((*this).weights, (*this).len);
    for (int i = 0; i < (*this).len; i++)
    {
        result[i] = ((*this)[i] < bag2[i]) ? bag2[i] - (*this)[i] : (*this)[i] - bag2[i];
    }
    
    return result;
}

multiSet multiSet::productMM(multiSet bag2)
{
    multiSet result((*this).weights, (*this).len);
    for (int i = 0; i < (*this).len; i++)
    {
        result[i] = ((*this)[i] * bag2[i] > (*this).weights[i]) ? (*this).weights[i] : (*this)[i] * bag2[i];
    }

    return result;
}