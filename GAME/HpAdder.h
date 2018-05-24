#pragma once
#include "ThingOfBag.h"
#include "GameMessageBox.h"
#include <sstream>
#include <atlimage.h> 

class HpAdder : public ThingOfBag{
public:
	int value;//��Ѫ����ֵ
	HBITMAP pic;
	HpAdder(int value) {
		CImage img;
		img.Load("img\\Thing\\hp_adder.jpg");
		pic = img.Detach();
		count = 1;
		img.Destroy();
		this->value = value;
	}
	void use(int &effect_data , GameMessageBox &box) {
		if (count > 0) {
			effect_data += value;
			box.add("������" + int2str(value) + "��HP", 30);
			count--;
		}
	}
	void paint(HWND &hwnd ,int x ,int y) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic);//��ͼƬ�ŵ�HDC��  
		BitBlt(g_hdc, x, y, 50, 50, mmhdc, 0, 0, SRCCOPY);
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	~HpAdder() {
		DeleteObject(pic);
	}
private:
	std::string int2str(const int &int_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		return stream.str();
	}
};