#pragma once
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <string>

class CAlgebraicAddition
{
public:	
	CAlgebraicAddition() : m_matrix(100, std::vector<int>(100, 1)), m_countThread(1){}

	void ParallelMetod(int countThread);
	void ConsistentMetod();

	DWORD WINAPI WriteCollumMinor(int id);

private:
	struct Params
	{
		int startPos, endPos;
		bool isUsed = false;
	};
	Params* params;

	void FindAlgebraicAddition(int n, int m);
	void FindAlgebraicAdditionParallel(int countThread);

	static DWORD WINAPI StaticThreadStart(void* Param)
	{
		CAlgebraicAddition* This = (CAlgebraicAddition*)Param;
		int id = 0;
		while (true)
		{
			if (This->params[id].isUsed == false)
				break;
			id++;
		}
		return This->WriteCollumMinor(id);
	}

	void CreateThreads(int countThread, HANDLE* handles);

	std::vector<std::vector<int>> m_matrix;
	int m_countThread;
};
