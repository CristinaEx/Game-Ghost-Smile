#pragma once
#include <Windows.h>
#include "GameMessageBox.h"

class ThingOfBag {
	//��ֻ����ֵ(HP)�����õ���Ʒ
public:
	int count;//����
	virtual void paint(HWND &hwnd, int x, int y) = 0;
	//���õ���ֵ
	virtual void use(int &effect_data, GameMessageBox &box) = 0;
};