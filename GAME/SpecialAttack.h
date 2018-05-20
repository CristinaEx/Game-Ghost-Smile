#pragma once
#include <Windows.h>
#include "player.h"

//特殊类型攻击的基类

class SpecialAttack {
public:
	int count = 0;
	int demage;//伤害
	int x;//横坐标
	int y;//纵坐标
	HBITMAP map;//一个方向朝向下的攻击贴图
	virtual void paint(HWND &hwnd) = 0;//绘出攻击
	virtual void run(Player &player) = 0;//攻击判定
};