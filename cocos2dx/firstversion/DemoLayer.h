#ifndef DEMO_LAYER_H
#define DEMO_LAYER_H

#include "GCCommon.h"

#include "cocos2d.h"

#include <stdlib.h>
USING_NS_CC;

/*
GCGameLayer可以简单理解为一个透明的显示层，并且可以接受触摸（鼠标，键盘）等输入设备事件，
一般来说游戏单场景里一定会有个主Layer，在其中处理游戏的主逻辑。
游戏中独立的显示窗口，比如结算框，则也可以做成Layer，在需要显示的时候,addChild到主Layer即可。
而引擎中最小的显示单位是CCSprite，一般来说我们都习惯往里面放单张图片用于显示。
*/
class DemoLayer :public GCGameLayer
{   
public:
    DemoLayer();
    virtual ~DemoLayer();

private:
	virtual void onEnter();				//被addChild，添加显示的时候触发，一般来说着个Layer用到的资源和事件都是在这里初始化和加载
	virtual void onExit();				//被removeChild，删除显示的时候触发，一般来说着个Layer用到的资源和事件都是在这里销毁
		
	virtual void update(float dt);		//每帧都会触发的update函数
	void myupdate(CCSprite *,int,int&,int&,int&,bool&,bool&);
	void myrandom();

	GCButton *m_pBtnTest;				//测试按钮
	GCButton *m_pBtnTest2;
	GCButton *m_pBtnTest3;
	void OnBtnTest(CCObject *pBtn);		//按钮响应函数(惊讶)
	void OnBtnTest2(CCObject *pBtn);    ////按钮响应函数(高兴)
	void OnBtnTest3(CCObject *pBtn);    //修改全部头像函数

	CCSprite *m_pSpriteHeadAni1;			//可动的人物头像
	CCSprite *m_pSpriteHeadAni2;
	CCSprite *m_pSpriteHeadAni3;
	CCSprite *m_pSpriteHeadAni4;
};


#endif
