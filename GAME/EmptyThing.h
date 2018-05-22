#pragma once
#include "ThingOfBag.h"

class EmptyThing : public ThingOfBag {
public:
	EmptyThing() {
		count = 0;
	}
	void paint(HWND &hwnd, int x, int y){}
	void use(int &effect_data, GameMessageBox &box) {
		count--;
	}
};