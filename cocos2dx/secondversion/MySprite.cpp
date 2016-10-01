#include "MySprite.h"

static const int g_iActFrameNumArray[][5] = {{9,3,21,7,4},
											 {6,3,15,7,16},
											 {5,4,5,5,6},
											 {12,4,14,5,5},
											 {4,8,4,7,15},
											 {6,8,6,9,3},
											 {6,8,8,6,7},
											 {4,4,5,7,5},};

vector<int> *m_plist = new vector<int>(8);      //��¼�Ѽ���plist

MySprite::MySprite(int num,int x,int y)
	:m_iTimes(0),m_bHappy(false),m_bCrazy(false),m_iState(0),m_iFrame(0),m_uLastTime(0)
{
	
	m_iNum = num;
	char szName[32];
	if(find(m_plist->begin(),m_plist->end(),m_iNum) == m_plist->end())//.plist������û��
	{
		m_plist->push_back(m_iNum);
		sprintf(szName,"player-%d.plist",m_iNum);
		AddPlist(szName);
	}
	sprintf(szName,"%d-%d-%d.png",num,m_iState,m_iFrame);
	CCSprite *sprite = CCSprite::spriteWithSpriteFrameName(szName);
	sprite->setPositionInPixels(ccp(x,y));
	m_pSprite = sprite;
	addChild(m_pSprite);
}

MySprite::~MySprite()
{
	
}

void MySprite::Happy()
{
	m_bHappy = true;
	m_iTimes = 0;
	m_iState = 4;
	m_iFrame = 0;
}

void MySprite::Crazy()
{
	m_bCrazy = true;
	m_iTimes = 0;
	m_iState = 3;
	m_iFrame = 0;
}

void MySprite::Toggle(int newNum)
{
	m_iNum = newNum;
	char szName[32];
	if(find(m_plist->begin(),m_plist->end(),m_iNum) == m_plist->end())//.plist������û��
	{
		m_plist->push_back(m_iNum);
		sprintf(szName,"player-%d.plist",m_iNum);
		AddPlist(szName);
	}
	m_iState = 0;
	m_iFrame = 0;
}

void MySprite::Continue()
{
	char szName[32];
	sprintf(szName,"%d-%d-%d.png",m_iNum,m_iState,m_iFrame);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//ȡ�ö�Ӧ��Ҫ��ʾ��SpriteFrame��
	m_pSprite->setDisplayFrame(pFrame);	//������ʾ��Ӧ֡

	m_iFrame++;	//������֡

	if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//ͬ������֡��������
	{
		if(m_bCrazy)
		{
			++m_iTimes;
			if(m_iTimes >= 3)
			{
				m_bCrazy = false;
				m_iFrame = 0;	//֡����0
				m_iState = (rand() % 3);
			}
			else
			{
				m_iFrame = 0;
				m_iState = 3;
			}
		}
		else if(m_bHappy)
		{
			++m_iTimes;
			if(m_iTimes >= 3)
			{
				m_bHappy = false;
				m_iFrame = 0;	//֡����0
				m_iState = (rand() % 3);
			}
			else
			{
				m_iFrame = 0;
				m_iState = 4;
			}
		}
		else
		{
			m_iFrame = 0;	//֡����0
			m_iState = (rand() % 3);
		}
	}
}

void MySprite::update(float dt)
{
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	unsigned int nowTime = now.tv_sec*1000+now.tv_usec/1000;
	if(nowTime - m_uLastTime >= 500)	//���500MS����һ��
	{
		m_uLastTime = nowTime;
		Continue();
	}
}

void MySprite::onEnter()
{
	GCGameLayer::onEnter();	//���һ���������ˣ������޷���Ӧ�¼�
	scheduleUpdate();			//����ÿ֡update����
}