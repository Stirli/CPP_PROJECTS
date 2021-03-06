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
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
	hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitie,
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		600,
		500,
		NULL,
		hMenu,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));


	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!hAccel || !TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
		/*int strLen = lstrlen(g_lpszLPaintMessage);
		TextOut(hDC, 20, 100, g_lpszLPaintMessage, strLen);*/
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
				hWnd,       /* ���������� ������������� ������� */
				ID_MYEDIT,   /* ������������� ���� */
				myText,  /* ����� ��� ����� */
				20    /* ������ ������ */
			);
			SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)myText);
			break;
		case IDM_CREATE:
			MessageBox(hWnd, TEXT("������ ����� '�������'"), TEXT("���� ����"), MB_OK);
			break;
		case IDM_OPEN:
			MessageBox(hWnd, TEXT("������ ����� '�������'"), TEXT("���� ����"), MB_OK);
			break;
		case IDM_EXIT:
			MessageBox(hWnd, TEXT("������ ����� '�����'"), TEXT("���� ����"), MB_OK);
			DestroyWindow(hWnd);
			break;
		case IDM_SELECT:
			MessageBox(hWnd, TEXT("������ ����� '�������'"), TEXT("���� ������"), MB_OK);
			break;
		case ID_ACCELERATOR_CUT:
		case IDM_CUT:
			MessageBox(hWnd, TEXT("������ ����� '��������'"), TEXT("���� ������"), MB_OK);
			break;
		case ID_ACCELERATOR_COPY:
		case IDM_COPY:
			MessageBox(hWnd, TEXT("������ ����� '����������'"), TEXT("���� ������"), MB_OK);
			break;
		case ID_ACCELERATOR_INSERT:
		case IDM_INSERT:
			MessageBox(hWnd, TEXT("������ ����� '��������'"), TEXT("���� ������"), MB_OK);
			break;
		case IDM_HELP:
			MessageBox(hWnd, TEXT("������ ����� '������'"), TEXT("���� �������"), MB_OK);
			break;
		case IDM_ABOUT:
			MessageBox(hWnd, TEXT("������ ����� '� ���������...'"), TEXT("���� �������"), MB_OK);
			break;
		}
		return 0;
	}
	break;

	case WM_MENUSELECT:

	{
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	TCHAR Buf[300];
	int size = LoadString(hInst, LOWORD(wParam), Buf, 300);
	DrawMyText(hWnd, Buf, size);

	break;

	}

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;
}

void DrawMyText(HWND hWnd, LPCWSTR str, int size)
{
	LPCWSTR lpszMsgSpace = TEXT("                                                                                     ");
	HDC hdc1 = GetDC(hWnd);

	RECT rc;

	GetClientRect(hWnd, &rc);
	TextOut(hdc1, rc.left + 10, rc.bottom - 30,
		lpszMsgSpace, lstrlen(lpszMsgSpace));
	TextOut(hdc1, rc.left + 10, rc.bottom - 30,
		str, size);

	ReleaseDC(hWnd, hdc1);
}
