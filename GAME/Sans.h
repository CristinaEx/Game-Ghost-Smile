#pragma once
#include "boss.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "LineAttack.h"
#include "PosAttack.h"
#include <vector>

#define SANS_TALK_MODE_1 0x0001
#define SANS_TALK_MODE_2 0x0002
#define SANS_TALK_MODE_3 0x0003
#define SANS_TALK_MODE_4 0x0004
#define SANS_ATTACK_MODE_1 0x0005
#define SANS_ATTACK_MODE_2 0x0006
#define SANS_ATTACK_MODE_3 0x0007
#define SANS_ATTACK_MODE_4 0x0008
#define SANS_NORMAL_MODE_1 0x0009
#define SANS_NORMAL_MODE_2 0x000a
#define SANS_TIRED_MODE 0x000b
#define SANS_END_MODE 0x000c

class Sans : public Boss {
public:
	//攻击模式攻击的点
	int attack_x;
	int attack_y;
	int count = 0;//记录当前流程
	int sleep = 0;//攻击间隔
	std::vector<SpecialAttack *> attacks;//特殊攻击(第0~5为LineAttack,第6~12为PosAttack,其中第十二个为SANS_ATTACK_MODE_3专用)
	Sans(std::string data) {
		srand((unsigned int)(time(NULL)));
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		mode = SANS_NORMAL_MODE_1;
		CImage img;
		img.Load("img\\Sans\\sans_talk_1.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_talk_2.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_talk_3.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_talk_4.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_attack_1.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_attack_2.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_attack_3.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_normal_1.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_normal_2.jpg");
		pic.push_back(img.Detach());
		img.Load("img\\Sans\\sans_tired.jpg");
		pic.push_back(img.Detach());
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new LineAttack(0, 0, 1, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
		attacks.push_back(new PosAttack(0, 0, 1));
	}

	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode) {
		case START_MODE:
			break;
		case SANS_TALK_MODE_1:
			index = 0;
			break;
		case SANS_TALK_MODE_2:
			index = 1;
			break;
		case SANS_TALK_MODE_3:
			index = 2;
			break;
		case SANS_TALK_MODE_4:
			index = 3;
			break;
		case SANS_ATTACK_MODE_1:
			index = 4;
			break;
		case SANS_ATTACK_MODE_2:
			index = 5;
			break;
		case SANS_ATTACK_MODE_3:
			index = 6;
			break;
		case SANS_ATTACK_MODE_4:
			index = 5;
			break;
		case SANS_NORMAL_MODE_1:
			index = 7;
			break;
		case SANS_NORMAL_MODE_2:
			index = 8;
			break;
		case SANS_TIRED_MODE:
			index = 9;
			break;
		case SANS_END_MODE:
			break;
		default:
			index = 0;
			break;
		}
		SelectObject(mmhdc, pic[index]);//将图片放到HDC上  
		TransparentBlt(g_hdc, x, y, 100, 100, mmhdc, 0, 0, 100, 100, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色  																   //BitBlt(g_hdc, x, y, 100, 150, mmhdc, 0, 0, SRCCOPY);//拷贝到设备环境上  
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
		for (auto attack : attacks)
			attack->paint(hwnd);
	}

