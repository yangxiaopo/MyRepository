#include "DemoLayer.h"

static void MyRandom(int *a,int *b,int *c,int *d)
{
	int arr[9];
	int i;
	for(i = 0;i < 9;i++)
	{
		arr[i] = i;
	}

	int temp = 8;
	while(temp > 4)
	{
		int j = ((rand() % temp) + 1);
		int k = arr[j];
		arr[j] = arr[temp];
		arr[temp]=k;
		temp--;
	}
	*a = arr[++temp];
	*b = arr[++temp];
	*c = arr[++temp];
	*d = arr[++temp];
}

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

	setTouchEnabled(true);	//允许这个Layer接受触摸（鼠标）事件

	//添加背景图（演示单张图片显示方法,资源都默认指定在Resources目录），注意直接使用图片资源创建的得是CCImageSprite
	GCImageSprite *pSpriteBG = GCImageSprite::spriteWithFile("bg.jpg",this);//这个方法里面会new CCSprite对象，大部分这种静态创建函数都是如此的
	pSpriteBG->setPositionInPixels(ccp(1016/2,703/2));	//程序窗口坐标原点（0,0）位于左下角，并且这个函数设置的是图片中心点位置
	addChild(pSpriteBG);	//注意addChild，所有的显示对象都必须被父对象调用addChild后才会被显示，并且子对象的onEnter会被触发
	
	//添加按钮,这里只演示单图片添加，pList对应的SpriteFrame模式添加自己尝试
	m_pBtnTest = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest));	//参数：(默认图片，点击图片，禁用图片，父对象，点击按钮回调函数)
	m_pBtnTest->setPositionInPixels(ccp(300,703/2));
	addChild(m_pBtnTest);
	m_pBtnTest2 = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest2));
	m_pBtnTest2->setPositionInPixels(ccp(500,703/2));
	addChild(m_pBtnTest2);
	m_pBtnTest3 = GCButton::buttonWithFile("modify_portrait_btn-0.png","modify_portrait_btn-1.png","modify_portrait_btn-0.png",this,menu_selector(DemoLayer::OnBtnTest3));
	m_pBtnTest3->setPositionInPixels(ccp(700,703/2));
	addChild(m_pBtnTest3);

	int a,b,c,d;
	MyRandom(&a,&b,&c,&d);

	m_pSpriteHeadAni1 = new MySprite(a,900,400);
	addChild(m_pSpriteHeadAni1);
	m_pSpriteHeadAni2 = new MySprite(b,500,600);
	addChild(m_pSpriteHeadAni2);
	m_pSpriteHeadAni3 = new MySprite(c,100,400);
	addChild(m_pSpriteHeadAni3);
	m_pSpriteHeadAni4 = new MySprite(d,500,200);
	addChild(m_pSpriteHeadAni4);	
}

void DemoLayer::onExit()
{
	GCGameLayer::onExit();
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
	int a,b,c,d;
	MyRandom(&a,&b,&c,&d);
	m_pSpriteHeadAni1->Toggle(a);
	m_pSpriteHeadAni2->Toggle(b);
	m_pSpriteHeadAni3->Toggle(c);
	m_pSpriteHeadAni4->Toggle(d);
}