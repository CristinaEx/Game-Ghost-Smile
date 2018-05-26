#pragma once
#include "ThingOfBag.h"
#include "GameMessageBox.h"
#include <sstream>
#include <atlimage.h> 

class HpAdder : public ThingOfBag{
	//加血物品
public:
	int value;//加血的数值
	HBITMAP pic;//贴图
	HpAdder(int value) {
		CImage img;
		img.Load("img\\Thing\\hp_adder.jpg");
		pic = img.Detach();
		count = 1;
		img.Destroy();
		this->value = value;
	}
	//使用
	void use(int &effect_data , GameMessageBox &box) {
		if (count > 0) {
			effect_data += value;
			box.add("增加了" + int2str(value) + "点HP", 30);
			count--;
		}
	}
	//绘制
	void paint(HWND &hwnd ,int x ,int y) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic);//将图片放到HDC上  
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