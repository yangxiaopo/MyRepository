#include "DemoLayer.h"

static int g_ia = 0;
static int g_ib = 0;
static int g_ic = 0;
static int g_id = 0;
//��ʼ�����5��������֡����5�������ֱ���(��ͨ1����ͨ2����ͨ3��ʧ����ʤ��)
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
	
	myrandom();

	char szName[32];
	sprintf(szName,"%d-0-0.png",g_ia);
	//��ӿɶ�������ͷ��
	m_pSpriteHeadAni1 = CCSprite::spriteWithSpriteFrameName(szName);//ֱ�Ӹ��ݵ�ͼ����֡������Sprite��������ʵ����ִ����ͬ�ϵ�����
	m_pSpriteHeadAni1->setPositionInPixels(ccp(900,400));
	//m_pSpriteHeadAni->setDisplayFrame();
	addChild(m_pSpriteHeadAni1);

	sprintf(szName,"%d-0-0.png",g_ib);
	m_pSpriteHeadAni2 = CCSprite::spriteWithSpriteFrameName(szName);//ֱ�Ӹ��ݵ�ͼ����֡������Sprite��������ʵ����ִ����ͬ�ϵ�����
	m_pSpriteHeadAni2->setPositionInPixels(ccp(500,600));
	addChild(m_pSpriteHeadAni2);

	sprintf(szName,"%d-0-0.png",g_ic);
	m_pSpriteHeadAni3 = CCSprite::spriteWithSpriteFrameName(szName);//ֱ�Ӹ��ݵ�ͼ����֡������Sprite��������ʵ����ִ����ͬ�ϵ�����
	m_pSpriteHeadAni3->setPositionInPixels(ccp(100,400));
	addChild(m_pSpriteHeadAni3);

	sprintf(szName,"%d-0-0.png",g_id);
	m_pSpriteHeadAni4 = CCSprite::spriteWithSpriteFrameName(szName);//ֱ�Ӹ��ݵ�ͼ����֡������Sprite��������ʵ����ִ����ͬ�ϵ�����
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
	if(nowTime - lastTime >= 500)	//���500MS����һ��
	{
		lastTime = nowTime;//����4��myupdate ÿһ�ν���4��������
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
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//ȡ�ö�Ӧ��Ҫ��ʾ��SpriteFrame��
	s->setDisplayFrame(pFrame);	//������ʾ��Ӧ֡

	iFrameIndex++;	//������֡

	switch (n)
	{
	case 1:
	{
		if(iFrameIndex >= g_iActFrameNum1[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 2:
	{
		if(iFrameIndex >= g_iActFrameNum2[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 3:
	{
		if(iFrameIndex >= g_iActFrameNum3[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 4:
	{
		if(iFrameIndex >= g_iActFrameNum4[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 5:
	{
		if(iFrameIndex >= g_iActFrameNum5[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 6:
	{
		if(iFrameIndex >= g_iActFrameNum6[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
				iActTypeIndex = (rand() % 3);
			}
		}
		break;
	}
	case 7:
	{
		if(iFrameIndex >= g_iActFrameNum7[iActTypeIndex])	//ͬ������֡��������
		{
			if(suprise)
			{
				++times;
				if(times > 3)
				{
					suprise = false;
					iFrameIndex = 0;	//֡����0
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
					iFrameIndex = 0;	//֡����0
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
				iFrameIndex = 0;	//֡����0
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