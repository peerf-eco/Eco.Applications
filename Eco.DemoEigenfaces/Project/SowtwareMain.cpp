#include <Windows.h>
//#include <stdio.h>
#include <string>
#include "SoftwareDefinitions.h"

#include "resource.h"
// точка входа
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	
	//класс приложения
	/*hInst = hInstance;*/
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return - 1; }
	MSG SoftwareMainMessage = { 0 };
	CreateWindow(L"MainWndClass",L"First c++ window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}


WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {

	WNDCLASS NWC = { 0 };
	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

//процедура
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg){
	case WM_COMMAND:
		switch (wp) {
		case OnMenuAction1:
			MessageBoxA(hWnd, "Menu 1 was clicked", "Menu worked", MB_OK);
			break;
		case OnClearField:
			SetWindowTextA(hEditControl, "");
			break;
		case OnReadField:
			num = GetDlgItemInt(hWnd, DlgIndexNumber, FALSE, false);
			SetWindowTextA(hStaticControl, std::to_string(num).c_str());
			break;
		case OnLoadPic:
		{
			hBitMap = LoadBitmap(hInst, L"C:\\BMP\\sample.bmp");
			if (hBitMap == NULL)
			{
				MessageBoxA(hWnd, "No picture!", "ERROR", NULL);
				break;
			}
			/*hPic = GetDlgItem(hWnd, IDB_BITMAP2);*/
			break;
		}
		case OnPaint:
		{
			BITMAP bm;
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(hPic, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HGDIOBJ hbmOld = SelectObject(hdcMem, hBitMap);
			GetObject(hBitMap, sizeof(bm), &bm);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);
			EndPaint(hPic, &ps);
			break;
		}
			
		/*case OnMenuAction2:
			MessageBoxA(hWnd, "Menu 2 was clicked", "Menu worked", MB_OK);
			break;
		case OnMenuAction3:
			MessageBoxA(hWnd, "Menu 3 was clicked", "Menu worked", MB_OK);
			break;*/
			
		//case OnSaveFile:
		//	SaveData("C:\\Савелий Волкович\\C++ приложения\\project\\x64\\Debug\\output.txt");

		//	break;
		//case OnLoadFile:
		//	LoadData("C:\\Савелий Волкович\\C++ приложения\\project\\x64\\Debug\\output.txt");

		//	break;
		case OnExitSoftware:
			PostQuitMessage(0);

			break;
		default: break;
		}
		break;

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
		break;
	}
}

// подменю
void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();

	HMENU SubMenu = CreateMenu();
	//HMENU SubActionMenu = CreateMenu();

	/*AppendMenu(SubActionMenu, MF_STRING, OnMenuAction1, L"Menu 1");
	AppendMenu(SubActionMenu, MF_STRING, OnMenuAction2, L"Menu 2");
	AppendMenu(SubActionMenu, MF_STRING, OnMenuAction3, L"Menu 3");*/

	//AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubActionMenu, L"Action");
	AppendMenu(SubMenu, MF_STRING, OnClearField, L"Clear");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"Save");
	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Load");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");
	AppendMenu(SubMenu, MF_STRING, OnLoadPic, L"Load Pic");


	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(RootMenu, MF_STRING, (UINT_PTR)SubMenu, L"Help");

	SetMenu(hWnd, RootMenu);
}

//Виджиты
void MainWndAddWidgets(HWND hWnd) {

	hStaticControl = CreateWindowA("static", "STATUS: WINAPI C++ app", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 5, 100, 30, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "This is EDIT control", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL , 5, 40, 470, 120, hWnd, NULL, NULL, NULL);
	hNumberControl = CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 5, 170, 120, 30, hWnd, (HMENU)DlgIndexNumber, NULL, NULL);


	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Read", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 50, 30, hWnd, (HMENU)OnReadField, NULL, NULL);
}

//void SaveData(LPCSTR path) {
//	HANDLE FileToSave = CreateFileA(
//		path,
//		GENERIC_WRITE,
//		0,
//		NULL,
//		CREATE_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	int saveLength = GetWindowTextLength(hEditControl) + 1;//буффер для записи
//	char* data = new char[saveLength];//буффер символов
//
//	saveLength = GetWindowTextA(hEditControl, data, saveLength);
//	
//	DWORD bytesIterated;//сколько символов записано в файл
//	WriteFile(FileToSave, data, saveLength, &bytesIterated, NULL);
//
//	CloseHandle(FileToSave);//закрытие файла
//	delete[] data;//освобождение памяти
//}
//
//void LoadData(LPCSTR path) {
//	HANDLE FileToLoad = CreateFileA(
//		path,
//		GENERIC_READ,
//		0,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	DWORD bytesIterated;
//	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);
//
//	SetWindowTextA(hEditControl, Buffer);
//
//	CloseHandle(FileToLoad);//закрытие файла
//}