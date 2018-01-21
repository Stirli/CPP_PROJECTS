#include <windows.h>
#include <tchar.h>
#include "resource.h"

#pragma once
#define ID_MYBUTTON 1001
#define ID_MYLIST 1002
#define ID_MYEDIT 1003

HINSTANCE g_hInst;
LPCWSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCWSTR g_lpszStaticText = TEXT("Введите текст");
LPCWSTR g_lpszButtonText = TEXT("Записать");
LPCWSTR g_lpszAplicationTitie = TEXT("Главное окно приложения. Программист Шершнев Игорь");
LPCWSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод. Сообщение поступило в связи с разрушением окна приложения.");
LPCWSTR g_lpszLBtnMessage = TEXT("Обработка сообщения WM_LBUTTONDOWN, которое посылается в окно при щелчке левой кнопки мыши");
LPCWSTR g_lpszLPaintMessage = TEXT("Обработка сообщения WM_PAINT.Это соообщение окно получает после того, как оно было закрыто другим окном и затем открыто.");
LPCWSTR g_lpszLMessage = TEXT("Выполняется обработка WM_CREATE");

LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

