#pragma once
#include<windows.h>


//游戏内静态元素只拥有贴图，而且只在小于一个单位距离时才会触发效果
class StaticElement {
public:
	HBITMAP pic;//贴图
	virtual void affect() = 0;//触发效果
};