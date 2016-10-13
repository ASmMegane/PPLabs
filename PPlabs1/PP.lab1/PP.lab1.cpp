#include "stdafx.h"
#include "CAlgebraicAddition.h"

int main()
{
	std::string countThread;
	std::cout << "Enter count thread: ";
	std::cin >> countThread;
	int count = std::atoi(countThread.c_str());
	while (count == 0)
	{
		std::cout << "Enter count thread: ";
		std::cin >> countThread;
		count = std::atoi(countThread.c_str());
	}

	CAlgebraicAddition Addition;

	Addition.ConsistentMetod();
	Addition.ParallelMetod(count);

    return 0;
}

