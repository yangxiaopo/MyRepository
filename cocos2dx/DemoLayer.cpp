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
	GCGameLayer::onEnter();	//���һ���������ˣ������޷���Ӧ�¼�

	setTouchEnabled(true);	//�������Layer���ܴ�������꣩�¼�

	//��ӱ���ͼ����ʾ����ͼƬ��ʾ����,��Դ��Ĭ��ָ����ResourcesĿ¼����ע��ֱ��ʹ��ͼƬ��Դ�����ĵ���CCImageSprite
	GCImageSprite *pSpriteBG = GCImageSprite::spriteWithFile("bg.jpg",this);//������������new CCSprite���󣬴󲿷����־�̬��������������˵�
	pSpriteBG->setPositionInPixels(ccp(1016/2,703/2));	//���򴰿�����ԭ�㣨0,0��λ�����½ǣ���������������õ���ͼƬ���ĵ�λ��
	addChild(pSpriteBG);	//ע��addChild�����е���ʾ���󶼱��뱻���������addChild��Żᱻ��ʾ�������Ӷ����onEnter�ᱻ����
	
	//��Ӱ�ť,����ֻ��ʾ��ͼƬ��ӣ�pList��Ӧ��SpriteFrameģʽ����Լ�����
	m_pBtnTest = GCButton::buttonWithFile("score-1-1.png","score-1-2.png","score-1-3.png",this,menu_selector(DemoLayer::OnBtnTest));	//������(Ĭ��ͼƬ�����ͼƬ������ͼƬ�������󣬵����ť�ص�����)
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