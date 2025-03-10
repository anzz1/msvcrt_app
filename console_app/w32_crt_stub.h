// w32_crt_stub.h

#pragma once

#define WINVER 0x501
#define _WIN32_WINNT 0x501
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _NO_CRT_STDIO_INLINE

#include <windows.h>

extern __declspec(dllimport) int __cdecl __getmainargs(long*,char***,char***,long,long*);
extern __declspec(dllimport) void __cdecl exit(int const);
int main(int argc, char** argv);

void mainCRTStartup() {
	long argc;
	char** argv;
	char** env;
	long l;
	__getmainargs(&argc, &argv, &env, 0, &l);
	exit(main(argc, argv));
}
