#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

int main()
{
	CBank* bank = new CBank();
	CBankClient* client1 = bank->CreateClient();
	CBankClient* client2 = bank->CreateClient();

	// TODO: WaitForMultipleObjects
	while (true)
	{
		WaitForMultipleObjects(static_cast<DWORD>(2), bank->GetClientsHandles(), TRUE, INFINITE);
	}

	return 0;
}