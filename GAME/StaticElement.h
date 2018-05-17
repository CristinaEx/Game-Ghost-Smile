#pragma once
#include<windows.h>
#include"Element.h"

//游戏内静态元素可以不拥有贴图只在小于一个单位距离时才会触发效果
class StaticElement : public Element{
public:
	int width;//宽度
	int height;//高度
	//返回x,y是否包含在元素内
	bool check(int x, int y) {
		if (Element::x <= x && x - Element::x <= width && Element::y <= y && y - Element::y <= height)
			return true;
		else 
			return false;
	}
};