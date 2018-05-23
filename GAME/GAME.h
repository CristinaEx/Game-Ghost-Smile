#pragma once

#include "resource.h"
#include "button.h"
#include "map.h"
#include "GameEneginer.h"
#include "DataDealer.h"

#define GAME_PRE 1201
#define GAME_START 1202
#define GAME_RUNNING 1203
#define GAME_BGMBOX 1204
#define GAME_SET 1205

//控制游戏的流程
class GameControl {
public:
	MusicPlayer player;//音乐播放
	GameEneginer game_eneginer; //游戏引擎
	int mode;//流程
	GameControl(HWND &hwnd){
		this->hwnd = hwnd;
		this->mode = GAME_PRE;
		this->player = MusicPlayer();
		this->game_eneginer = GameEneginer(hwnd, player);
	}
	GameControl(){}
	~GameControl() {
	}
	//初始化界面
	//对应WM_PAINT
	void wmPaint(HDC &hdc) {
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
	//data_path 为读取文件名(默认保存在data//文件夹内)
	void start(std::string data_path = "") {
		this->data_path = data_path;
		this->mode = GAME_START;
	}
	//进行流程
	void run() {
		switch (this->mode)
		{
		case GAME_PRE:
			//表示当前在游戏主界面
			break;
		case GAME_START:;
			//开始新游戏
			DataDealer::clearPath(DATA_PATH);
			buttons.eraseButton();
			paint("img\\start.png");
			player.close();
			//进行加载地图等耗时操作
			this->game_eneginer.init(this->data_path);
			this->mode = GAME_RUNNING;
			break;
		case GAME_RUNNING:
			//在游戏进行中
			game_eneginer.run();
			break;
		default:
			return;
		}
	}
	//游戏初始界面预处理
	void pre(HDC &hdc) {
		player.play("bgm\\koko.wav", "");
		this->prePaint(hdc);
		//读取存档等操作
		buttons.addButton(hwnd, false);
	}
private:
	//游戏进入前界面绘画
	void prePaint(HDC &hdc) {
		CImage img;
		img.Load("img\\begin.jpg");
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
		RECT rect;
		GetClientRect(hwnd, &rect);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		SelectObject(mmhdc, hp);
		DeleteObject(bg);
		DeleteDC(mmhdc);
		TextOut(hdc, 800, 500, _T("Ghost Smile"), 11);
		img.Destroy();
	}
	//绘图
	void paint(const char* pic_name) {
		HDC g_hdc = GetDC(hwnd);
		CImage img;
		img.Load(pic_name);
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
		BitBlt(g_hdc, 0, 0, 960, 640, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		SelectObject(mmhdc, hp);
		DeleteObject(bg);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
		img.Destroy();
	}
protected:
	HWND hwnd;//主窗口句柄
	Buttons buttons;//开始界面的按钮
	std::string data_path; //读取文件路径
};
