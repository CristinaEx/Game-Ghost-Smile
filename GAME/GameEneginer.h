#pragma once
#include "windows.h"
#include "MusicPlayer.h"
#include "GameMessageBox.h"
#include "map.h"

//游戏引擎
class GameEneginer {
public:
	HWND hwnd;//主窗口句柄
	Map map;//地图
	Player player;//玩家
	GameMessageBox box;//消息盒
	GameEneginer() {}
	GameEneginer(HWND &hwnd, MusicPlayer &py) : box(hwnd){
		this->hwnd = hwnd;
		map = Map(py);
		player = Player(box);
	}
	//游戏内容初始化
	//若data_path为NULL，则创建新游戏
	void init(std::string data_path = "") {
		if (data_path.empty()) {
			//创建新游戏
			map.init(1608);
			player.init();
		}
		else {
			//载入游戏
		}
	}
	//进行活动
	void run() {
		//处理玩家死亡消息
		if (player.hp_now <= 0)
			over();
		else {
			paintPic(map.background);
			//加载玩家信息
			player.run();
			//地图元素
			map.run(player, box);
			dealMeaasge();
			map.paint(hwnd);
			player.paint(hwnd);
		}
		box.run();
	}
private:

	//绘制图片
	void paintPic(HBITMAP &bg , int x = 0,int y = 0) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
		BitBlt(g_hdc, x, y, 960, 640, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}

	//死亡界面
	void over() {
		box.add("Game Over ! (继续请按空格,返回标题画面请按回车)", 30);
		if (player.hp_now == 0) {
			map.player.close();
			CImage img;
			img.Load("img\\over.jpg");
			HBITMAP bg = img.Detach();
			paintPic(bg);
			map.player.play("bgm\\start.wav");
			player.hp_now = -1;
			box.element_message = GAMEENEGINER | CHECK_EMPTY;
			DeleteObject(bg);
			img.Destroy();
		}
		else{
			if (box.element_message == (PLAYER | CHECK_TRUE)) {
				player.hp_now = player.hp_max;
				map.init(map.map_mode);
			}
		}
	}

	//处理messagebox的消息
	void dealMeaasge() {
		if (box.mode == 0)
			return;
		switch (box.element_message & 0xf000) {
		case PLAYER:
			break;
		case DOOR:
			map.init(0x0fff & box.element_message);
			box.element_message = CHECK_EMPTY;
			break;
		default:
			break;
		}
	}
};