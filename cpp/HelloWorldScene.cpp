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

#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

HelloWorld::HelloWorld()
	: orc(nullptr)
	, reskinGirl(nullptr)
	, archer(nullptr)
	, dragon(nullptr)
	, zoomIn(false)
	, zoomOut(false)
	, rotateLeft(false)
	, rotateRight(false)
{
	memset(curSkin, 0, sizeof(curSkin));
	gameCameras.resize(CAMERA_COUNT);
}

Scene* HelloWorld::scene()
{
     return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = Director::getInstance()->getWinSize();

	/****************************
	*3D
	*****************************/

	auto camera = gameCameras[CAMERA_WORLD_3D_SCENE] = this->getDefaultCamera();
	camera->initPerspective(60, (GLfloat)winSize.width / winSize.height, 0.1f, 200.0f);
	camera->setPosition3D(Vec3(0.0, 100, 100));
	camera->lookAt(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));

	//terrain
	Terrain::DetailMap r("Terrain/dirt.jpg"), g("Terrain/Grass2.jpg"), b("Terrain/road.jpg"), a("Terrain/GreenSkin.jpg");
	Terrain::TerrainData data("Terrain/heightmap16.jpg", "Terrain/alphamap.png", r, g, b, a, Size(32, 32), 40.0f, 2);
	auto terrain = Terrain::create(data, Terrain::CrackFixedType::SKIRT);
	terrain->setMaxDetailMapAmount(4);
	terrain->setSkirtHeightRatio(3);
	//terrain->setLODDistance(64, 128, 192);
	this->addChild(terrain);

	//orc
	orc = Sprite3D::create("Sprite3D/orc.c3b");
	orc->setRotation3D(Vec3(0, 180, 0));
	orc->setPositionY(terrain->getHeight(orc->getPositionX(), orc->getPositionZ()));
	auto animation = Animation3D::create("Sprite3D/orc.c3b");
	if (animation)
	{
		auto animate = Animate3D::create(animation);
		animate->setSpeed(0.6f);
		orc->runAction(RepeatForever::create(animate));
	}

	auto handler = PUParticleSystem3D::create("Particle3D/scripts/blackHole.pu", "Particle3D/materials/pu_mediapack_01.material");
	handler->setScale(0.6f);
	handler->startParticleSystem();
	orc->getAttachNode("Bip001 L Hand")->addChild(handler);
	this->addChild(orc);

	//reskinGirl
	std::string fileName = "Sprite3D/ReskinGirl.c3b";
	reskinGirl = Sprite3D::create(fileName);
	reskinGirl->setPosition3D(orc->getPosition3D() + Vec3(-50, 0, 0));
	reskinGirl->setPositionY(terrain->getHeight(reskinGirl->getPositionX(), reskinGirl->getPositionZ()));
	auto animation2 = Animation3D::create(fileName);
	if (animation2)
	{
		auto animate = Animate3D::create(animation2);
		reskinGirl->runAction(RepeatForever::create(animate));
	}

	auto handler2 = PUParticleSystem3D::create("Particle3D/scripts/flameSystem.pu", "Particle3D/materials/pu_mediapack_01.material");
	handler2->setScale(0.5f);
	handler2->startParticleSystem();
	reskinGirl->getAttachNode("Bip01 R Finger1Nub")->addChild(handler2);
	this->addChild(reskinGirl);

	auto& body = skins[(int)SkinType::UPPER_BODY];
	body.push_back("Girl_UpperBody01");
	body.push_back("Girl_UpperBody02");

	auto& pants = skins[(int)SkinType::PANTS];
	pants.push_back("Girl_LowerBody01");
	pants.push_back("Girl_LowerBody02");

	auto& shoes = skins[(int)SkinType::SHOES];
	shoes.push_back("Girl_Shoes01");
	shoes.push_back("Girl_Shoes02");

	auto& hair = skins[(int)SkinType::HAIR];
	hair.push_back("Girl_Hair01");
	hair.push_back("Girl_Hair02");

	auto& face = skins[(int)SkinType::FACE];
	face.push_back("Girl_Face01");
	face.push_back("Girl_Face02");

	auto& hand = skins[(int)SkinType::HAND];
	hand.push_back("Girl_Hand01");
	hand.push_back("Girl_Hand02");

	auto& glasses = skins[(int)SkinType::GLASSES];
	glasses.push_back("");
	glasses.push_back("Girl_Glasses01");

	applyCurSkin();

	//dragon
	dragon = Sprite3D::create("Model/dragon/dragon.c3b");
	dragon->setPosition3D(orc->getPosition3D() + Vec3(50, 0, 0));
	dragon->setPositionY(terrain->getHeight(dragon->getPositionX(), dragon->getPositionZ()));
	auto animation3 = Animation3D::create("Model/dragon/dragon.c3b");
	if (animation3)
	{
		auto animate = Animate3D::create(animation3);
		animate->setSpeed(0.6f);
		dragon->runAction(RepeatForever::create(animate));
	}
	this->addChild(dragon);

	//archer
	archer = Sprite3D::create("model/archer/archer.c3b");
	archer->setPosition3D(orc->getPosition3D() + Vec3(25, 0, 0));
	archer->setPositionY(terrain->getHeight(archer->getPositionX(), archer->getPositionZ()));
	auto animation4 = Animation3D::create("model/archer/archer.c3b");
	if (animation4)
	{
		auto animate = Animate3D::create(animation4);
		animate->setSpeed(0.6f);
		archer->runAction(RepeatForever::create(animate));
	}
	this->addChild(archer);

	/****************************
	*2D
	*****************************/

	auto camera2D = Camera::create();
	camera2D->setCameraFlag(CameraFlag::USER2);
	this->addChild(camera2D);

	// add a label shows "Hello World"
	auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", TITLE_FONT_SIZE);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
	label->setCameraMask((unsigned short)CameraFlag::USER2);
	this->addChild(label, 1);

	//add switch weapon button
	static bool isAttach = false;
	auto label1 = LabelTTF::create("Attach", "fonts/arial.ttf", 13);
	static MenuItemLabel* item1 = nullptr;
	if (item1 == nullptr)
	{
		item1 = MenuItemLabel::create(label1);
	}

	item1->setCallback([&](cocos2d::Ref *sender) {
		if (!isAttach)
		{
			auto sp = Sprite3D::create("Sprite3D/axe.c3b");
			orc->getAttachNode("Bip001 R Hand")->addChild(sp);
			item1->setString("Detach");
		}
		else
		{
			orc->removeAttachNode("Bip001 R Hand");
			item1->setString("Attach");
		}
		isAttach = !isAttach;
	});
	auto itemSize = item1->getContentSize();
	item1->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height));

	auto menuSelect = CCMenu::create(item1, NULL);
	menuSelect->setPosition(Vec2(0, 0));
	menuSelect->setCameraMask((unsigned short)CameraFlag::USER2);
	this->addChild(menuSelect, 1);

	//add reskin button
	TTFConfig ttfConfig("fonts/arial.ttf", 13);
	auto label2 = Label::createWithTTF(ttfConfig, "Hair");
	auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::menuCallback_reSkin, this));
	auto label3 = Label::createWithTTF(ttfConfig, "Glasses");
	auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::menuCallback_reSkin, this));
	auto label4 = Label::createWithTTF(ttfConfig, "Coat");
	auto item4 = MenuItemLabel::create(label4, CC_CALLBACK_1(HelloWorld::menuCallback_reSkin, this));
	auto label5 = Label::createWithTTF(ttfConfig, "Pants");
	auto item5 = MenuItemLabel::create(label5, CC_CALLBACK_1(HelloWorld::menuCallback_reSkin, this));
	auto label6 = Label::createWithTTF(ttfConfig, "Shoes");
	auto item6 = MenuItemLabel::create(label6, CC_CALLBACK_1(HelloWorld::menuCallback_reSkin, this));
	item2->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 2));
	item3->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 3));
	item4->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 4));
	item5->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 5));
	item6->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 6));
	item2->setUserData((void*)SkinType::HAIR);
	item3->setUserData((void*)SkinType::GLASSES);
	item4->setUserData((void*)SkinType::UPPER_BODY);
	item5->setUserData((void*)SkinType::PANTS);
	item6->setUserData((void*)SkinType::SHOES);
	auto pMenu1 = Menu::create(item2, item3, item4, item5, item6, nullptr);
	pMenu1->setPosition(Vec2(0, 0));
	pMenu1->setCameraMask((unsigned short)CameraFlag::USER2);
	this->addChild(pMenu1, 10);

	//(zoom in & zoom out) button
	auto label7 = Label::createWithTTF(ttfConfig, "Zoom Out");
	auto item7 = MenuItemLabel::create(label7);
	auto label8 = Label::createWithTTF(ttfConfig, "Zoom In");
	auto item8 = MenuItemLabel::create(label8);
	//(rotate left & rotate right) button
	auto label9 = Label::createWithTTF(ttfConfig, "Rotate Left");
	auto item9 = MenuItemLabel::create(label9);
	auto label10 = Label::createWithTTF(ttfConfig, "Rotate Right");
	auto item10 = MenuItemLabel::create(label10);
	item7->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 7));
	item8->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 8));
	item9->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 9));
	item10->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 10));

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);
	listener2->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesCamera, this, &zoomOut);
	listener2->onTouchEnded = [this](Touch* touch, Event* event) {
		zoomOut = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, label7);

	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->setSwallowTouches(true);
	listener3->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesCamera, this, &zoomIn);
	listener3->onTouchEnded = [this](Touch* touch, Event* event) {
		zoomIn = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, label8);

	auto listener4 = EventListenerTouchOneByOne::create();
	listener4->setSwallowTouches(true);
	listener4->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesCamera, this, &rotateLeft);
	listener4->onTouchEnded = [this](Touch* touch, Event* event) {
		rotateLeft = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, label9);

	auto listener5 = EventListenerTouchOneByOne::create();
	listener5->setSwallowTouches(true);
	listener5->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesCamera, this, &rotateRight);
	listener5->onTouchEnded = [this](Touch* touch, Event* event) {
		rotateRight = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener5, label10);

	auto pMenu2 = Menu::create(item7, item8, item9, item10, nullptr);
	pMenu2->setPosition(Vec2(0, 0));
	pMenu2->setCameraMask((unsigned short)CameraFlag::USER2);
	this->addChild(pMenu2, 11);

	this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::updateCamera), 0.0f);

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));

    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
	menu->setCameraMask((unsigned short)CameraFlag::USER2);
    this->addChild(menu, 1);

	return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::applyCurSkin()
{
	for (ssize_t i = 0; i < reskinGirl->getMeshCount(); i++) {
		auto mesh = reskinGirl->getMeshByIndex(static_cast<int>(i));
		bool isVisible = false;
		for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
			if (mesh->getName() == skins[j].at(curSkin[j]))
			{
				isVisible = true;
				break;
			}
		}
		reskinGirl->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
	}
}

