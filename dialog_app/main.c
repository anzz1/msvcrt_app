#include "w32_crt_stub.h"
#include "resource.h"

INT_PTR __stdcall DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_INITDIALOG:
			return TRUE;

		case WM_CLOSE:
			DestroyWindow(hDlg);
			return TRUE;

		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;
	}

	return FALSE;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	HWND hDlg;
	MSG msg;
	BOOL ret;

	hDlg = CreateDialogParamA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), 0, DialogProc, 0);
	ShowWindow(hDlg, SW_SHOWNORMAL);

	while((ret = GetMessageA(&msg, 0, 0, 0)) != 0) {
		if(ret == -1)
			return -1;

		if(!IsDialogMessageA(hDlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	return 0;
}
