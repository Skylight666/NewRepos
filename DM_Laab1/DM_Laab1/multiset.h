#pragma once
class multiSet
{
public:
	int* array, * weights;
	int len;
	multiSet(int* array, int* weights, int len);
	multiSet(int* weights, int len);
	int& operator[] (int i);
	void out();
	multiSet unionMM(multiSet bag2);
	multiSet intersectionMM(multiSet bag2);
};