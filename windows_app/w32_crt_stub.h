// w32_crt_stub.h

#pragma once

#define WINVER 0x501
#define _WIN32_WINNT 0x501
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _NO_CRT_STDIO_INLINE

#include <windows.h>

extern __declspec(dllimport) void __cdecl exit(int const);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

int __stdcall WinMainCRTStartup() {
	STARTUPINFOA StartupInfo;
	int wShowWindow;
	CHAR *lpCmdLine;

	StartupInfo.dwFlags = 0;
	GetStartupInfoA(&StartupInfo);
	wShowWindow = (StartupInfo.dwFlags & STARTF_USESHOWWINDOW) ? StartupInfo.wShowWindow : SW_SHOWDEFAULT;

	lpCmdLine = GetCommandLineA();
	if (lpCmdLine && *lpCmdLine) {
		if (*lpCmdLine == '"') {
			++lpCmdLine;
			while (*lpCmdLine)
				if (*lpCmdLine++ == '"')
					break;
		} else {
			while (*lpCmdLine && *lpCmdLine != ' ' && *lpCmdLine != '\t')
				++lpCmdLine;
		}
		while (*lpCmdLine == ' ' || *lpCmdLine == '\t')
			++lpCmdLine;

		return WinMain(GetModuleHandleA(0), 0, lpCmdLine, wShowWindow);
	}
	else {
		return WinMain(GetModuleHandleA(0), 0, "", wShowWindow);
	}
}
