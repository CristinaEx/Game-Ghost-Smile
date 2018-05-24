#pragma once
#include "boss.h"
#include "DataDealer.h"
#include <vector>
#include "FallAttack.h"
#include "MoveAttack.h"
#include <cstdlib>
#include <ctime>

#define UNDYNE_TALK_MODE 0x0001
#define UNDYNE_ATTACK_MODE_1 0x0002
#define UNDYNE_ATTACK_MODE_2 0x0003
#define UNDYNE_ATTACK_MODE_3 0x0004
#define UNDYNE_TIRED_MODE 0x0005
#define UNDYNE_END_MODE 0x0006

#define UNDYNE_DATA_NAME "undyne.dat"

class Undyne : public Boss {
public:
	int count = 0;//��¼��ǰ����
	int sleep = 0;//��¼�������
	//����ģʽ�����ĵ�
	int attack_x;
	int attack_y;
	std::vector<SpecialAttack *> attacks;//���⹥��(��0~2ΪMoveAttack,��3~5ΪFallAttack)
	Undyne(std::string data) {
		srand((unsigned int)(time(NULL)));
		std::vector<std::string> datas = splitString(data, ' ');
		x = str2int(datas[0]);
		y = str2int(datas[1]);
		CImage img;
		img.Load("img\\undyne\\undyne_talk.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		img.Load("img\\undyne\\undyne_attack.jpg");
		pic.push_back(img.Detach());
		img.Destroy();
		mode = UNDYNE_TALK_MODE;
		attacks.push_back(new MoveAttack(0, 1));
		attacks.push_back(new MoveAttack(0, 1));
		attacks.push_back(new MoveAttack(0, 1));
		attacks.push_back(new FallAttack(0, 0, 1));
		attacks.push_back(new FallAttack(0, 0, 1));
		attacks.push_back(new FallAttack(0, 0, 1));
		if (DataDealer::checkFileExist(std::string(DATA_PATH) + std::string(UNDYNE_DATA_NAME)))
		{
			mode = UNDYNE_END_MODE;
			count = 100000;
		}
	}
	void paint(HWND &hwnd) {
		HDC g_hdc = GetDC(hwnd);
		HDC mmhdc = CreateCompatibleDC(g_hdc);
		int index;
		switch (mode) {
		case UNDYNE_TALK_MODE:
			index = 0;
			break;
		case UNDYNE_ATTACK_MODE_1:
			index = 1;
			break;
		case UNDYNE_ATTACK_MODE_2:
			index = 1;
			break;
		case UNDYNE_ATTACK_MODE_3:
			index = 1;
			break;
		case UNDYNE_TIRED_MODE:
			index = 0;
			break;
		case UNDYNE_END_MODE:
			index = 0;
			break;
		default:
			index = 1;
			break;
		}
		HBITMAP *hp = (HBITMAP *)SelectObject(mmhdc, pic[index]);//��ͼƬ�ŵ�HDC��  
		TransparentBlt(g_hdc, x, y, 75, 105, mmhdc, 0, 0, 75, 105, RGB(1, 1, 1));//RGB(1,1,1)�����Զ����ɫ  	
		SelectObject(mmhdc, hp);
		DeleteDC(mmhdc);
		ReleaseDC(hwnd, g_hdc);
		for (auto attack : attacks)
			attack->paint(hwnd);
	}
	void run(Player &player, GameMessageBox &box) {
		switch (count) {
		case 130:
			box.add("Undyne:ι�������ߣ����뵽����ȥ?",90);
			break;
		case 300:
			mode = UNDYNE_ATTACK_MODE_1;
			break;
		case 330:
			box.add("Undyne:���Ӳ����ġ�", 90);
			break;
		case 5500:
			box.add("������Undyne�Ѿ������ˡ�", 90);
			DataDealer::writeFile(std::string(DATA_PATH) + std::string(UNDYNE_DATA_NAME), "1");
			mode = UNDYNE_TIRED_MODE;
			box.element_message = CHECK_EMPTY;
			break;
		case 5600:
			box.add("���Undyne���۵�ʱ����������ҽ������~", 90);
			break;
		case 100030:
			box.add("Undyne:��...", 100);
			break;
		default:
			break;
		}
		//������й���
		if (count >= 300 && count <= 5500 && sleep <= 0) {
			mode = rand() % (UNDYNE_ATTACK_MODE_3 - UNDYNE_ATTACK_MODE_2 + 1) + UNDYNE_ATTACK_MODE_2;
			if (mode != UNDYNE_ATTACK_MODE_1 && pow(player.x - x, 2) + pow(player.y - y, 2) <= 3600 && sleep <= 20) {
				mode = UNDYNE_ATTACK_MODE_1;
				sleep = 0;
			}
		}
		switch (mode) {
		case UNDYNE_TALK_MODE:
			break;
		case UNDYNE_ATTACK_MODE_1:
			if (sleep <= 0)
				sleep = 20;
			else
				sleep--;
			if (sleep == 10){
				if (pow(player.x - x, 2) + pow(player.y - y, 2) <= 3600) {
					player.hp_now -= 2;
					box.add("��Ҫ����Undyne!�������ƿ��ܻ��˵���!", 30);
				}
				
			}
			break;
		case UNDYNE_ATTACK_MODE_2:
			if (sleep <= 0)
				sleep = 45;
			else
				sleep--;
			if (sleep < 20 && sleep % 5 == 0 && sleep > 0) {
				attacks[sleep / 5 + 2]->count = 30;
				attacks[sleep / 5 + 2]->x = player.x;
				attacks[sleep / 5 + 2]->y = player.y;
			}
			break;
		case UNDYNE_ATTACK_MODE_3:
			if (sleep <= 0)
				sleep = 45;
			else
				sleep--;
			if (sleep < 20 && sleep % 5 == 0 && sleep > 0) {
				attacks[sleep / 5 - 1]->count = 30;
				attacks[sleep / 5 - 1]->x = 0;
				attacks[sleep / 5 - 1]->y = player.y;
			}
			break;
		case UNDYNE_TIRED_MODE:
			if (pow(x - player.x, 2) + pow(y - player.y, 2) <= 1600) {
				box.add("Papyrus:��С�һ��Ҫ��ʲô��", 50);
				mode = UNDYNE_END_MODE;
				sleep = 100;
			}
			break;
		case UNDYNE_END_MODE:
			if (sleep != 0)
				sleep--;
			else
			{
				box.add("��", 90);
				mode = 0xf000;
			}
			break;
		default:
			break;
		}
		for (auto attack : attacks)
			attack->run(player);
		count++;
	}
private:
	//ʹ��c��Ϊ�ָ����и��ַ���s
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
	~Undyne() {
		for (HBITMAP hp : pic)
			DeleteObject(hp);
	}
};