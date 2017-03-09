#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <iostream>


void Separation(std::vector<int> & arr, int startPos, int endPos)
{
	std::vector<int> newArr(endPos - startPos + 1);
	int half = newArr.size() / 2;
	for (int i = 0; i < half; i++)
	{
		if (arr[startPos + i * 2] > arr[startPos + i * 2 + 1])
			std::swap(arr[startPos + i * 2], arr[startPos + i * 2 + 1]);
		newArr[i] = arr[startPos + i * 2];
		newArr[i + half] = arr[startPos + i * 2 + 1];
	}

	for (int i = 0; i < newArr.size(); i++)
		arr[startPos + i] = newArr[i];
}

void Compexch(int & a, int & b)
{
	if (a > b)
		std::swap(a, b);
}

void Merge(std::vector<int> & arr, int startPos, int endPos)
{
	std::vector<int> newArr(endPos - startPos + 1);
	int half = (endPos + startPos) / 2;
	for (int i = 0; i < newArr.size(); i+=2)
	{
		newArr[i] = arr[startPos+ i / 2];
		newArr[i + 1] = arr[half + i / 2 + 1];
	}

	for (int i = 0; i < newArr.size(); i++)
		arr[startPos + i] = newArr[i];
}

void Sort(std::vector<int> & arr, int startPos, int endPos)
{
	if (endPos == startPos + 1) 
		Compexch(arr[startPos], arr[endPos]);
	if (endPos < startPos + 2)
		return;
	int half = (startPos + endPos) / 2;
	Separation(arr, startPos, endPos);

	Sort(arr, startPos, half);
	Sort(arr, half + 1, endPos);

	Merge(arr, startPos, endPos);

	for (int i = startPos + 1; i < endPos; i += 2)
		Compexch(arr[i], arr[i + 1]);
}

int main()
{
	std::vector<int> arr { 9, 8, 1, 6, 7, 4, 0, 2};

	Sort(arr, 0, 7);

	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
    return 0;
}

