#pragma once
#include "GameMessageBox.h"
#include "player.h"

class Element {
public:
	virtual void run(Player &player, GameMessageBox &box) = 0;
	int x;//ºá×ø±ê
	int y;//×Ý×ø±ê
};