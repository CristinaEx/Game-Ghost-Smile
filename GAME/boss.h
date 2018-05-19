#pragma once
#include "Element.h"

#define START_MODE 0xf000

class Boss : public Element {
public:
	int mode;//µ±Ç°×´Ì¬
	std::vector<HBITMAP> pic;//ÌùÍ¼
};