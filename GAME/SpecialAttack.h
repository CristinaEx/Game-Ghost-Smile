#pragma once
#include<Windows.h>

//�������͹����Ļ���

class SpecialAttack {
public:
	int count;//����ģʽ�ж�
	int damage;//�˺�
	HBITMAP map;//һ���������µĹ�����ͼ
	virtual void paint() = 0;//�������
	virtual void run() = 0;//�����ж�
};