	void run(Player &player, GameMessageBox &box) {
		switch (count) {
		case 80:
			mode = SANS_TALK_MODE_1;
			box.add("Sans:你好，玩家。你认为这只是一个普通的游戏，不是吗？", 60);
			break;
		case 160:
			mode = SANS_TALK_MODE_2;
			box.add("Sans:但是，你有没有想过，哪个游戏的UI会这么差呢？", 60);
			break;
		case 240:
			mode = SANS_TALK_MODE_1;
			box.add("Sans:就好像...从来没有美工那样？", 60);
			break;
		case 320:
			mode = SANS_TALK_MODE_2;
			box.add("Sans:不过我很高兴得告诉你，这破游戏曾经是有美工的。", 60);
			break;
		case 400:
			mode = SANS_TALK_MODE_3;
			box.add("Sans:想找回美工的话，继续走下去吧，不过我猜你可能要...", 60);
			break;
		case 480:
			mode = SANS_TALK_MODE_4;
			box.add("Sans:留 ", 20);
			break;
		case 500:
			box.add("Sans:留 在", 20);
			break;
		case 520:
			box.add("Sans:留 在 这", 20);
			break;
		case 540:
			box.add("Sans:留 在 这 了", 20);
			break;
		case 560:
			box.add("Sans:留 在 这 了 。", 20);
			break;
		case 580:
			mode = SANS_ATTACK_MODE_3;
			break;
		case 9000:
			mode = SANS_TIRED_MODE;
			break;
		default:
			break;
		}
		//随机进行攻击
		if (count >= 600 && count <= 9000) {
			if(sleep <= 0)mode = rand() % (SANS_ATTACK_MODE_2 - SANS_ATTACK_MODE_1 + 1) + SANS_ATTACK_MODE_1;
			if (mode != SANS_ATTACK_MODE_3 && pow(player.x - x, 2) + pow(player.y - y, 2) <= 10000 && sleep <= 20) {
				mode = SANS_ATTACK_MODE_3;
				sleep = 0;
			}
		}
		switch (mode) {
		case START_MODE:
			break;
		case SANS_NORMAL_MODE_1:
			if (sleep <= 0) {
				mode = SANS_NORMAL_MODE_2;
				sleep = 1;
			}
			else
				sleep--;
			break;
		case SANS_NORMAL_MODE_2:
			if (sleep <= 0) {
				mode = SANS_NORMAL_MODE_1;
				sleep = 1;
			}
			else
				sleep--;
			break;
		case SANS_ATTACK_MODE_1:
			if (sleep <= 0)	
				sleep = 60;
			else
				sleep--;
			if (sleep <= 30 && sleep > 0 && sleep % 5 == 0) {
				(attacks[5 + sleep / 5])->x = player.x;
				(attacks[5 + sleep / 5])->y = player.y;
				(attacks[5 + sleep / 5])->count = 30;
			}
			break;
		case SANS_ATTACK_MODE_2:
			if (sleep <= 0)
				sleep = 60;
			else
				sleep--;
			if (sleep <= 45 && sleep >= 20 && sleep % 5 == 0) {
				int mode = rand() % (LINE_TOP - LINE_RIGHT + 1) + LINE_RIGHT;
				switch (mode) {
				case LINE_LEFT:
					(attacks[sleep / 5 - 4])->x = 0;
					(attacks[sleep / 5 - 4])->y = player.y;
					break;
				case LINE_RIGHT:
					(attacks[sleep / 5 - 4])->x = 900;
					(attacks[sleep / 5 - 4])->y = player.y;
					break;
				case LINE_TOP:
					(attacks[sleep / 5 - 4])->x = player.x;
					(attacks[sleep / 5 - 4])->y = 100;
					break;
				case LINE_BUTTON:
					(attacks[sleep / 5 - 4])->x = player.x;
					(attacks[sleep / 5 - 4])->y = 500;
					break;
				default:
					break;
				}
				(attacks[sleep / 5 - 4])->count = 45;
				((LineAttack *)(attacks[sleep / 5 - 4]))->sleep = 0;
				((LineAttack *)(attacks[sleep / 5 - 4]))->mode = mode;
			}
			break;
		case SANS_ATTACK_MODE_3:
			if (sleep <= 0) {
				(attacks[12])->x = 0;
				(attacks[12])->y = player.y;
				(attacks[12])->count = 30;
				sleep = 15;
			}
			else if (sleep > 5) {
				player.x -= (player.x / (sleep - 5));
				sleep--;
			}
			else if (sleep == 5) {
				sleep--;
			}
			else
				sleep--;
			break;
		case SANS_TIRED_MODE:
			//...
			break;
		case SANS_END_MODE:
			//...
			break;
		default:
			break;
		}
		for (auto attack : attacks)
			attack->run(player);
		count++;
	}
private:
	//使用c作为分隔符切割字符串s
	std::vector<std::string> splitString(const std::string& s, const char c)
	{
		std::vector<std::string> result;
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			result.push_back(s.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 1;
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			result.push_back(s.substr(pos1));
		return result;
	}

	//string -> int
	int str2int(const std::string &string_temp)
	{
		std::stringstream stream(string_temp);
		int int_temp;
		stream >> int_temp;
		return int_temp;
	}
	~Sans() {
		for (auto attack : attacks)
			delete attack;
	}
};