#pragma once
#include "windows.h"
#include "MusicPlayer.h"

//游戏引擎
class GameEneginer {
public:
	HWND hwnd;//主窗口句柄
	Map map;//地图
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
		}
		else {
			//载入游戏
		}
	}
};