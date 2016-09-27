#include "DemoLayer.h"

static int g_ia = 0;
static int g_ib = 0;
static int g_ic = 0;
static int g_id = 0;
//初始化玩家5个动作的帧数，5个动作分别是(普通1，普通2，普通3，失利，胜利)
const int g_iActFrameNum1[5] = {9,3,21,7,4};
const int g_iActFrameNum2[5] = {6,3,15,7,16};
const int g_iActFrameNum3[5] = {5,4,5,5,6};
const int g_iActFrameNum4[5] = {12,4,14,5,5};
const int g_iActFrameNum5[5] = {4,8,4,7,15};
const int g_iActFrameNum6[5] = {6,8,6,9,3};
const int g_iActFrameNum7[5] = {6,8,8,6,7};

static bool suprise1 = false;
static bool suprise2 = false;
static bool suprise3 = false;
static bool suprise4 = false;
static bool happy1 = false;
static bool happy2 = false;
static bool happy3 = false;
static bool happy4 = false;
static int times1 = 0;
static int times2 = 0;
static int times3 = 0;
static int times4 = 0;

static bool exchange = false;

DemoLayer::DemoLayer()
{
	
}

DemoLayer::~DemoLayer()
{
	
}

void DemoLayer::myrandom()
{
	int arr[8];
	int i;
	for(i = 0;i < 8;i++)
	{
		arr[i] = i;
	}

	int temp = 7;
	while(temp > 3)
	{
		int j = ((rand() % temp) + 1);
		int k = arr[j];
		arr[j] = arr[temp];
		arr[temp]=k;
		temp--;
	}
	g_ia = arr[++temp];
	g_ib = arr[++temp];
	g_ic = arr[++temp];
	g_id = arr[++temp];
}

void DemoLayer::onEnter()
{
	GCGameLayer::onEnter();	//这句一定不能忘了，否则无法响应事件
	
	scheduleUpdate();			//启用每帧update调用

	setTouchEnabled(true);	//允许这个Layer接受触摸（鼠标）事件

	//添加背景图（演示单张图片显示方法,资源都默认指定在Resources目录），注意直接使用图片资源创建的得是CCImageSprite
	GCImageSprite *pSpriteBG = GCImageSprite::spriteWithFile("bg.jpg",this);//这个方法里面会new CCSprite对象，大部分这种静态创建函数都是如此的
	pSpriteBG->setPositionInPixels(ccp(1016/2,703/2));	//程序窗口坐标原点（0,0）位于左下角，并且这个函数设置的是图片中心点位置
	addChild(pSpriteBG);	//注意addChild，所有的显示对象都必须被父对象调用addChild后才会被显示，并且子对象的onEnter会被触发
	
	//添加按钮,这里只演示单图片添加，pList对应的SpriteFrame模式添加自己尝试
	m_pBtnTest = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest));	//参数：(默认图片，点击图片，禁用图片，父对象，点击按钮回调函数)
	m_pBtnTest->setPositionInPixels(ccp(300,703/2));
	addChild(m_pBtnTest);
	m_pBtnTest2 = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest2));	//参数：(默认图片，点击图片，禁用图片，父对象，点击按钮回调函数)
	m_pBtnTest2->setPositionInPixels(ccp(500,703/2));
	addChild(m_pBtnTest2);
	m_pBtnTest3 = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest3));	//参数：(默认图片，点击图片，禁用图片，父对象，点击按钮回调函数)
	m_pBtnTest3->setPositionInPixels(ccp(700,703/2));
	addChild(m_pBtnTest3);

	//添加人物资源（pList）(这是IOS下一个拼图工具把多张png图片组合成一张图片，并且在plist文件里说明里面单张图片的信息，
	//可以看到资源有player-0.plist和player-0.png，前者就是说明后者原始单图的XML信息(单图名，尺寸，在拼图中的位置)，可以用文本编辑器打开plist看下就明白了)
	AddPlist("player-1.plist");//添加plist进缓存
	AddPlist("player-2.plist");
	AddPlist("player-3.plist");
	AddPlist("player-4.plist");
	AddPlist("player-5.plist");
	AddPlist("player-6.plist");
	AddPlist("player-7.plist");
	
	myrandom();

	char szName[32];
	sprintf(szName,"%d-0-0.png",g_ia);
	//添加可动的人物头像
	m_pSpriteHeadAni1 = CCSprite::spriteWithSpriteFrameName(szName);//直接根据单图对象帧名创建Sprite，里面其实就是执行了同上的两行
	m_pSpriteHeadAni1->setPositionInPixels(ccp(900,400));
	//m_pSpriteHeadAni->setDisplayFrame();
	addChild(m_pSpriteHeadAni1);

	sprintf(szName,"%d-0-0.png",g_ib);
	m_pSpriteHeadAni2 = CCSprite::spriteWithSpriteFrameName(szName);//直接根据单图对象帧名创建Sprite，里面其实就是执行了同上的两行
	m_pSpriteHeadAni2->setPositionInPixels(ccp(500,600));
	addChild(m_pSpriteHeadAni2);

	sprintf(szName,"%d-0-0.png",g_ic);
	m_pSpriteHeadAni3 = CCSprite::spriteWithSpriteFrameName(szName);//直接根据单图对象帧名创建Sprite，里面其实就是执行了同上的两行
	m_pSpriteHeadAni3->setPositionInPixels(ccp(100,400));
	addChild(m_pSpriteHeadAni3);

	sprintf(szName,"%d-0-0.png",g_id);
	m_pSpriteHeadAni4 = CCSprite::spriteWithSpriteFrameName(szName);//直接根据单图对象帧名创建Sprite，里面其实就是执行了同上的两行
	m_pSpriteHeadAni4->setPositionInPixels(ccp(500,200));
	addChild(m_pSpriteHeadAni4);
}



