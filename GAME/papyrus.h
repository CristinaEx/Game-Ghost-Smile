#pragma once
#include "boss.h"
#include "DataDealer.h"
#include "HpAdder.h"

#define PAPYRUS_START_MODE 0x0001
#define PAPYRUS_STAND_MODE_LEFT 0x0002
#define PAPYRUS_STAND_MODE_RIGHT 0x0003
#define PAPYRUS_TALK_MODE_1 0x0004
#define PAPYRUS_TALK_MODE_2 0x0005
#define PAPYRUS_TALK_MODE_3 0x0006
#define PAPYRUS_TALK_MODE_4 0x0007
#define PAPYRUS_LEAVING_MODE_1 0x0008
#define PAPYRUS_LEAVING_MODE_2 0x0009
#define PAPYRUS_GO_MODE 0x000a
#define PAPYRUS_GOING_MODE 0x000b

#define PAPYRUS_DATA_NAME "papyrus.dat"

class Papyrus : public Boss {
public:
	bool exist = true;//是否存在
	int count = 0;//记录当前流程
	Papyrus(std::string data) {
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		//注:因为Papyrus在两个地图中有不同的形态，必须在第三个参数规定它的mode
		//1605->PAPYRUS_START_MODE
		//1606->PAPYRUS_LEAVING_MODE_2
		//1607->PAPYRUS_GO_MODE
		mode = str2int(datas[2]);
		CImage img;
		img.Load("img\\Papyrus\\papyrus_left.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\Papyrus\\papyrus_right.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\Papyrus\\papyrus_talk_1.png");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\Papyrus\\papyrus_talk_2.png");
		pic.push_back(img.Detach());
		img.Destroy();
		if (DataDealer::checkFileExist(std::string(DATA_PATH) + std::string(PAPYRUS_DATA_NAME))) {
			//data存在
			int type = str2int(DataDealer::readFileFirstLine(std::string(DATA_PATH) + std::string(PAPYRUS_DATA_NAME)));
			switch (type) {
			case 1:
				count = 1000;//Papyrus离开1605地图，开始1606的时间
				if (mode != PAPYRUS_LEAVING_MODE_2)
					exist = false;
				break;
			case 2:
				count = 2000;//Papyrus离开1606地图，开始1607的时间
				if (mode != PAPYRUS_GO_MODE)
					exist = false;
				break;
			default:
				break;
			}
		}
		else if (mode != PAPYRUS_START_MODE)
			exist = false;
	}
	void paint(HWND &hwnd) {
		if (exist) {
			HDC g_hdc = GetDC(hwnd);
			HDC mmhdc = CreateCompatibleDC(g_hdc);
			int index;
			switch (mode) {
			case PAPYRUS_START_MODE:
				index = 1;
				break;
			case PAPYRUS_STAND_MODE_LEFT:
				index = 0;
				break;
			case PAPYRUS_STAND_MODE_RIGHT:
				index = 1;
				break;
			case PAPYRUS_TALK_MODE_1:
				index = 0;
				break;
			case PAPYRUS_TALK_MODE_2:
				index = 1;
				break;
			case PAPYRUS_TALK_MODE_3:
				index = 2;
				break;
			case PAPYRUS_TALK_MODE_4:
				index = 3;
				break;
			default:
				index = 1;
				break;
			}
			HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//将图片放到HDC上  
			TransparentBlt(g_hdc, x, y, 65, 100, mmhdc, 0, 0, 65, 100, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色  	
			SelectObject(mmhdc, hp);
			DeleteDC(mmhdc);
			ReleaseDC(hwnd, g_hdc);
		}
	}
	void run(Player &player, GameMessageBox &box) {
		if (exist) {
			switch (count) {
			case 40:
				box.add("Papyrus:你是Sans说的那个新来的坏家伙吗？你怎么跑到这里来了？",90);
				break;
			case 140:
				box.add("Papyrus:看起来你是从Sans那偷偷的溜过来的嘛~", 90);
				mode = PAPYRUS_TALK_MODE_3;
				break;
			case 240:
				box.add("Papyrus:新来的家伙，看起来你也不是很像坏人嘛，你是做过很多恶作剧吗？", 90);
				mode = PAPYRUS_TALK_MODE_1;
				break;
			case 340:
				box.add("Papyrus:偷偷告诉你一个秘密，其实我也经常把Sans的巧克力棒藏起来...", 90);
				break;
			case 440:
				box.add("Papyrus:然后吃掉啦~", 50);
				mode = PAPYRUS_TALK_MODE_3;
				break;
			case 500:
				box.add("Papyrus:你可不要告诉Sans哦...", 90);
				mode = PAPYRUS_TALK_MODE_1;
				break;
			case 600:
				box.add("Papyrus:嗨小家伙，我想我有一点喜欢你了。", 90);
				break;
			case 700:
				box.add("Papyrus:但是要是Undyne知道了肯定会不高兴的吧...", 90);
				break;
			case 800:
				box.add("Papyrus:这样吧，跟我来，我带你去找Asriel。", 90);
				break;
			case 850:
				box.add("Papyrus:你先拿着这个!可能会用得上的!", 50);
				break;
			case 900:
				mode = PAPYRUS_LEAVING_MODE_1;
				player.bag.add(new HpAdder(20));
				player.bag.add(new HpAdder(20));
				player.bag.add(new HpAdder(20));
				box.add("获得:生命恢复药剂(HP+20)*3，按B打开背包查看使用按键。", 100);
				break;
			case 1010:
				box.add("Papyrus:这边来!", 50);
				break;
			case 2030:
				box.add("Papyrus:这条路一直往下走就是Asriel家了......",90);
				break;
			case 2230:
				box.add("Papyrus:糟了，我们被Undyne发现了，小家伙，快跟我走！", 90);
				mode = PAPYRUS_GOING_MODE;
				break;
			case 8030:
				box.add("Papyrus:你自己进去找Asriel吧，小家伙，我们下次再见~", 90);
				mode = PAPYRUS_GOING_MODE;
				break;
			}
			switch (mode) {
			case PAPYRUS_START_MODE:
				if (player.x >= 400)
					mode = PAPYRUS_STAND_MODE_LEFT;
				break;
			case PAPYRUS_STAND_MODE_LEFT:
				x += 20;
				box.add("Papyrus:呀!", 30);
				mode = PAPYRUS_TALK_MODE_1;
				break;
			case PAPYRUS_TALK_MODE_1:
				if (player.x > 500)
					mode = PAPYRUS_TALK_MODE_2;
				break;
			case PAPYRUS_TALK_MODE_2:
				if (player.x < 500)
					mode = PAPYRUS_TALK_MODE_1;
				break;
			case PAPYRUS_TALK_MODE_3:
				if (player.x > 500)
					mode = PAPYRUS_TALK_MODE_4;
				break;
			case PAPYRUS_TALK_MODE_4:
				if (player.x < 500)
					mode = PAPYRUS_TALK_MODE_3;
				break;
			case PAPYRUS_LEAVING_MODE_1:
				//去1606
				if (x < 725)x += 10;
				else if (y > 140)y -= 10;
				else {
					exist = false;
					DataDealer::writeFile(std::string(DATA_PATH) + std::string(PAPYRUS_DATA_NAME),"1");
				}
				break;
			case PAPYRUS_LEAVING_MODE_2:
				//去1607
				if (x < 900)x += 10;
				else {
					exist = false;
					DataDealer::writeFile(std::string(DATA_PATH) + std::string(PAPYRUS_DATA_NAME), "2");
				}
				break;
			case PAPYRUS_GO_MODE:
				break;
			}
		}
		if (mode != PAPYRUS_START_MODE)
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
	~Papyrus() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
};