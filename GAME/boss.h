#pragma once
#include "Element.h"

#define START_MODE 0

class Boss : public Element {
public:
	int mode;//��ǰ״̬
	std::vector<HBITMAP> pic;//��ͼ
};