void HelloWorld::menuCallback_reSkin(Ref* sender)
{
	long index = (long)(((MenuItemLabel*)sender)->getUserData());
	if (index < (int)SkinType::MAX_TYPE)
	{
		curSkin[index] = (curSkin[index] + 1) % skins[index].size();
		applyCurSkin();
	}
}

bool HelloWorld::onTouchesCamera(Touch* touch, Event* event, bool* toChange)
{
	auto target = static_cast<Label*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		*toChange = true;
		return true;
	}
	return false;
}

void HelloWorld::updateCamera(float fDelta)
{
	auto camera = gameCameras[CAMERA_WORLD_3D_SCENE];
	//if (_sprite3D)
	{
		/*
		if (_cameraType == CameraType::ThirdPerson)
		{
		updateState(fDelta);
		if (isState(_curState, State_Move))
		{
		move3D(fDelta);
		if (isState(_curState, State_Rotate))
		{
		Vec3 curPos = _sprite3D->getPosition3D();
		Vec3 newFaceDir = _targetPos - curPos;
		newFaceDir.y = 0;
		newFaceDir.normalize();
		Vec3 up;
		_sprite3D->getNodeToWorldTransform().getUpVector(&up);
		up.normalize();
		Vec3 right;
		Vec3::cross(-newFaceDir, up, &right);
		right.normalize();
		Vec3 pos = Vec3(0, 0, 0);
		Mat4 mat;
		mat.m[0] = right.x;
		mat.m[1] = right.y;
		mat.m[2] = right.z;
		mat.m[3] = 0.0f;
		mat.m[4] = up.x;
		mat.m[5] = up.y;
		mat.m[6] = up.z;
		mat.m[7] = 0.0f;
		mat.m[8] = newFaceDir.x;
		mat.m[9] = newFaceDir.y;
		mat.m[10] = newFaceDir.z;
		mat.m[11] = 0.0f;
		mat.m[12] = pos.x;
		mat.m[13] = pos.y;
		mat.m[14] = pos.z;
		mat.m[15] = 1.0f;
		_sprite3D->setAdditionalTransform(&mat);
		}
		}
		}*/
		if (zoomOut == true)
		{
			if (camera)
			{
				/*
				if (_cameraType == CameraType::ThirdPerson)
				{
				Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
				Vec3 cameraPos = _camera->getPosition3D();
				if (lookDir.length() <= 300)
				{
				cameraPos += lookDir.getNormalized();
				_camera->setPosition3D(cameraPos);
				}
				}
				else if (_cameraType == CameraType::Free)*/
				{
					Vec3 cameraPos = camera->getPosition3D();
					if (cameraPos.length() <= 300)
					{
						cameraPos += cameraPos.getNormalized();
						camera->setPosition3D(cameraPos);
					}
				}
			}
		}
		else if (zoomIn == true)
		{
			if (camera)
			{
				/*
				if (_cameraType == CameraType::ThirdPerson)
				{
				Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
				Vec3 cameraPos = _camera->getPosition3D();
				if (lookDir.length() >= 50)
				{
				cameraPos -= lookDir.getNormalized();
				_camera->setPosition3D(cameraPos);
				}
				}
				else if (_cameraType == CameraType::Free)*/
				{
					Vec3 cameraPos = camera->getPosition3D();
					if (cameraPos.length() >= 50)
					{
						cameraPos -= cameraPos.getNormalized();
						camera->setPosition3D(cameraPos);
					}
				}
			}
		}
		else if (rotateLeft == true)
		{
			//if (_cameraType == CameraType::Free || _cameraType == CameraType::FirstPerson)
			{
				Vec3  rotation3D = camera->getRotation3D();
				rotation3D.y += 1;
				camera->setRotation3D(rotation3D);
			}
		}
		else if (rotateRight == true)
		{
			//if (_cameraType == CameraType::Free || _cameraType == CameraType::FirstPerson)
			{
				Vec3  rotation3D = camera->getRotation3D();
				rotation3D.y -= 1;
				camera->setRotation3D(rotation3D);
			}
		}
	}
}