
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

//#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Editor.h"

#if defined(_DEBUG)
#	pragma comment(lib, "sxguiwinapi_d.lib")
#else
#	pragma comment(lib, "sxguiwinapi.lib")
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SXGUIinit();

	Editor edt;

	MSG msg = {0};
	
	while(WM_QUIT != msg.message)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && WM_QUIT != msg.message)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		edt.Update();
	}

	return(msg.wParam);
}
