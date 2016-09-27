#ifndef MY_SPRITE_H
#define MY_SPRITE_H

#include "GCCommon.h"
#include "cocos2d.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>

USING_NS_CC;

class MySprite :public GCGameLayer
{
public:
	MySprite(int,int,int);
	virtual ~MySprite();
	void Happy();
	void Crazy();
	void Toggle(int);
	void Continue();

private:
	virtual void onEnter();				//��addChild�������ʾ��ʱ�򴥷���һ����˵�Ÿ�Layer�õ�����Դ���¼������������ʼ���ͼ���
	virtual void update(float dt);		//ÿ֡���ᴥ����update����

	CCSprite *m_pSprite;      //����ָ��
	int m_iNum;               //��������
	int m_iState;             //ʲô״̬
	int m_iFrame;             //֡��
	bool m_bCrazy;            //�Ƿ�ץ��
	bool m_bHappy;            //�Ƿ���
	int m_iTimes;             //ѭ������
	unsigned int m_uLastTime;  //��¼��һ���ж���ʱ��
};

#endif MY_SPRITE_H