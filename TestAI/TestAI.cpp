// TestAI.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestAI.h"
#include "Cgdi.h"
#include "WindowUtils.h"
#include "PrecisionTimer.h"
#include "GameWorld.h"
#include "Soldier.h"
#include "PlayerControllor.h"
#include "AttackSystem.h"
#include "SoldierPF.h"
#include "File/CSVReader.h"
#include "DebugClass/DebugConsole.h"

#define MAX_LOADSTRING 100
#define  WinWidth 1000
#define  WinHeight 1000

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
PrecisionTimer timer(30);
GameWorld*	g_World = 0;
// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				StartNewGame();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTAI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTAI));

	// ����Ϣѭ��:
	bool bDone = false;
	HWND hWnd = GetActiveWindow();

	while(!bDone)
	{

		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
		{
			if( msg.message == WM_QUIT ) 
			{
				// Stop loop if it's a quit message
				bDone = true;
			} 

			else 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		if (timer.ReadyForNextFrame() && msg.message != WM_QUIT)
		{
			//--------------------------
			//update game states
			//--------------------------
			//
			if (!PlayerControllor::Instance()->GetProxySoldier() ||
				 !PlayerControllor::Instance()->GetProxySoldier()->GetSoldierPF()->DebugRender)
			{
				g_World->Update();
			}
			PlayerControllor::Instance()->Update();

			//render 
			RedrawWindow(hWnd, true);

			Sleep(2);
		}

	}

	g_World->Release();

	UnregisterClass( szWindowClass, hInstance );

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTAI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= /*(HBRUSH)(COLOR_WINDOW)*/0;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTAI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindowEx (NULL,                 // extended style
	   szWindowClass,  // window class name
		szTitle,  // window caption
	   WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
	   GetSystemMetrics(SM_CXSCREEN)/2 - WinWidth/2,
	   GetSystemMetrics(SM_CYSCREEN)/2 - WinHeight/2,                    
	   WinWidth,     // initial x size
	   WinHeight,    // initial y size
	   NULL,                 // parent window handle
	   NULL,                 // window menu handle
	   hInstance,            // program instance handle
	   NULL);     

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient; 

	//used to create the back buffer
	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;
	//
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	static TCHAR	szFileName[MAX_PATH],
					szTitleName[MAX_PATH];


	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_GAME_NEW:

			StartNewGame();

			break;
		case IDM_GAME_LOAD:

			FileOpenDlg(hWnd, szFileName, szTitleName, "Brain map file (*.map)", "map");


			if (strlen(szTitleName) > 0)
			{
				g_World->LoadWorld(szTitleName);
			}

			break;

		case IDM_GAME_SAVE:

			FileSaveDlg(hWnd, szFileName, szTitleName, "Brain map file (*.map)", "map");


			if (strlen(szTitleName) > 0)
			{
				g_World->SaveWorld(szTitleName);
			}

			break;

		case ID_ART_CIRCLE:
			if (PlayerControllor::Instance()->GetProxySoldier())
			{
				PlayerControllor::Instance()->GetProxySoldier()->GetAttackSystem()->SetAttackRange(RangeType::CIRCLE);
			}
			break;
		case ID_ART_CROSS:
			if (PlayerControllor::Instance()->GetProxySoldier())
			{
				PlayerControllor::Instance()->GetProxySoldier()->GetAttackSystem()->SetAttackRange(RangeType::CROSS);
			}
			break;
		case ID_ART_QUAD:
			if (PlayerControllor::Instance()->GetProxySoldier())
			{
				PlayerControllor::Instance()->GetProxySoldier()->GetAttackSystem()->SetAttackRange(RangeType::QUAD);
			}
			break;
		case ID_ART_H:
			if (PlayerControllor::Instance()->GetProxySoldier())
			{
				PlayerControllor::Instance()->GetProxySoldier()->GetAttackSystem()->SetAttackRange(RangeType::HORIZONTAL);
			}
			break;
		case ID_ART_V:
			if (PlayerControllor::Instance()->GetProxySoldier())
			{
				PlayerControllor::Instance()->GetProxySoldier()->GetAttackSystem()->SetAttackRange(RangeType::VERTICAL);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		{
			hdcBackBuffer = CreateCompatibleDC(NULL);

			//get the DC for the front buffer
			HDC hdc = GetDC(hWnd);

			hBitmap = CreateCompatibleBitmap(hdc,
				cxClient,
				cyClient);


			//select the bitmap into the memory device context
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

			//don't forget to release the DC
			ReleaseDC(hWnd, hdc); 

			//
			g_World = GameWorld::Instance();
			debug_con<<"======================"<<debug_end;
			debug_con<<"$  Welcome To World! $"<<debug_end;
			debug_con<<"======================"<<debug_end;
			debug_con<<"Read CSV table"<<debug_end;
			CSVReader	reader("Book1.csv");

			break;
		}
	case WM_PAINT:

		PAINTSTRUCT ps;

		BeginPaint (hWnd, &ps);

		gdi->StartDrawing(hdcBackBuffer);

		gdi->BlackBrush();
		gdi->Rect(0,0,cxClient,cyClient);

		if (g_World)
		{
			g_World->Render();
		}

		gdi->TransparentText();
		gdi->TextColor(Cgdi::green);
		gdi->TextAtPos(5,5,"BunkerAI");

		


		gdi->StopDrawing(hdcBackBuffer);
		//now blit backbuffer to front
		BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

		EndPaint (hWnd, &ps);
		break;
	case WM_DESTROY:
		{

			//clean up our backbuffer objects
			SelectObject(hdcBackBuffer, hOldBitmap);

			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap); 
			// kill the application, this sends a WM_QUIT message  
			PostQuitMessage (0);
		}

		break;
	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			//now to resize the backbuffer accordingly. First select
			//the old bitmap back into the DC
			SelectObject(hdcBackBuffer, hOldBitmap);

			//don't forget to do this or you will get resource leaks
			DeleteObject(hBitmap); 

			//get the DC for the application
			HDC hdc = GetDC(hWnd);

			//create another bitmap of the same size and mode
			//as the application
			hBitmap = CreateCompatibleBitmap(hdc,
				cxClient,
				cyClient);

			ReleaseDC(hWnd, hdc);

			//select the new bitmap into the DC
			SelectObject(hdcBackBuffer, hBitmap);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			auto x = LOWORD(lParam);
			auto y = HIWORD(lParam);
			PlayerControllor::Instance()->Pick();
			debug_con<<x<<","<<y<<debug_end;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void StartNewGame()
{
	g_World->Init();
}
