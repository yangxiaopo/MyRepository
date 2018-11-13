#ifndef __CHAPTER_9_10_H__
#define __CHAPTER_9_10_H__

#include "cocos2d.h"

USING_NS_CC;

class Chapter9_10 : public Ref
{
public:
    static cocos2d::Scene* createScene();

	static void applyCurSkin(Sprite3D* player);
	static void menuCallback_reSkin(cocos2d::Ref* sender, Sprite3D* player);

	void Chapter9_10::updateCamera(float fDelta);
};

#endif // __CHAPTER_9_9_H__