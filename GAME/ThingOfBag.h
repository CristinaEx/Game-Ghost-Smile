#pragma once
#include <Windows.h>
#include "GameMessageBox.h"

class ThingOfBag {
	//均只对数值(HP)有作用的物品
public:
	int count;//计数
	virtual void paint(HWND &hwnd, int x, int y) = 0;
	//作用的数值
	virtual void use(int &effect_data, GameMessageBox &box) = 0;
};