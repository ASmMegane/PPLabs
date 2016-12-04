#include "stdafx.h"
#include "Bank.h"

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}

HANDLE * CBank::GetClientsHandles() const
{
	std::vector<HANDLE> handles;

	for (auto const& client : m_clients)
	{
		handles.push_back(client.m_handle);
	}

	return handles.data();
}



void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;

	SomeLongOperations(client);


	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << (totalBalance + value) << "." << std::endl;

	bool isAccepteble = false;
	if (totalBalance + value > 0)
	{
		SetTotalBalance(GetTotalBalance() + value);
		std::cout << "Total Balance = " << GetTotalBalance() << std::endl;
		isAccepteble = true;
	}
	else
	{
		std::cout << "Client can not cash out" << std::endl;
	}
	if (isAccepteble && (GetTotalBalance() < 0 || totalBalance != GetTotalBalance() - value))
	{
		std::cout << "Error!!!!!!!!" << std::endl;
	}
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations(CBankClient const &client)
{
	Sleep((1000 + rand() % 3000) * (client.m_id + 1));
}