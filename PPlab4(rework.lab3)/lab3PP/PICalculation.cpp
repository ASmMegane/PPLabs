#include "stdafx.h"
#include "PICalculation.h"

PICalculation::PICalculation(std::string type, CString ipAdress, int port, int countIter)
{
	m_IPAdress = ipAdress;
	m_iterCount = countIter;
	m_processCount = 0;
	m_portServer = port;
	if (type == "server")
		Server();
	else if (type == "client")
		Client();
}

PICalculation::PICalculation(std::string type, int countProcess, int port)
{
	m_processCount = countProcess;
	m_portServer = port;
	if (type == "server")
		Server();
	else if (type == "client")
		Client();
}

void PICalculation::OutputDataServer()
{
	double pi = m_allPIValue / m_processCount;
	std::cout << "PI value: " << pi << std::endl;
}

void PICalculation::Server()
{
	CreateServer();
	ReadData();
	OutputDataServer();
}

void PICalculation::Client()
{
	m_piValue = CalculationPI();
	CreateClient();
	SendData();
}

int PICalculation::GetRandomNumber(int range) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, int(range));
	return dist(gen);
}

void PICalculation::CreateServer()
{
	m_sockect.Create(10001);
	if (m_sockect.Listen() == FALSE)
	{
		wprintf(L"Unable to Listen on that port, please try another port");
		m_sockect.Close();
	}
}

void PICalculation::CreateClient()
{
	m_sockect.Create();
	m_sockect.Connect(m_IPAdress, m_portServer);
}

bool PICalculation::SendData()
{
	double buf = m_piValue;
	m_sockect.Send((void*)&buf, sizeof(buf));

	m_sockect.Close();
	return true;
}

bool PICalculation::ReadData()
{
	CSocket socketClient;
	byte buf[1025];
	double receivedData;
	int sizeRecivedData = 0;
	bool isReceived = false;
	int countProcces = 0;
	while (m_sockect.Accept(socketClient))
	{
		isReceived = false;
		int receivedDataLenght;
		
		while (!isReceived)
		{
			if ((receivedDataLenght = socketClient.Receive(buf + sizeRecivedData, 1024)) > 0)
			{
				if (sizeRecivedData + receivedDataLenght < sizeof(double))
					sizeRecivedData += receivedDataLenght;
				else
				{
					receivedData = *((double*) buf);
					isReceived = true;
				}
			}
			else
				break;
		}
		if (isReceived)
		{
			m_allPIValue += receivedData;
		}

		std::cout << "Number process: " << countProcces << ". Value: " << receivedData << std::endl;

		countProcces++;

		socketClient.Close();
		if (countProcces == m_processCount)
			break;
	}
	return isReceived;
}

double PICalculation::CalculationPI() const 
{
	double radius = 1000;

	double allPoint = 0;
	double pointInCircle = 0;

	for (int i = 0; i < m_iterCount; i++)
	{
		int x = GetRandomNumber((int)radius);
		int y = GetRandomNumber((int)radius);
		if (std::pow(y, 2) <= std::pow(radius, 2) - std::pow(x, 2))
		{
			pointInCircle++;
		}
		allPoint++;
	}
	double pi = 4 * (pointInCircle / allPoint);

	return pi;
}