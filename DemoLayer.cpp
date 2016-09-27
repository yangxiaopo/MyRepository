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
	GCGameLayer::onEnter();	//���һ���������ˣ������޷���Ӧ�¼�
	
	scheduleUpdate();			//����ÿ֡update����

	setTouchEnabled(true);	//�������Layer���ܴ�������꣩�¼�

	//��ӱ���ͼ����ʾ����ͼƬ��ʾ����,��Դ��Ĭ��ָ����ResourcesĿ¼����ע��ֱ��ʹ��ͼƬ��Դ�����ĵ���CCImageSprite
	GCImageSprite *pSpriteBG = GCImageSprite::spriteWithFile("bg.jpg",this);//������������new CCSprite���󣬴󲿷����־�̬��������������˵�
	pSpriteBG->setPositionInPixels(ccp(1016/2,703/2));	//���򴰿�����ԭ�㣨0,0��λ�����½ǣ���������������õ���ͼƬ���ĵ�λ��
	addChild(pSpriteBG);	//ע��addChild�����е���ʾ���󶼱��뱻���������addChild��Żᱻ��ʾ�������Ӷ����onEnter�ᱻ����
	
	//��Ӱ�ť,����ֻ��ʾ��ͼƬ��ӣ�pList��Ӧ��SpriteFrameģʽ����Լ�����
	m_pBtnTest = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest));	//������(Ĭ��ͼƬ�����ͼƬ������ͼƬ�������󣬵����ť�ص�����)
	m_pBtnTest->setPositionInPixels(ccp(300,703/2));
	addChild(m_pBtnTest);
	m_pBtnTest2 = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest2));	//������(Ĭ��ͼƬ�����ͼƬ������ͼƬ�������󣬵����ť�ص�����)
	m_pBtnTest2->setPositionInPixels(ccp(500,703/2));
	addChild(m_pBtnTest2);
	m_pBtnTest3 = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest3));	//������(Ĭ��ͼƬ�����ͼƬ������ͼƬ�������󣬵����ť�ص�����)
	m_pBtnTest3->setPositionInPixels(ccp(700,703/2));
	addChild(m_pBtnTest3);

	//���������Դ��pList��(����IOS��һ��ƴͼ���߰Ѷ���pngͼƬ��ϳ�һ��ͼƬ��������plist�ļ���˵�����浥��ͼƬ����Ϣ��
	//���Կ�����Դ��player-0.plist��player-0.png��ǰ�߾���˵������ԭʼ��ͼ��XML��Ϣ(��ͼ�����ߴ磬��ƴͼ�е�λ��)���������ı��༭����plist���¾�������)
	AddPlist("player-1.plist");//���plist������
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
	if(nowTime - lastTime >= 500)	//���500MS����һ��
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