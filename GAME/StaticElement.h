#pragma once
#include<windows.h>


//��Ϸ�ھ�̬Ԫ��ֻӵ����ͼ������ֻ��С��һ����λ����ʱ�Żᴥ��Ч��
class StaticElement {
public:
	HBITMAP pic;//��ͼ
	virtual void affect() = 0;//����Ч��
};