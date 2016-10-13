#include "stdafx.h"
#include "CAlgebraicAddition.h"

void CAlgebraicAddition::FindAlgebraicAddition(int n, int m)
{
	std::vector<std::vector<int>> minor(m_matrix.size() - 1, std::vector<int>(m_matrix.size() - 1, 0));
	int nShift = 0, mShift = 0;
	for (int i = 0; i < m_matrix.size(); i++)
	{
		mShift = 0;
		if (i == n)
		{
			nShift = -1;
			continue;
		}
		for (int k = 0; k < m_matrix[i].size(); k++)
		{
			if (k == m)
			{
				mShift = -1;
				continue;
			}
			minor[i + nShift][k + mShift] = m_matrix[i][k];
		}
	}
	int algebraicAddition = (-1) ^ (n + m);
}


DWORD WINAPI CAlgebraicAddition::WriteCollumMinor(int id)
{
	for (int i = this->params[id].startPos; i < this->params[id].endPos; i++)
		for (int k = 0; k < m_matrix[i].size(); k++)
			FindAlgebraicAddition(k, i);
	return 0;
}

void CAlgebraicAddition::CreateThreads(int countThread, HANDLE* handles)
{
	m_countThread = countThread;
	params = new Params[countThread];
	int countLineMatrix = int(m_matrix.size() / countThread);
	for (int i = 0; i < countThread; i++)
	{
		params[i].startPos = i * countLineMatrix;
		if (i == countThread - 1)
			params[i].endPos = m_matrix.size();
		else
			params[i].endPos = params[i].startPos + countLineMatrix;
		
		handles[i] = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)StaticThreadStart, (void*)this, CREATE_SUSPENDED, NULL);
	}
}

void CAlgebraicAddition::FindAlgebraicAdditionParallel(int countThread)
{
	HANDLE* handles = new HANDLE[countThread];

	CreateThreads(countThread, handles);

	for (int i = 0; i < countThread; i++)
		ResumeThread(handles[i]);

	WaitForMultipleObjects(countThread, handles, true, INFINITE);

	delete(handles);
	delete(params);

}

void CAlgebraicAddition::ParallelMetod(int countThread)
{
	unsigned int startTime = clock();
	FindAlgebraicAdditionParallel(countThread);
	unsigned int endTime = clock();
	float searchTime = (endTime - startTime) / 1000.0;
	std::cout << "Parallel run time: " << searchTime << std::endl;
}

void CAlgebraicAddition::ConsistentMetod()
{
	unsigned int startTime = clock();
	for (int i = 0; i < m_matrix.size(); i++)
		for (int k = 0; k < m_matrix[i].size(); k++)
			FindAlgebraicAddition(k, i);
	unsigned int endTime = clock();
	float searchTime = (endTime - startTime) / 1000.0;
	std::cout << "Sequence run time: " << searchTime << std::endl;
}