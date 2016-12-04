#include "stdafx.h"
#include "BankClient.h"
#include "Bank.h"


CBankClient::CBankClient(CBank *bank, unsigned id)
	: m_bank(bank)
	, m_id(id)
	, m_handle(CreateThread(NULL, 0, ThreadFunction, this, 0, NULL))
{
}


unsigned CBankClient::GetId()
{
	return m_id;
}


DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	
	srand(client->m_id);

	while (true)
	{
		Sleep(GetSleepDuration(client));
		client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
	}
	return 0;
}


unsigned int CBankClient::GetSleepDuration(CBankClient *client)
{
	return (1000 + rand() % 2999) * (client->m_id + 1);
}


unsigned int CBankClient::GetBalanceChangeValue()
{
	return (-100 + rand() % 201);
}