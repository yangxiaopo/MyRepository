#include "DemoLayer.h"

DemoLayer::DemoLayer()
{
	
}

DemoLayer::~DemoLayer()
{
	delete m_pSpriteHeadAni1;
	delete m_pSpriteHeadAni2;
	delete m_pSpriteHeadAni3;
	delete m_pSpriteHeadAni4;
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

	m_pSpriteHeadAni1 = new MySprite(arr[++temp],900,400);
	m_pSpriteHeadAni2 = new MySprite(arr[++temp],500,600);
	m_pSpriteHeadAni3 = new MySprite(arr[++temp],100,400);
	m_pSpriteHeadAni4 = new MySprite(arr[++temp],500,200);
	
	addChild(m_pSpriteHeadAni1->GetSprite());
	addChild(m_pSpriteHeadAni2->GetSprite());
	addChild(m_pSpriteHeadAni3->GetSprite());
	addChild(m_pSpriteHeadAni4->GetSprite());
	
}



void DemoLayer::onExit()
{
	GCGameLayer::onExit();
}

void DemoLayer::update(float dt)
{
	static unsigned int lastTime = 0;
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	unsigned int nowTime = now.tv_sec*1000+now.tv_usec/1000;
	if(nowTime - lastTime >= 500)	//间隔500MS进入一次
	{
		lastTime = nowTime;
		m_pSpriteHeadAni1->Continue();
		m_pSpriteHeadAni2->Continue();
		m_pSpriteHeadAni3->Continue();
		m_pSpriteHeadAni4->Continue();
	}
}

void DemoLayer::OnBtnTest(CCObject *pBtn)
{
	m_pSpriteHeadAni1->Crazy();
	m_pSpriteHeadAni2->Crazy();
	m_pSpriteHeadAni3->Crazy();
	m_pSpriteHeadAni4->Crazy();
}
void DemoLayer::OnBtnTest2(CCObject *pBtn)
{
	m_pSpriteHeadAni1->Happy();
	m_pSpriteHeadAni2->Happy();
	m_pSpriteHeadAni3->Happy();
	m_pSpriteHeadAni4->Happy();
}
void DemoLayer::OnBtnTest3(CCObject *pBtn)
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
	m_pSpriteHeadAni1->Toggle(arr[++temp]);
	m_pSpriteHeadAni2->Toggle(arr[++temp]);
	m_pSpriteHeadAni3->Toggle(arr[++temp]);
	m_pSpriteHeadAni4->Toggle(arr[++temp]);
}