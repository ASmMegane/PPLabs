#pragma once
#include <random>
#include <string>

class PICalculation
{
public:
	PICalculation(std::string type, int countProcess, int countIter);
	~PICalculation() = default;

	void Server();
	void Client();

private:

	void CreateServer();
	void CreateClient();
	void CreateProcesses();

	bool ReadData();
	bool SendData();

	void OutputDataServer();

	int GetRandomNumber(int range) const;
	
	double CalculationPI() const;

	CSocket m_sockect;
	double m_allPIValue;
	unsigned int m_processCount;
	unsigned int m_iterCount;
	double m_piValue;

};
