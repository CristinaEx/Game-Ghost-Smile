#pragma once

#include "resource.h"
#include "button.h"
#include "map.h"
#include "GameEneginer.h"
#include "DataDealer.h"

#ifndef _GAME_H

#define GAME_PRE 1201
#define GAME_START 1202
#define GAME_RUNNING 1203
#define GAME_BGMBOX 1204
#define GAME_SET 1205

#define GAME_END 1206

//控制游戏的流程
class GameControl {
public:
	MusicPlayer player;//音乐播放
	GameEneginer game_eneginer; //游戏引擎
	int mode;//流程
	GameControl(HWND &hwnd){
		this->hwnd = hwnd;
		this->mode = GAME_PRE;
		this->player = MusicPlayer();
		this->game_eneginer = GameEneginer(hwnd, player);
	}
	GameControl(){}
	~GameControl() {
	}
	//初始化结局
	void pre_end() {
		end_check = true;
		mode = GAME_END;
		game_eneginer.map.player.close();
		switch (str2int(DataDealer::readFileFirstLine("data\\end.dat"))) {
		case 1:
			end_mode = 0;//核爆结局
			player.play("bgm\\start233.wav");
			break;
		case 2:
			end_mode = 1;//拯救结局
			player.play("bgm\\wind.wav");
			break;
		default:
			end_mode = 0;
		}
	}
	//初始化界面
	//对应WM_PAINT
	void wmPaint(HDC &hdc) {
		switch (this->mode) 
		{
		case GAME_PRE:
			//表示当前在游戏主界面
			this->pre(hdc);
			break;
		case GAME_START:
			//开始游戏
			buttons.eraseButton();
			paint("img\\start.png");
			break;
		case GAME_RUNNING:
			//在游戏进行中
			break;
		default:
			return;
		}
	}
	//游戏开始
	//data_path 为读取文件名(默认保存在data//文件夹内)
	void start(std::string data_path = "") {
		this->data_path = data_path;
		this->mode = GAME_START;
	}
	//进行流程
	void run() {
		switch (this->mode)
		{
		case GAME_PRE:
			//表示当前在游戏主界面
			break;
		case GAME_START:;
			//开始新游戏
			DataDealer::clearPath(DATA_PATH);
			buttons.eraseButton();
			paint("img\\start.png");
			player.close();
			//进行加载地图等耗时操作
			this->game_eneginer.init(this->data_path);
			this->mode = GAME_RUNNING;
			break;
		case GAME_RUNNING:
			//在游戏进行中
			game_eneginer.run();
			break;
		case GAME_END:
			end();
			break;
		default:
			return;
		}
	}
	//游戏初始界面预处理
	void pre(HDC &hdc) {
		player.play("bgm\\koko.wav", "");
		this->prePaint(hdc);
		//读取存档等操作
		buttons.addButton(hwnd, end_check);
	}
private:
	int end_mode;
	bool end_check = false;
	//游戏进入前界面绘画
	void prePaint(HDC &hdc) {
		CImage img;
		img.Load("img\\begin.jpg");
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
		RECT rect;
		GetClientRect(hwnd, &rect);
		BitBlt(hdc, 0, 0, rect.right, rect.bottom, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		SelectObject(mmhdc, hp);
		DeleteObject(bg);
		DeleteDC(mmhdc);
		TextOut(hdc, 800, 500, _T("Ghost Smile"), 11);
		img.Destroy();
	}
	//绘图
	void paint(const char* pic_name) {
		HDC g_hdc = GetDC(hwnd);
		CImage img;
		img.Load(pic_name);
		HBITMAP bg = img.Detach();
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
		BitBlt(g_hdc, 0, 0, 960, 640, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		SelectObject(mmhdc, hp);
		DeleteObject(bg);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
		img.Destroy();
	}
	//END
	void end() {
		static int count = 0;
		if (end_mode) {
			//拯救结局
			paint("img\\end_2\\1.jpg");
			if (count >= 160 && count <= 1830) {
				HDC g_hdc = GetDC(hwnd);
				CImage img;
				img.Load("img\\end_2\\sans.jpg");
				HBITMAP bg = img.Detach();
				HDC mmhdc = CreateCompatibleDC(g_hdc);
				HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
				BitBlt(g_hdc, 80, 530, 50, 50, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
				SelectObject(mmhdc, hp);
				DeleteObject(bg);
				DeleteDC(mmhdc);
				ReleaseDC(hwnd, g_hdc);
				img.Destroy();
			}
			switch (count) {
			case 0:
				game_eneginer.box.add("Sans:嘟嘟嘟...", 150);
				break;
			case 160:
				game_eneginer.box.add("Sans:喂喂，接通了吗？", 150);
				break;
			case 320:
				game_eneginer.box.add("Sans:你好，玩家。", 150);
				break;
			case 480:
				game_eneginer.box.add("Sans:那个，我不太会表达感谢。", 150);
				break;
			case 640:
				game_eneginer.box.add("Sans:不过，呃，谢谢你了。", 150);
				break;
			case 800:
				game_eneginer.box.add("Sans:Papyrus很想念你，他说你可以和他一起做恶作剧。", 150);
				break;
			case 960:
				game_eneginer.box.add("Sans:但愿别是什么把我的巧克力藏起来之类的了。", 150);
				break;
			case 1200:
				game_eneginer.box.add("Sans:那个，我说。", 150);
				break;
			case 1360:
				game_eneginer.box.add("Sans:不要再回来了，让我们好好生活吧。", 150);
				break;
			case 1520:
				game_eneginer.box.add("Sans:不论是你还是我们，都有一段美好的回忆，这就足够了，不是么？。", 150);
				break;
			case 1680:
				game_eneginer.box.add("Sans:不要再回来了。", 150);
				break;
			case 1840:
				game_eneginer.box.add("嘟嘟嘟...", 150);
				break;
			case 5500:
				mode = GAME_PRE;
				HDC g_hdc = GetDC(hwnd);
				pre(g_hdc);
				ReleaseDC(hwnd, g_hdc);
				player.close();
				count = 0;
				break;
			}
		}
		else {
			//核爆结局
			paint("img\\end_1\\1.jpg");
			if (count >= 160 && count <= 1490) {
				HDC g_hdc = GetDC(hwnd);
				CImage img;
				img.Load("img\\end_1\\sans.jpg");
				HBITMAP bg = img.Detach();
				HDC mmhdc = CreateCompatibleDC(g_hdc);
				HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, bg);//将图片放到HDC上  
				BitBlt(g_hdc, 80, 530, 50, 50, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
				SelectObject(mmhdc, hp);
				DeleteObject(bg);
				DeleteDC(mmhdc);
				ReleaseDC(hwnd, g_hdc);
				img.Destroy();
			}
			switch (count) {
			case 0:
				game_eneginer.box.add("Sans:嘟嘟嘟...", 150);
				break;
			case 160:
				game_eneginer.box.add("Sans:喂喂，接通了吗？",150);
				break;
			case 320:
				game_eneginer.box.add("Sans:你好，玩家。", 150);
				break;
			case 480:
				game_eneginer.box.add("Sans:拖你的福，怪物世界变成了一片废墟。", 150);
				break;
			case 640:
				game_eneginer.box.add("Sans:Asriel死了，Undyne也死了，几乎所有怪物都死了。", 150);
				break;
			case 800:
				game_eneginer.box.add("Sans:Papyrus很伤心，因为他的朋友们都不见了，包括那只小幽灵。", 150);
				break;
			case 1120:
				game_eneginer.box.add("Sans:嘿，我说。", 150);
				break;
			case 1280:
				game_eneginer.box.add("Sans:不要再回来了，不然你可能会有一段不太愉快的时光。", 150);
				break;
			case 1440:
				game_eneginer.box.add("Sans:你这个肮脏的 杀 人 犯。", 150);
				break;
			case 1500:
				game_eneginer.box.add("嘟嘟嘟...", 150);
				break;
			case 2600:
				mode = GAME_PRE;
				HDC g_hdc = GetDC(hwnd);
				pre(g_hdc);
				ReleaseDC(hwnd,g_hdc);
				player.close();
				count = 0;
				break;
			}
		}
		game_eneginer.box.run();
		count++;
	}
	//string -> int
	int str2int(const std::string &string_temp)
	{
		std::stringstream stream(string_temp);
		int int_temp;
		stream >> int_temp;
		return int_temp;
	}
protected:
	HWND hwnd;//主窗口句柄
	Buttons buttons;//开始界面的按钮
	std::string data_path; //读取文件路径
};

#endif
