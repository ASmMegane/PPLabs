#pragma once
#include <random>
#include <string>

class PICalculation
{
public:
	PICalculation(std::string type, CString ipAdress,int port, int countIter);
	PICalculation(std::string type, int countProcces, int port);
	~PICalculation() = default;

	void Server();
	void Client();

private:

	void CreateServer();
	void CreateClient();

	bool ReadData();
	bool SendData();

	void OutputDataServer();

	int GetRandomNumber(int range) const;
	
	double CalculationPI() const;

	CSocket m_sockect;
	double m_allPIValue;
	unsigned int m_processCount;
	unsigned int m_iterCount;
	unsigned int m_portServer;
	double m_piValue;
	CString m_IPAdress;
};
