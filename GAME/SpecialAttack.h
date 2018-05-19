#pragma once
#include<Windows.h>

//特殊类型攻击的基类

class SpecialAttack {
public:
	int count;//攻击模式判断
	int damage;//伤害
	HBITMAP map;//一个方向朝向下的攻击贴图
	virtual void paint() = 0;//绘出攻击
	virtual void run() = 0;//攻击判定
};