#pragma once
#include<windows.h>
#include"Element.h"

//��Ϸ�ھ�̬Ԫ�ؿ��Բ�ӵ����ͼֻ��С��һ����λ����ʱ�Żᴥ��Ч��
class StaticElement : public Element{
public:
	int width;//���
	int height;//�߶�
	//����x,y�Ƿ������Ԫ����
	bool check(int x, int y) {
		if (Element::x <= x && x - Element::x <= width && Element::y <= y && y - Element::y <= height)
			return true;
		else 
			return false;
	}
};