#pragma once
#include <Windows.h>
#include <memory>
#include <functional>
#include "Primitives.h"

class CBank;

class CBankClient
{
public:
	unsigned int GetId();
	~CBankClient() = default;

private:
	CBankClient(CBank *bank, unsigned int id, Primitives *syncPrimitives);

	static unsigned int GetSleepDuration(CBankClient *client);
	static unsigned int GetBalanceChangeValue();

	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

	static std::function<void(CBankClient*)> GetSyncMethodFunc(PRIMITIVE_TYPE type);

	friend CBank;

	CBank *m_bank;
	unsigned m_id;
	HANDLE m_handle;
	Primitives *m_syncPrimitives = nullptr;
};
