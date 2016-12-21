#include "stdafx.h"
#include "PICalculation.h"

PICalculation::PICalculation(std::string type, int countProcess, int countIter)
{
	m_processCount = countProcess;
	m_iterCount = countIter;
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
	CreateProcesses();
	OutputDataServer();
}

void PICalculation::Client()
{
	m_piValue = CalculationPI();
	CreateClient();
	SendData();
}

void PICalculation::CreateProcesses()
{
	STARTUPINFO* si = new STARTUPINFO[m_processCount];
	PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[m_processCount];
	HANDLE* handlePi = new HANDLE[m_processCount];

	std::string command(__argv[0]);
	std::wstring cmdLine(command.begin(), command.end());
	std::string commandArg = std::string(" client ") + std::to_string(m_processCount) + ' ' + std::to_string(m_iterCount);
	std::wstring wCommandArg(commandArg.begin(), commandArg.end());
	cmdLine.append(wCommandArg);


	for (int i = 0; i < (int)m_processCount; i++)
	{
		ZeroMemory(&(si[i]), sizeof(si[i]));
		si[i].cb = sizeof(si[i]);
		ZeroMemory(&(pi[i]), sizeof(pi[i]));

		handlePi[i] = pi[i].hProcess;
	}

	for (int i = 0; i < (int)m_processCount; i++)
	{
		CreateProcess(NULL, (LPWSTR)cmdLine.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &(si[i]), &(pi[i]));
	}

	ReadData();

	WaitForMultipleObjects(m_processCount, handlePi, true, INFINITE);

	delete(si);
	delete(pi);
	delete(handlePi);
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
	if (m_sockect.Listen(m_processCount) == FALSE)
	{
		wprintf(L"Unable to Listen on that port, please try another port");
		m_sockect.Close();
	}
}

void PICalculation::CreateClient()
{
	m_sockect.Create();
	CString ipAddress = _T("127.0.0.1");
	m_sockect.Connect(ipAddress, 10001);
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
	int countProcces = m_processCount;
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

		std::cout << "Number process: " << countProcces << ". Count itr: " << m_iterCount << ". Value: " << receivedData << std::endl;

		socketClient.Close();
		countProcces--;
		if (countProcces == 0)
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