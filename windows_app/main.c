#include "w32_crt_stub.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MessageBoxA(0, "Hello World", "Hello", MB_OK);
	return 0;
}
