#include "MySprite.h"

static const int g_iActFrameNumArray[7][5] = {{9,3,21,7,4},
											  {6,3,15,7,16},
											  {5,4,5,5,6},
											  {12,4,14,5,5},
											  {4,8,4,7,15},
											  {6,8,6,9,3},
											  {6,8,8,6,7}};

MySprite::MySprite(int num,int x,int y)
	:m_iTimes(0),m_bHappy(false),m_bCrazy(false),m_iState(0),m_iFrame(0)
{
	m_iNum = num;

	char szName[32];
	sprintf(szName,"%d-%d-%d.png",num,m_iState,m_iFrame);
	CCSprite *sprite = CCSprite::spriteWithSpriteFrameName(szName);
	sprite->setPositionInPixels(ccp(x,y));
	m_pSprite = sprite;
}

MySprite::~MySprite()
{
	m_pSprite->release();
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
	m_iState = 0;
	m_iFrame = 0;
}

void MySprite::Continue()
{
	char szName[32];
	sprintf(szName,"%d-%d-%d.png",m_iNum,m_iState,m_iFrame);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//取得对应需要显示的SpriteFrame，
	m_pSprite->setDisplayFrame(pFrame);	//设置显示对应帧

	m_iFrame++;	//继续下帧

	switch (m_iNum)
	{
	case 1:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 2:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 3:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 4:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 5:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 6:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	case 7:
	{
		if(m_iFrame >= g_iActFrameNumArray[m_iNum - 1][m_iState])	//同个动作帧数放完了
		{
			if(m_bCrazy)
			{
				++m_iTimes;
				if(m_iTimes >= 3)
				{
					m_bCrazy = false;
					m_iFrame = 0;	//帧数归0
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
					m_iFrame = 0;	//帧数归0
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
				m_iFrame = 0;	//帧数归0
				m_iState = (rand() % 3);
			}
		}
		break;
	}
	default:
		break;
	}
}

CCSprite *MySprite::GetSprite()
{
	return m_pSprite;
}