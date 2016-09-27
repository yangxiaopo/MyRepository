#ifndef MY_SPRITE_H
#define MY_SPRITE_H

#include "GCCommon.h"
#include "cocos2d.h"
#include <stdlib.h>

USING_NS_CC;

class MySprite
{
public:
	MySprite(int,int,int);
	virtual ~MySprite();
	void Happy();
	void Crazy();
	void Toggle(int);
	void Continue();
	CCSprite *GetSprite();

private:
	CCSprite *m_pSprite;      //����ָ��
	int m_iNum;               //��������
	int m_iState;             //ʲô״̬
	int m_iFrame;             //֡��
	bool m_bCrazy;            //�Ƿ�ץ��
	bool m_bHappy;            //�Ƿ���
	int m_iTimes;             //ѭ������
};

#endif MY_SPRITE_H