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
	virtual void onEnter();				//被addChild，添加显示的时候触发，一般来说着个Layer用到的资源和事件都是在这里初始化和加载
	virtual void update(float dt);		//每帧都会触发的update函数

	CCSprite *m_pSprite;      //精灵指针
	int m_iNum;               //几号人物
	int m_iState;             //什么状态
	int m_iFrame;             //帧数
	bool m_bCrazy;            //是否抓狂
	bool m_bHappy;            //是否开心
	int m_iTimes;             //循环次数
	unsigned int m_uLastTime;  //记录上一次行动的时间
};

#endif MY_SPRITE_H