#pragma once
#define BUTTON_START 10086
#define BUTTON_SET 10087
#define BUTTON_BGMBOX 10088
#define BUTTON_EXIT 10090
#define BUTTON_LOAD 10091

class Buttons {
private:
	HWND button_start;
	HWND button_load;
	HWND button_set;
	HWND button_bgmbox;
	HWND button_exit;
	bool alive;
	//添加按钮
	//hwnd:当前句柄
	//load:是否添加读取按钮
	void createButton(HWND hwnd, bool load = false) {
		int pos = 110;
		//开始按钮
		button_start = CreateWindow(TEXT("button"),
			TEXT("START"), //text
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //style
			100, //x_pos
			pos, //y_pos
			100, //width
			50, //height
			hwnd,
			(HMENU)BUTTON_START,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		pos += 60;
		//读取按钮
		if (load) {
			button_load = CreateWindow(TEXT("button"),
				TEXT("LOAD"), //text
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //style
				100, //x_pos
				pos, //y_pos
				100, //width
				50, //height
				hwnd,
				(HMENU)BUTTON_LOAD,
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			pos += 60;
		}
		//设置按钮
		button_set = CreateWindow(TEXT("button"),
			TEXT("SET"), //text
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //style
			100, //x_pos
			pos, //y_pos
			100, //width
			50, //height
			hwnd,
			(HMENU)BUTTON_SET,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		pos += 60;
		//音乐盒按钮
		button_bgmbox = CreateWindow(TEXT("button"),
			TEXT("BGM BOX"), //text
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //style
			100, //x_pos
			pos, //y_pos
			100, //width
			50, //height
			hwnd,
			(HMENU)BUTTON_BGMBOX,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		pos += 60;
		//结束按钮
		button_exit = CreateWindow(TEXT("button"),
			TEXT("EXIT"), //text
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //style
			100, //x_pos
			pos, //y_pos
			100, //width
			50, //height
			hwnd,
			(HMENU)BUTTON_EXIT,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
	}
public:
	Buttons() {
		alive = false;
	}
	void addButton(HWND hwnd, bool load = false) {
		if (alive) {
			ShowWindow(button_start, SW_SHOW);
			ShowWindow(button_load, SW_SHOW);
			ShowWindow(button_set, SW_SHOW);
			ShowWindow(button_bgmbox, SW_SHOW);
			ShowWindow(button_exit, SW_SHOW);
		}
		else {
			alive = true;
			createButton(hwnd, load);
		}
	}
	void eraseButton() {
		ShowWindow(button_start, SW_HIDE);
		ShowWindow(button_load, SW_HIDE);
		ShowWindow(button_set, SW_HIDE);
		ShowWindow(button_bgmbox, SW_HIDE);
		ShowWindow(button_exit, SW_HIDE);
	}
};