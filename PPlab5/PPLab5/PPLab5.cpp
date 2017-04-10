#include "stdafx.h"

std::vector<int> Merge(std::vector<int> const& vector1, std::vector<int> const& vector2)
{
	std::vector<int> resultVec;

	std::vector<int> vec1 = vector1;
	std::vector<int> vec2 = vector2;
	
	while (!vec1.empty() && !vec2.empty())
	{
		if (vec1[0] > vec2[0])
		{
			resultVec.push_back(vec2[0]);
			vec2.erase(vec2.begin());
		}
		else
		{
			resultVec.push_back(vec1[0]);
			vec1.erase(vec1.begin());
		}
	}
	while (!vec1.empty())
	{
		resultVec.push_back(vec1[0]);
		vec1.erase(vec1.begin());
	}
	while (!vec2.empty())
	{
		resultVec.push_back(vec2[0]);
		vec2.erase(vec2.begin());
	}
	return resultVec;
}

std::vector<int> Sort(std::vector<std::vector<int>> const& vec)
{
	auto vector = vec;

	while (vector.size() > 1)
	{
		std::vector<std::vector<int>> tempVec;

#pragma omp parallel for
		for (int i = 0; i < int(vector.size()); i += 2)
		{
			std::vector<std::vector<int>> result;
			if (i + 1 >= vector.size())
			{
				result.push_back(vector[i]);
			}
			else 
			{
				result.push_back(Merge(vector[i], vector[i + 1]));
			}

#pragma omp critical
			for (auto & value : result)
			{
				tempVec.push_back(value);
			}
		}
		vector = tempVec;
	}
	return vector[0];
}


int main(int argc, char * argv[])
{

	if (argc < 2)
		return 1;

	std::ifstream inFile(argv[1]);

	std::vector<int> arr;

	while (!inFile.eof())
	{
		int num;
		inFile >> num;
		arr.push_back(num);
	}

	std::vector<std::vector<int>> vectorForSort;
	for (auto & elem : arr)
	{
		vectorForSort.push_back(std::vector<int>());
		vectorForSort.back().push_back(elem);
	}
	auto start = std::chrono::system_clock::now();
	auto result = Sort(vectorForSort);
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = end - start;
	std::cout << "Time: " << dif.count() << std::endl;
	return 0;
}
