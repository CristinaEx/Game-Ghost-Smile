#pragma once
#include <atlimage.h>
#include <string>
#include <sstream>
#include <vector>
#include "Bag.h"

#define RIGHT 0x0000
#define LEFT 0x0001

#define TO_RIGHT 0x0010
#define TO_LEFT 0x0020
#define TO_TOP 0x0100
#define TO_BUTTON 0x0200
#define TO_FAST_RIGHT 0x0050
#define TO_FAST_LEFT 0x0060
#define TO_FAST_TOP 0x0070
#define TO_FAST_BUTTON 0x0080
#define NORMAL_MODE 0x0000
#define SNEAK_MODE 0x1000


//��ҽ�ɫ
class Player{
public:
	int exp_max;//��ǰ�ȼ������ֵ
	int level;//�ȼ�
	int hp_max;//��ǰ�ȼ����Ѫ��
	int mode;//��ǰ״̬
	int hp_now;//��ǰѪ��
	int exp_now;//��ǰ����ֵ
	int x;//������
	int y;//������
	std::vector<HBITMAP> pic;//��ͼ
	Bag bag;
	Player(){}
	Player(GameMessageBox &box) : bag(box){}
	void init() {
		mode = NORMAL_MODE | RIGHT;
		exp_max = 10;
		level = 1;
		hp_max = 20;
		hp_now = 20;
		exp_now = 0;
		CImage img;
		img.Load("img\\player\\right_player.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\player\\left_player.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\player\\head_player.jpg");
		pic.push_back(img.Detach());
		x = 200;
		y = 400;
		img.Destroy();
		bag.init();
	}
	//����
	void paint(HWND hwnd) {
		paintPlayer(hwnd);
		paintMessage(hwnd);
		if(bag.visable)bag.paint(hwnd);
	}
	//ִ�д������
	void run() {
		//������������
		while (exp_max <= exp_now) {
			exp_now -= exp_max;
			exp_max *= 1.1;
			hp_max += 5;
			hp_now = hp_max;
			level++;
		}
		if (hp_now > hp_max)
			hp_now = hp_max;
		switch (mode & 0xf0f0) {
		case NORMAL_MODE | TO_RIGHT:
			if(x <= 890)x += 10;
			mode = mode & 0xff0f;
			break;
		case NORMAL_MODE | TO_LEFT:
			if (x >= 10)x -= 10; 
			mode = mode & 0xff0f;
			break;
		default:
			break;
		}
		switch (mode & 0xff00) {
		case NORMAL_MODE | TO_TOP:
			if (y >= 10)y -= 10;
			mode = mode & 0xf0ff;
			break;
		case NORMAL_MODE | TO_BUTTON:
			if (y <= 500)y += 10;
			mode = mode & 0xf0ff;
			break;
		default:
			break;
		}
	}
	~Player() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
private:
	//��ӡ��ǰ��Ϣ
	void paintMessage(HWND hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		std::string str = "��ǰ�ȼ�:" + int2str(level);
		SetTextColor(g_hdc, RGB(255, 255, 255));
		SetBkColor(g_hdc, RGB(0, 0, 0));
		TextOut(g_hdc, 70, 20, str.c_str(), str.length());
		TextOut(g_hdc, 70, 35, _T("EXP:"), 4);
		TextOut(g_hdc, 70, 50, _T("HP:"), 3);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[2]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, 20, 20, 50, 50, mmhdc, 0, 0, 50, 50, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  																   //BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//�������豸������  
		SelectObject(mmhdc, hp);
		//����ʵ�ߣ����Ϊ2����ɫ�ı�
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		//����ѡ��DC
		HPEN *hOldPen = (HPEN*)SelectObject(g_hdc, hPen);
		//����һ����ɫ��ˢ��
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH *oldBrush = (HBRUSH*)SelectObject(g_hdc, hBrush);
		Rectangle(g_hdc, 100, 35, 300, 50);
		Rectangle(g_hdc, 100, 52, 300, 67);
		//ɾ��Pen
		SelectObject(g_hdc, hOldPen);
		DeleteObject(hPen);
		//����EXP
		HBRUSH anotherBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(g_hdc, anotherBrush);
		Rectangle(g_hdc, 100, 37, 100 + (exp_now * 200 / exp_max), 48);
		//����HP
		HBRUSH otherBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(g_hdc, otherBrush);
		Rectangle(g_hdc, 100, 54, 100 + (hp_now * 200 / hp_max) , 65);
		SetBkMode(g_hdc, TRANSPARENT);
		str = int2str(exp_now) + '/' + int2str(exp_max);
		TextOut(g_hdc, 150, 35, str.c_str(), str.length());
		str = int2str(hp_now) + '/' + int2str(hp_max);
		TextOut(g_hdc, 150, 52, str.c_str(), str.length());
		//�Ż�oldBrush
		SelectObject(g_hdc, oldBrush);
		//ɾ��Brush
		DeleteObject(otherBrush);
		DeleteObject(anotherBrush);
		DeleteObject(hBrush);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	//��ӡ��ҽ�ɫ��ͼ
	void paintPlayer(HWND hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode & 0xf00f) {
		case NORMAL_MODE | RIGHT:
			index = 0;
			break;
		case NORMAL_MODE | LEFT:
			index = 1;
			break;
		default:
			index = 0;
			break;
		}
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, x, y, 50, 75, mmhdc, 0, 0, 50, 75, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  
		//BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//�������豸������  
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	std::string int2str(const int &int_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		return stream.str();
	}
};