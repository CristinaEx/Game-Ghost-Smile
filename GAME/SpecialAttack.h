#pragma once
#include <Windows.h>
#include "player.h"

//�������͹����Ļ���

class SpecialAttack {
public:
	int count = 0;
	int demage;//�˺�
	int x;//������
	int y;//������
	HBITMAP map;//һ���������µĹ�����ͼ
	virtual void paint(HWND &hwnd) = 0;//�������
	virtual void run(Player &player) = 0;//�����ж�
};