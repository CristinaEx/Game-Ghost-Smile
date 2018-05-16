#pragma once
#include<windows.h>
#include <mmsystem.h>
#include<dsound.h>
#include<string>
#include <sstream>
#pragma comment(lib, "WINMM.LIB")
class MusicPlayer {
public:
	//当前播放的音乐的名字
	std::string music_name = "";

	//播放音乐
	//file_path_name 为音乐的路径+文件名
	//command需包括空格
    void play(std::string file_path_name,std::string command = "")
	{
		this->music_name = file_path_name;
		mciSendString(TEXT(("open " + this->music_name).c_str()), NULL, 0, NULL);
		mciSendString(TEXT(("play " + this->music_name + command).c_str()), NULL, 0, NULL);
	}
	//关闭音乐
	void close() {
		if (!music_name.empty()) {
			mciSendString(TEXT(("stop " + this->music_name).c_str()), NULL, 0, NULL);
			mciSendString(TEXT(("close " + this->music_name).c_str()), NULL, 0, NULL);
		}
		this->music_name.clear();
	}
	//设置音量
	void setVolume(int volume) {
		mciSendString(TEXT(("setaudio movie volume to " + this->int2str(volume)).c_str()), NULL, 0, NULL);
	}
	//获取音量大小
	int getVolume() {
		char V[5];
		mciSendString(TEXT(std::string("status movie volume").c_str()), V, 5, NULL);
		int result = 0;
		int mod = 0;
		for (int index = 4; index >= 0; index--) {
			if (V[index] == '\0')mod = 1;
			result += (V[index] - 48) * mod;
			mod *= 10;
		}
		return result;
	}
private:
	//把字符串转为wchar_t
	wchar_t *multiByteToWideChar(std::string& str)
	{
	    char * pCStrKey = const_cast<char*>(str.c_str());
		//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
		int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
		wchar_t *pWCStrKey = new wchar_t[pSize];
		//第二次调用将单字节字符串转换成双字节字符串
		MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
		return pWCStrKey;
	}

	//把整形对应数字转为字符串
	std::string int2str(const int &int_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		return stream.str();   //此处也可以用 stream>>string_temp  
	}
};
