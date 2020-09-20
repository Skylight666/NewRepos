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

	int cardinalityMM();

	multiSet unionMM(multiSet bag2);
	multiSet intersectionMM(multiSet bag2);
	multiSet complementationMM();
	multiSet differenceMM(multiSet bag2);
	multiSet sumMM(multiSet bag2);
	multiSet symmetricDifferenceMM(multiSet bag2);
	multiSet productMM(multiSet bag2);
};