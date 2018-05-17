#pragma once
#include "windows.h"
#include "MusicPlayer.h"
#include "player.h"

//游戏引擎
class GameEneginer {
public:
	HWND hwnd;//主窗口句柄
	Map map;//地图
	Player player;//玩家
	GameEneginer() {}
	GameEneginer(HWND &hwnd, MusicPlayer &player) {
		this->hwnd = hwnd;
		map = Map(player);
	}
	//游戏内容初始化
	//若data_path为NULL，则创建新游戏
	void init(std::string data_path = "") {
		if (data_path.empty()) {
			//创建新游戏
			map.init();
			player.init();
		}
		else {
			//载入游戏
		}
	}
	//进行活动
	void run() {
		paintPic(map.background);
		//加载玩家信息
		player.run();
		//地图元素
		map.run(player);
		player.paint(hwnd);
	}
private:
	//绘制图片
	void paintPic(HBITMAP &bg , int x = 0,int y = 0) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		SelectObject(mmhdc, bg);//将图片放到HDC上  
		BitBlt(g_hdc, x, y, 960, 640, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	//在底端绘制文字
	void paintWord() {
		//...
	}
};