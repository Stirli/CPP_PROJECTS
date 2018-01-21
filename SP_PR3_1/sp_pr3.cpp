#include "sp_pr3.h"

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
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = muBrash;
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
	static HWND hwndEdit;
	static HWND hwndListBox;
	static HWND hwndButton;
	switch (msg)
	{
		HDC hDC;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}

	break;
	case WM_CREATE:
	{
		CreateWindowEx(0L, TEXT("static"), g_lpszStaticText,
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10, 10, 100, 20,
			hWnd, NULL, NULL, NULL);
		hwndEdit = CreateWindowEx(0L, TEXT("edit"), L"",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_RIGHT | WS_BORDER,
			120, 10, 100, 20,
			hWnd, (HMENU)ID_MYEDIT, g_hInst, NULL);
		hwndListBox = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | WS_BORDER,
			120, 40, 100, 100,
			hWnd, (HMENU)ID_MYLIST,
			g_hInst, NULL);
		hwndButton = CreateWindowEx(0L, TEXT("button"), g_lpszButtonText,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			230, 10, 100, 20, hWnd,
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
		case ID_MYEDIT:

			break;
		case ID_MYBUTTON:
			TCHAR myText[20];
			GetWindowText(GetDlgItem(hWnd, ID_MYEDIT), myText, 20);

			GetDlgItemText(
				hWnd,       /* дескриптор родительского диалога */
				ID_MYEDIT,   /* идентификатор поля */
				myText,  /* буфер под текст */
				20    /* размер буфера */
			);
			SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)myText);
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
