#pragma once
#include "Element.h"

#define START_MODE 0xf000

class Boss : public Element {
public:
	int mode;//��ǰ״̬
	std::vector<HBITMAP> pic;//��ͼ
};