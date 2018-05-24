#pragma once
#include "EmptyThing.h"
#include <vector>
#include "GameMessageBox.h"
#include "HpAdder.h"

//����
class Bag {
public:
	std::vector<ThingOfBag *> bag;
	GameMessageBox box;
	bool visable = false;
	HBITMAP pic;
	Bag(){}
	Bag(GameMessageBox &box) {
		this->box = box;
		CImage img;
		img.Load("img\\Thing\\bag.jpg");
		pic = img.Detach();
	}
	//������ʼ��
	void init() {
		//����ֻ������
		bag.push_back(new EmptyThing());
		bag.push_back(new EmptyThing());
		bag.push_back(new EmptyThing());
		bag.push_back(new EmptyThing());
		bag.push_back(new EmptyThing());
		bag.push_back(new EmptyThing());
	}
	//��ͼ
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		//TextOut(g_hdc, 200, 200, _T("Test"), 4);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc,pic);//��ͼƬ�ŵ�HDC��  
		BitBlt(g_hdc, 700, 400, 188, 132, mmhdc, 0, 0, SRCCOPY);
		if (bag[0]->count > 0)bag[0]->paint(hwnd, 705, 405);
		if (bag[1]->count > 0)bag[1]->paint(hwnd, 770, 405);
		if (bag[2]->count > 0)bag[2]->paint(hwnd, 835, 405);
		if (bag[3]->count > 0)bag[3]->paint(hwnd, 705, 480);
		if (bag[4]->count > 0)bag[4]->paint(hwnd, 770, 480);
		if (bag[5]->count > 0)bag[5]->paint(hwnd, 835, 480);
		TextOut(g_hdc, 750, 450, _T("Q"), 1);
		TextOut(g_hdc, 815, 450, _T("W"), 1);
		TextOut(g_hdc, 880, 450, _T("E"), 1);
		TextOut(g_hdc, 750, 510, _T("A"), 1);
		TextOut(g_hdc, 815, 510, _T("S"), 1);
		TextOut(g_hdc, 880, 510, _T("D"), 1);
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	//ʹ�ñ�������Ʒ
	void use(int &effect_data,int index) {
		bag[index]->use(effect_data,box);
		if (bag[index]->count <= 0)bag[index] = new EmptyThing();
	}
	//����һ����Ʒ
	//������������������Ļ����ʾ��ʾ
	void add(ThingOfBag *thing) {
		int mode = true;
		for (int index = 0;index < 6;index++)
		{
			if (bag[index]->count > 0)continue;
			else {
				mode = false;
				bag[index] = thing;
				break;
			}
		}
		if (mode)
			box.add("��������!",30);
	}
	~Bag() {
		for (ThingOfBag * thing : bag)
			delete thing;
	}
};