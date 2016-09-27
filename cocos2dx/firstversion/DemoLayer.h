#ifndef DEMO_LAYER_H
#define DEMO_LAYER_H

#include "GCCommon.h"

#include "cocos2d.h"

#include <stdlib.h>
USING_NS_CC;

/*
GCGameLayer���Լ����Ϊһ��͸������ʾ�㣬���ҿ��Խ��ܴ�������꣬���̣��������豸�¼���
һ����˵��Ϸ��������һ�����и���Layer�������д�����Ϸ�����߼���
��Ϸ�ж�������ʾ���ڣ�����������Ҳ��������Layer������Ҫ��ʾ��ʱ��,addChild����Layer���ɡ�
����������С����ʾ��λ��CCSprite��һ����˵���Ƕ�ϰ��������ŵ���ͼƬ������ʾ��
*/
class DemoLayer :public GCGameLayer
{   
public:
    DemoLayer();
    virtual ~DemoLayer();

private:
	virtual void onEnter();				//��addChild�������ʾ��ʱ�򴥷���һ����˵�Ÿ�Layer�õ�����Դ���¼������������ʼ���ͼ���
	virtual void onExit();				//��removeChild��ɾ����ʾ��ʱ�򴥷���һ����˵�Ÿ�Layer�õ�����Դ���¼���������������
		
	virtual void update(float dt);		//ÿ֡���ᴥ����update����
	void myupdate(CCSprite *,int,int&,int&,int&,bool&,bool&);
	void myrandom();

	GCButton *m_pBtnTest;				//���԰�ť
	GCButton *m_pBtnTest2;
	GCButton *m_pBtnTest3;
	void OnBtnTest(CCObject *pBtn);		//��ť��Ӧ����(����)
	void OnBtnTest2(CCObject *pBtn);    ////��ť��Ӧ����(����)
	void OnBtnTest3(CCObject *pBtn);    //�޸�ȫ��ͷ����

	CCSprite *m_pSpriteHeadAni1;			//�ɶ�������ͷ��
	CCSprite *m_pSpriteHeadAni2;
	CCSprite *m_pSpriteHeadAni3;
	CCSprite *m_pSpriteHeadAni4;
};


#endif
