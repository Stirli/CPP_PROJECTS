#include <windows.h>
#include <tchar.h>

#define ID_MYBUTTON 1001
#define ID_MYLIST 1002
#define ID_MYEDIT 1003



LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCWSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCWSTR g_lpszStaticText = TEXT("Нажмите INFO");
LPCWSTR g_lpszButtonText = TEXT("INFO");
LPCWSTR g_lpszAplicationTitie = TEXT("Главное окно приложения.");

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;

	g_hInst = hInstance;
	COLORREF myColor = RGB(0, 255, 0);
	HBRUSH muBrash = CreateSolidBrush(myColor);

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = muBrash;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitie,
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		600,
		500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	static HWND hwndButton;
	static HWND staticHwnd;
	switch (msg)
	{
		HDC hDC;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	case WM_CREATE:
	{
		staticHwnd = CreateWindowEx(0L, TEXT("static"), g_lpszStaticText,
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10, 52, 90, 32,
			hWnd, NULL, NULL, NULL);
		hwndButton = CreateWindowEx(0L, TEXT("button"), g_lpszButtonText,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			10, 10, 90, 32, hWnd,
			(HMENU)ID_MYBUTTON, g_hInst, NULL);
		return 0;
	}
	break;
	case WM_COMMAND:
	{
		int wmld, wmEvent;
		wmEvent = HIWORD(wParam);

		switch (LOWORD(wParam))
		{
		case ID_MYBUTTON:

			static bool flag;
			if (!flag) {
				WNDCLASSEX inf;
				if (GetClassInfoEx(NULL, TEXT("button"), &inf)) {
					TCHAR szBuffer[64];
					int strLen = wsprintf(szBuffer, TEXT("%s\n%X"), inf.lpszClassName, inf.style);
					SetWindowText(staticHwnd, szBuffer);
					SetWindowText((HWND)lParam, TEXT("Выход"));
				}
				else {
					MessageBox(hWnd, TEXT("Не удалось получить инфо"), TEXT("ОШИБКА"), MB_OK | MB_ICONERROR);
				}

				flag = true;
			}
			else {
				DestroyWindow(hWnd);
			}

			break;
		}
		return 0;
	}

	break;
	default:

		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;
}