void DemoLayer::onExit()
{
	GCGameLayer::onExit();
}

void DemoLayer::update(float dt)
{
	static int iFrameIndex1 = 0;
	static int iActTypeIndex1 = 0;

	static int iFrameIndex2 = 0;
	static int iActTypeIndex2 = 0;

	static int iFrameIndex3 = 0;
	static int iActTypeIndex3 = 0;

	static int iFrameIndex4 = 0;
	static int iActTypeIndex4 = 0;

	if(suprise1 && suprise2 && suprise3 && suprise4)
	{
		if(times1 == 0 && times2 ==0 && times3 == 0 && times4 == 0)
		{
			++times1;
			++times2;
			++times3;
			++times4;

			iFrameIndex1 = 0;
			iActTypeIndex1 = 3;

			iFrameIndex2 = 0;
			iActTypeIndex2 = 3;

			iFrameIndex3 = 0;
			iActTypeIndex3 = 3;

			iFrameIndex4 = 0;
			iActTypeIndex4 = 3;
		}
	}
	else if(happy1 && happy2 && happy3 && happy4)
	{
		if(times1 == 0 && times2 == 0 && times3 == 0 && times4 == 0)
		{
			++times1;
			++times2;
			++times3;
			++times4;

			iFrameIndex1 = 0;
			iActTypeIndex1 = 4;

			iFrameIndex2 = 0;
			iActTypeIndex2 = 4;

			iFrameIndex3 = 0;
			iActTypeIndex3 = 4;

			iFrameIndex4 = 0;
			iActTypeIndex4 = 4;
		}
	}
	else if(exchange)
	{
		myrandom();

		iFrameIndex1 = 0;
		iActTypeIndex1 = 0;
		
		iFrameIndex2 = 0;
		iActTypeIndex2 = 0;

		iFrameIndex3 = 0;
		iActTypeIndex3 = 0;

		iFrameIndex4 = 0;
		iActTypeIndex4 = 0;

		exchange = false;
	}

	static unsigned int lastTime = 0;
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	unsigned int nowTime = now.tv_sec*1000+now.tv_usec/1000;
	if(nowTime - lastTime >= 500)	//间隔500MS进入一次
	{
		lastTime = nowTime;//我有4个myupdate 每一次进入4个都更新
		myupdate(m_pSpriteHeadAni1,g_ia,iActTypeIndex1,iFrameIndex1,times1,happy1,suprise1);
		myupdate(m_pSpriteHeadAni2,g_ib,iActTypeIndex2,iFrameIndex2,times2,happy2,suprise2);
		myupdate(m_pSpriteHeadAni3,g_ic,iActTypeIndex3,iFrameIndex3,times3,happy3,suprise3);
		myupdate(m_pSpriteHeadAni4,g_id,iActTypeIndex4,iFrameIndex4,times4,happy4,suprise4);
	}
}

void DemoLayer::myupdate(CCSprite *s,int n,int &iActTypeIndex,int &iFrameIndex,int &times,bool &happy,bool &suprise)
{
	char szName[32];
	sprintf(szName,"%d-%d-%d.png",n,iActTypeIndex,iFrameIndex);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//取得对应需要显示的SpriteFrame，
	s->setDisplayFrame(pFrame);	//设置显示对应帧

	iFrameIndex++;	//继续下帧

	switch (n)
	{
	case 1:
	{
		if(iFrameIndex >= g_iActFrameNum1[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 2:
	{
		if(iFrameIndex >= g_iActFrameNum2[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 3:
	{
		if(iFrameIndex >= g_iActFrameNum3[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 4:
	{
		if(iFrameIndex >= g_iActFrameNum4[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 5:
	{
		if(iFrameIndex >= g_iActFrameNum5[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 6:
	{
		if(iFrameIndex >= g_iActFrameNum6[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 7:
	{
		if(iFrameIndex >= g_iActFrameNum7[iActTypeIndex])	//同个动作帧数放完了
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 3;
				}
			}
			else if(happy)
			{
				++times;
				if(times > 3)
				{
					happy = false;
					iFrameIndex = 0;	//帧数归0
					iActTypeIndex = (rand() % 3);
				}
				else
				{
					iFrameIndex = 0;
					iActTypeIndex = 4;
				}
			}
			else
			{
				iFrameIndex = 0;	//帧数归0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	default:
		break;
	}
}

void DemoLayer::OnBtnTest(CCObject *pBtn)
{
	suprise1 = true;
	suprise2 = true;
	suprise3 = true;
	suprise4 = true;
	times1 = 0;
	times2 = 0;
	times3 = 0;
	times4 = 0;
}
void DemoLayer::OnBtnTest2(CCObject *pBtn)
{
	happy1 = true;
	happy2 = true;
	happy3 = true;
	happy4 = true;
	times1 = 0;
	times2 = 0;
	times3 = 0;
	times4 = 0;
}
void DemoLayer::OnBtnTest3(CCObject *pBtn)
{
	exchange = true;
}