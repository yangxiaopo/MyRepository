/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    // a selector callback
    void menuCloseCallback(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void updateCamera(float fDelta);
private:
	HelloWorld();
	void applyCurSkin();
	void menuCallback_reSkin(Ref* sender);

	/** Define the all cameras, which in Scene3DTest, render order. */
	enum GAME_CAMERAS_ORDER {
		CAMERA_WORLD_3D_SKYBOX = 0,
		CAMERA_WORLD_3D_SCENE,
		CAMERA_UI_2D,
		CAMERA_DIALOG_2D_BASE,
		CAMERA_DIALOG_3D_MODEL,
		CAMERA_DIALOG_2D_ABOVE,
		CAMERA_OSD_2D_BASE,
		CAMERA_OSD_3D_MODEL,
		CAMERA_OSD_2D_ABOVE,
		CAMERA_COUNT,
	};

	std::vector<Camera *> gameCameras;

	Sprite3D* orc;

	enum SkinType
	{
		HAIR = 0,
		GLASSES,
		FACE,
		UPPER_BODY,
		HAND,
		PANTS,
		SHOES,
		MAX_TYPE,
	};

	std::vector<std::string> skins[(int)SkinType::MAX_TYPE]; //all skins
	int                      curSkin[(int)SkinType::MAX_TYPE]; //current skin index
	Sprite3D* reskinGirl;
	Sprite3D* dragon;
	Sprite3D* archer;

	bool zoomOut;
	bool zoomIn;
	bool rotateLeft;
	bool rotateRight;
	bool onTouchesCamera(Touch* touch, Event* event, bool* toChange);
};

#endif // __HELLOWORLD_SCENE_H__
