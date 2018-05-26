#pragma once
#include "GameMessageBox.h"
#include "player.h"

class Element {
public:
	virtual void run(Player &player, GameMessageBox &box) = 0;//运行逻辑
	int x;//横坐标
	int y;//纵坐标
	virtual void paint(HWND &hwnd) = 0;//绘制自身
};