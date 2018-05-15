#pragma once

#include "resource.h"
#include "button.h"

#define GAME_PRE 1201
#define GAME_START 1202
#define GAME_RUNNING 1203
#define GAME_BGMBOX 1204
#define GAME_SET 1205

//控制图HDC和音乐播放
class GameControl {
public:
	GameControl(HWND hwnd) {
		this->hwnd = hwnd;
		this->mode = GAME_PRE;
	}
	GameControl() {

	}
	~GameControl() {
	}
	//初始化界面
	//对应WM_PAINT
	void wmPaint(HDC hdc) {
		switch (this->mode) 
		{
		case GAME_PRE:
			//表示当前在游戏主界面
			this->pre(hdc);
			break;
		case GAME_START:
			//开始游戏
			buttons.eraseButton();
			paint("img\\start.png");
			break;
		case GAME_RUNNING:
			//在游戏进行中
			break;
		default:
			return;
		}
	}
	//游戏开始
	void start() {
		this->mode = GAME_START;
	}
	//进行流程
	void run() {
		switch (this->mode)
		{
		case GAME_PRE:
			//表示当前在游戏主界面
			break;
		case GAME_START:
			//开始游戏
			buttons.eraseButton();
			paint("img\\start.png");
			//进行加载地图等耗时操作
			this->mode = GAME_RUNNING;
			break;
		case GAME_RUNNING:
			//在游戏进行中
			break;
		default:
			return;
		}
	}
private:
	//游戏初始界面预处理
	void pre(HDC hdc) {
		player.play("bgm\\koko.wav","");
		this->prePaint(hdc);
		//读取存档等操作
		buttons.addButton(hwnd, false);
	}
	//游戏进入前界面绘画
	void prePaint(HDC hdc) {
		CImage img;
		img.Load("img\\begin.jpg");
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(hdc);
		SelectObject(mmhdc, bg);//将图片放到HDC上  
		RECT rect;
		GetClientRect(hwnd, &rect);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		DeleteDC(mmhdc);
		DeleteObject(bg);
		TextOut(hdc, 950, 500, _T("Ghost Smile  -- 2018 05 08"), 26);
	}
	//绘图
	void paint(const char* pic_name) {
		HDC g_hdc = GetDC(hwnd);
		CImage img;
		img.Load(pic_name);
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		SelectObject(mmhdc, bg);//将图片放到HDC上  
		RECT rect;
		GetClientRect(hwnd, &rect);
		BitBlt(g_hdc, 0, 0, rect.right, rect.bottom, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		DeleteDC(mmhdc);
		DeleteObject(bg);
		ReleaseDC(hwnd, g_hdc);
	}
	//绘图
	void paint(HBITMAP bg) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		SelectObject(mmhdc, bg);//将图片放到HDC上  
		RECT rect;
		GetClientRect(hwnd, &rect);
		BitBlt(g_hdc, 0, 0, rect.right, rect.bottom, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		DeleteDC(mmhdc);
		DeleteObject(bg);
		ReleaseDC(hwnd, g_hdc);
	}
protected:
	HWND hwnd;//主窗口句柄
	MusicPlayer player;//音乐播放
	int mode;//流程
	Buttons buttons;//开始界面的按钮
};