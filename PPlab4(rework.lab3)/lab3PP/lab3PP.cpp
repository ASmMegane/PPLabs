#include "stdafx.h"
#include "lab3PP.h"
#include "PICalculation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: change error code to suit your needs
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {

			// TODO: code your application's behavior here.
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }
	if (AfxSocketInit() == FALSE)
	{
		wprintf(L"Sockets Could Not Be Initialized");
		nRetCode = 1;
	}

	
	if (__argc == 5)
		PICalculation piNumber((std::string)__argv[1], CString(__argv[2]), std::atoi(__argv[3]), std::atoi(__argv[4]));
	if (__argc == 4)
		PICalculation piNumber((std::string)__argv[1], std::atoi(__argv[2]), std::atoi(__argv[3]));
    return nRetCode;
}
