#include <windows.h>
#include <tchar.h>
#include "resource.h"

#pragma once
#define ID_MYBUTTON 1001
#define ID_MYLIST 1002
#define ID_MYEDIT 1003

HINSTANCE g_hInst;
LPCWSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCWSTR g_lpszStaticText = TEXT("������� �����");
LPCWSTR g_lpszButtonText = TEXT("��������");
LPCWSTR g_lpszAplicationTitie = TEXT("������� ���� ����������. ����������� ������� �����");
LPCWSTR g_lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� �������� � �������� ������ �����. ��������� ��������� � ����� � ����������� ���� ����������.");
LPCWSTR g_lpszLBtnMessage = TEXT("��������� ��������� WM_LBUTTONDOWN, ������� ���������� � ���� ��� ������ ����� ������ ����");
LPCWSTR g_lpszLPaintMessage = TEXT("��������� ��������� WM_PAINT.��� ���������� ���� �������� ����� ����, ��� ��� ���� ������� ������ ����� � ����� �������.");
LPCWSTR g_lpszLMessage = TEXT("����������� ��������� WM_CREATE");

LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

