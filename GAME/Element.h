#pragma once
#include <Windows.h>
#include <vector>
#include "player.h"

class Element {
public:
	virtual void run(Player &player) = 0;
	int x;//ºá×ø±ê
	int y;//×Ý×ø±ê
};