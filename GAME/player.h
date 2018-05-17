#pragma once
#include "Element.h"
#include <atlimage.h>
#include <string>
#include <sstream>

#define RIGHT 0x0000
#define LEFT 0x0001

#define TO_RIGHT 0x0010
#define TO_LEFT 0x0020
#define TO_TOP 0x0030
#define TO_BUTTON 0x0040
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
	Player(){}
	void init() {
		mode = NORMAL_MODE | RIGHT;
		exp_max = 10;
		level = 1;
		hp_max = 20;
		hp_now = 20;
		exp_now = 0;
		CImage img;
		img.Load("img\\right_player.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\left_player.jpg");
		pic.push_back(img.Detach());
		x = 200;
		y = 400;
	}
	//����
	void paint(HWND hwnd) {
		paintPlayer(hwnd);
		paintMessage(hwnd);
	}
	//ִ�д������
	void run() {
		switch (mode & 0xfff0) {
		case NORMAL_MODE | TO_RIGHT:
			if(x <= 890)x += 10;
			mode = mode & 0x1001;
			break;
		case NORMAL_MODE | TO_LEFT:
			if (x >= 10)x -= 10; 
			mode = mode & 0x1001;
			break;
		case NORMAL_MODE | TO_TOP:
			if (y >= 10)y -= 10;
			mode = mode & 0x1001;
			break;
		case NORMAL_MODE | TO_BUTTON:
			if (y <= 500)y += 10;
			mode = mode & 0x1001;
		default:
			break;
		}
	}
private:
	//��ӡ��ǰ��Ϣ
	void paintMessage(HWND hwnd) {
		HDC g_hdc = GetDC(hwnd);
		std::string str = "��ǰ�ȼ�:" + 
			int2str(level) + 
			"  ����ֵ:" + 
			int2str(exp_now) + '/' + int2str(exp_max) +
			"  HP:" + 
			int2str(hp_now) + '/' + int2str(hp_max);
		TextOut(g_hdc, 20, 20, str.c_str(), str.length());
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
		SelectObject(mmhdc, pic[index]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, x, y, 50, 75, mmhdc, 0, 0, 50, 75, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  
		//BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//�������豸������  
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