#pragma once
#include <Windows.h>
#include <vector>
#include "player.h"
#include "GameMessageBox.h"

class Element {
public:
	virtual void run(Player &player, GameMessageBox &box) = 0;
	int x;//ºá×ø±ê
	int y;//×Ý×ø±ê
};