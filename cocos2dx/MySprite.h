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
	CCSprite *m_pSprite;      //精灵指针
	int m_iNum;               //几号人物
	int m_iState;             //什么状态
	int m_iFrame;             //帧数
	bool m_bCrazy;            //是否抓狂
	bool m_bHappy;            //是否开心
	int m_iTimes;             //循环次数
};

#endif MY_SPRITE_H