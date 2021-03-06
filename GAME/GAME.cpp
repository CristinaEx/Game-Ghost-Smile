//GAME.cpp: 定义应用程序的入口点。
//960 * 640 -> 每十个像素划为一个区域

#include "stdafx.h"
#include "GAME.h"

#define FPS 30
#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
//_T : 兼容模式
//_L : Unicode
//MAX_LOADSTRING = 100
WCHAR szTitle[12] = L"Ghost Smile";                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 游戏
GameControl game;

// 判断游戏是否进行
bool running = true;

// 主函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。
	

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

    MSG msg;
    // 主消息循环: 
	// PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
	// GetMessage(&msg, nullptr, 0, 0)
	while (running) {
		int timeStart = GetTickCount();
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//hwnd为实例句柄，存放在全局变量
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		//流程进行
		game.run();
		//控制帧数
		while (GetTickCount() - timeStart < 1000 / FPS);//等待直到一帧的时间结束
	}

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  窗口分辨率:960*640
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   //960 * 640的窗口
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
	   300, 100, 960, 640, nullptr, nullptr, hInstance, nullptr);

   //获取game实例
   game = GameControl(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool top_down = false;
	static bool button_down = false;
	static bool left_down = false;
	static bool right_down = false;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case BUTTON_START:
				game.start();
				break;
			case BUTTON_LOAD:
				break;
			case BUTTON_SET:
				break;
			case BUTTON_BGMBOX:
				break;
			case BUTTON_EXIT:
				DestroyWindow(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			//初始更新显示窗口
            PAINTSTRUCT ps;
			//要处理 WM_PAINT 消息，首先应调用 BeginPaint  
			//然后处理所有的逻辑以及在窗口中布局文本、按钮和其他控件等  
			//然后调用 EndPaint。
            HDC hdc = BeginPaint(hWnd, &ps);  
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			game.wmPaint(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN: 
		// WM_LBUTTONDOWN是鼠标左键按下的事件“枚举”
		break;
    case WM_DESTROY:
		running = false;
        PostQuitMessage(0);
        break;
	case WM_KEYDOWN://按下键盘消息  
		switch (wParam)//通过判断wParam来确定按下的按键  
		{
		case VK_ESCAPE: //按下【ESC】键   
			PostQuitMessage(0);//退出程序  
			break;
		case VK_UP: //按下【↑】键  
			top_down = true;
			break;
		case VK_DOWN: //按下【↓】键  
			button_down = true;
			break;
		case VK_LEFT: //按下【←】键  
			left_down = true;
			break;
		case VK_RIGHT: //按下【→】键  
			right_down = true;
			break;
		case  VK_SPACE: //按下空格键
			if ((game.game_eneginer.box.element_message & 0xf000) == END) {
				//结局选择
				DataDealer::writeFile("data\\end.dat", "1");
				game.pre_end();
			}
			else if (game.game_eneginer.box.mode)game.game_eneginer.box.element_message = PLAYER | CHECK_TRUE;
			break;
		case  VK_RETURN: //按下回车键
			//处理返回标题画面的事件
			if (game.game_eneginer.box.element_message == (GAMEENEGINER | CHECK_EMPTY)) {
				game.game_eneginer.map.player.close();
				game.mode = GAME_PRE;
				HDC hdc = GetDC(hWnd);
				game.pre(hdc);
				ReleaseDC(hWnd, hdc);
			}
			break;
		case  VK_TAB://按下TAB键
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.exp_now += 10000;
			break;
		case 'B':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.visable = (game.game_eneginer.player.bag.visable == false);
			break;
		case 'Q':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[0]->use(game.game_eneginer.player.hp_now,game.game_eneginer.box);
			break;
		case 'W':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[1]->use(game.game_eneginer.player.hp_now, game.game_eneginer.box);
			break;
		case 'E':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[2]->use(game.game_eneginer.player.hp_now, game.game_eneginer.box);
			break;
		case 'A':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[3]->use(game.game_eneginer.player.hp_now, game.game_eneginer.box);
			break;
		case 'S':
			if ((game.game_eneginer.box.element_message & 0xf000) == END){
				//结局选择
				DataDealer::writeFile("data\\end.dat", "2");
				game.pre_end();
			}
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[4]->use(game.game_eneginer.player.hp_now, game.game_eneginer.box);
			break;
		case 'D':
			if (game.mode == GAME_RUNNING)
				game.game_eneginer.player.bag.bag[5]->use(game.game_eneginer.player.hp_now, game.game_eneginer.box);
			break;
		}
		break;
	case WM_KEYUP://弹起键盘消息 
		switch (wParam)//通过判断wParam来确定按下的按键  
		{
		case VK_UP:
			top_down = false;
			break;
		case VK_DOWN:
			button_down = false;
			break;
		case VK_LEFT:
			left_down = false;
			break;
		case VK_RIGHT:
			right_down = false;
			break;
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
	}
	if (game.mode == GAME_RUNNING) {
		if (top_down)
			game.game_eneginer.player.mode = (game.game_eneginer.player.mode & 0xf0ff) | TO_TOP;
		if (button_down)
			game.game_eneginer.player.mode = (game.game_eneginer.player.mode & 0xf0ff) | TO_BUTTON;
		if (left_down)
			game.game_eneginer.player.mode = (game.game_eneginer.player.mode & 0xff00) | TO_LEFT | LEFT;
		if (right_down)
			game.game_eneginer.player.mode = (game.game_eneginer.player.mode & 0xff00) | TO_RIGHT | RIGHT;
	}
    return 0;
}

// “关于”框的消息处理程序。
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
