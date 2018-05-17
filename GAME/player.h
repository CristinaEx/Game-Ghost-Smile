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


//玩家角色
class Player{
public:
	int exp_max;//当前等级最大经验值
	int level;//等级
	int hp_max;//当前等级最大血量
	int mode;//当前状态
	int hp_now;//当前血量
	int exp_now;//当前经验值
	int x;//横坐标
	int y;//纵坐标
	std::vector<HBITMAP> pic;//贴图
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
	//绘制
	void paint(HWND hwnd) {
		paintPlayer(hwnd);
		paintMessage(hwnd);
	}
	//执行处理操作
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
	//打印当前信息
	void paintMessage(HWND hwnd) {
		HDC g_hdc = GetDC(hwnd);
		std::string str = "当前等级:" + 
			int2str(level) + 
			"  经验值:" + 
			int2str(exp_now) + '/' + int2str(exp_max) +
			"  HP:" + 
			int2str(hp_now) + '/' + int2str(hp_max);
		TextOut(g_hdc, 20, 20, str.c_str(), str.length());
		ReleaseDC(hwnd, g_hdc);
	}
	//打印玩家角色贴图
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
		SelectObject(mmhdc, pic[index]);//将图片放到HDC上  
		TransparentBlt(g_hdc, x, y, 50, 75, mmhdc, 0, 0, 50, 75, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色  
		//BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
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