#pragma once

#include "boss.h"
#include "DataDealer.h"

#define ASRIEL_START_MODE 0x0001
#define ASRIEL_TALK_MODE 0x0002
#define ASRIEL_END_MODE 0x0004

class Asriel : public Boss {
public:
	int count = 0;//记录当前流程
	Asriel(std::string data) {
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		CImage img;
		img.Load("img\\asriel\\asriel.png");
		pic.push_back(img.Detach());
		img.Destroy();
		mode = ASRIEL_START_MODE;
	}
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode) {
		case ASRIEL_START_MODE:
			index = 0;
			break;
		default:
			index = 0;
			break;
		}
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//将图片放到HDC上  
		TransparentBlt(g_hdc, x, y, 70, 115, mmhdc, 0, 0, 70, 115, RGB(1, 1, 1));//RGB(1,1,1)代表自定义黑色  	
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
	}
	void run(Player &player, GameMessageBox &box) {
		switch (count) {
		case 30:
			box.add("喔喔喔喔，这里充满了美工的气息!", 150);
			break;
		case 200:
			box.add("简直太令人高兴啦，这个游戏可以吸引更多的人了呀!", 150);
			break;
		case 360:
			box.add("为了庆祝一下，稍微把这里核爆吧~", 150);
			break;
		case 520:
			box.add("[点击空格使用核爆]", 50);
			break;
		case 680:
			box.add("哦，抱歉，这次不需要你来操作了呢!", 150);
			break;
		case 840:
			box.add("不过恭喜你!你可以获得超多的EXP，因为这里的怪物都会死掉呢~", 150);
			break;
		case 1000:
			box.add("哈哈哈哈哈哈哈哈哈", 150);
			break;
		case 1240:
			box.add("Asriel:你就是Sans说的会给我们带来灾难的人吗？", 150);
			break;
		case 1400:
			box.add("Asriel:我们在这已经生活了很久了，已经不再想有纷争了......", 150);
			break;
		case 1560:
			box.add("Asriel:Sans说，如果你已经到这了，事情就已经到了很严重的地步了。", 150);
			break;
		case 1720:
			box.add("Asriel:但并不是无法挽回的局面。", 150);
			break;
		case 1880:
			box.add("Asriel:Sans要我把SAVE给你。", 150);
			break;
		case 2040:
			box.add("Asriel:他说，\"存档点已经被清除了，SAVE已经无法用来存档了，但可以用来SAVE\"。", 150);
			break;
		case 2200:
			box.add("Asriel:点击S使用SAVE。", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2360:
			box.add("Asriel:我不懂Sans的意思，但是他说你一定会明白。", 150);
			mode = ASRIEL_END_MODE;
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2520:
			box.add("别听他的！如果SAVE后你就无法拥有经验值了！", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2680:
			box.add("我把核爆的按钮给你！你可以自己体验到一瞬间杀死所有怪物的快感！", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2800:
			box.add("[点击空格使用核爆][点击空格使用核爆][点击空格使用核爆]", 100);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 2900:
			box.add("Asriel:希望你可以拯救我们的家园。", 150);
			box.element_message = END | CHECK_EMPTY;
			break;
		case 3000:
			box.add("[点击空格使用核爆][点击空格使用核爆][点击空格使用核爆]", 1000);
			box.element_message = END | CHECK_EMPTY;
			break;
		}
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
	~Asriel() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
};