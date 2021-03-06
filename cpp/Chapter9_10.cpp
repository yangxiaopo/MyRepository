#include "Chapter9_10.h"
#include "Chapter9.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <functional>

USING_NS_CC;

enum class SkinType
{
	UPPER_BODY = 0,
	PANTS,
	SHOES,
	HAIR,
	FACE,
	HAND,
	GLASSES,
	MAX_TYPE,
};

static std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
static int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index

//TODO
static bool zoomOutPressed = false;
static bool zoomInPressed = false;
static bool test1 = false;
static bool test2 = false;

cocos2d::Camera*      camera = nullptr;

Scene* Chapter9_10::createScene()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a scene
    // 'scene' is an autorelease object
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto scene = Scene::create();

	/************************************
	*3D
	*************************************/
	camera = scene->getDefaultCamera();
	camera->initPerspective(60, (GLfloat)winSize.width / winSize.height, 0.1f, 200.0f);
	camera->setPosition3D(Vec3(0.0, 100, 100));
	camera->lookAt(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));

	Terrain::DetailMap r("chapter9/dirt.jpg"), g("chapter9/Grass2.jpg"), b("chapter9/road.jpg"), a("chapter9/GreenSkin.jpg");
	Terrain::TerrainData data("chapter9/heightmap16.jpg", "chapter9/alphamap.png", r, g, b, a, Size(32, 32), 40.0f, 2);
    auto terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
	terrain->setMaxDetailMapAmount(4);
	terrain->setSkirtHeightRatio(3);
	//terrain->setLODDistance(64, 128, 192);
	scene->addChild(terrain);

	static Sprite3D* player = nullptr;
    if(player == nullptr)
		player = Sprite3D::create("chapter9/orc.c3b");
	player->setRotation3D(Vec3(0, 180, 0));
    player->setPositionY(terrain->getHeight(player->getPositionX(),player->getPositionZ()));
    auto animation = Animation3D::create("chapter9/orc.c3b");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
		animate->setSpeed(0.6f);
        player->runAction(RepeatForever::create(animate));
    }

	auto handler = PUParticleSystem3D::create("blackHole.pu", "pu_mediapack_01.material");
	handler->setScale(0.03f);
	handler->startParticleSystem();
	AttachNode* node = player->getAttachNode("Bip001 L Hand");

	node->addChild(handler);

	//auto _cameraFirst = Camera::createPerspective(30, (GLfloat)winSize.width / winSize.height, 10, 200);
	//camera->setCameraFlag(CameraFlag::USER2);
	//_cameraFirst->setCameraFlag(CameraFlag::DEFAULT);
	scene->removeChild(camera);
	auto bone = player->getSkeleton()->getBoneByName("Bip001 Head");
	Mat4 mat = player->getNodeToWorldTransform() * bone->getWorldMat();
	//player->getAttachNode("Bip001 Head")->addChild(camera);//1
	//camera->setNodeToParentTransform(mat);//1
	Vec3 scale, translation;//2
	Quaternion rotation;
	mat.decompose(&scale, &rotation, &translation);
	camera->setScaleX(scale.x);
	camera->setScaleY(scale.y);
	camera->setScaleZ(scale.z);
	camera->setPosition3D(translation);
	camera->setRotationQuat(rotation);//it's also OK
	player->getAttachNode("Bip001 Head")->addChild(camera);

	//auto bone = player->getSkeleton()->getBoneByName("Bip001 L Hand");
	//Mat4 mat = player->getNodeToWorldTransform() * bone->getWorldMat();
	scene->addChild(player);

	static Sprite3D* monster = Sprite3D::create("chapter9/ReskinGirl.c3b");
	monster->setPosition3D(player->getPosition3D() + Vec3(-50, 0, 0));
	monster->setPositionY(terrain->getHeight(monster->getPositionX(), monster->getPositionZ()));
	auto animation2 = Animation3D::create("chapter9/ReskinGirl.c3b");
	if (animation2)
	{
		auto animate = Animate3D::create(animation2);
		monster->runAction(RepeatForever::create(animate));
	}

	auto handler2 = PUParticleSystem3D::create("flameSystem.pu", "pu_mediapack_01.material");
	handler2->setScale(0.5f);
	handler2->startParticleSystem();
	monster->getAttachNode("Bip01 R Finger1Nub")->addChild(handler2);

	scene->addChild(monster);

	auto& body = _skins[(int)SkinType::UPPER_BODY];
	body.push_back("Girl_UpperBody01");
	body.push_back("Girl_UpperBody02");

	auto& pants = _skins[(int)SkinType::PANTS];
	pants.push_back("Girl_LowerBody01");
	pants.push_back("Girl_LowerBody02");

	auto& shoes = _skins[(int)SkinType::SHOES];
	shoes.push_back("Girl_Shoes01");
	shoes.push_back("Girl_Shoes02");

	auto& hair = _skins[(int)SkinType::HAIR];
	hair.push_back("Girl_Hair01");
	hair.push_back("Girl_Hair02");

	auto& face = _skins[(int)SkinType::FACE];
	face.push_back("Girl_Face01");
	face.push_back("Girl_Face02");

	auto& hand = _skins[(int)SkinType::HAND];
	hand.push_back("Girl_Hand01");
	hand.push_back("Girl_Hand02");

	auto& glasses = _skins[(int)SkinType::GLASSES];
	glasses.push_back("");
	glasses.push_back("Girl_Glasses01");

	memset(_curSkin, 0, sizeof(_curSkin));

	applyCurSkin(monster);

	Sprite3D* monster2 = Sprite3D::create("model/dragon/dragon.c3b");
	monster2->setPosition3D(player->getPosition3D() + Vec3(50, 0, 0));
	monster2->setPositionY(terrain->getHeight(monster->getPositionX(), monster->getPositionZ()));
	auto animation3 = Animation3D::create("model/dragon/dragon.c3b");
	if (animation3)
	{
		auto animate = Animate3D::create(animation3);
		animate->setSpeed(0.6f);
		monster2->runAction(RepeatForever::create(animate));
	}

	scene->addChild(monster2);

	Sprite3D* monster3 = Sprite3D::create("model/archer/archer.c3b");
	monster3->setPosition3D(player->getPosition3D() + Vec3(25, 0, 0));
	monster3->setPositionY(terrain->getHeight(monster->getPositionX(), monster->getPositionZ()));
	auto animation4 = Animation3D::create("model/archer/archer.c3b");
	if (animation4)
	{
		auto animate = Animate3D::create(animation4);
		animate->setSpeed(0.6f);
		monster3->runAction(RepeatForever::create(animate));
	}

	scene->addChild(monster3);
	/************************************
	*2D
	*************************************/
	auto camera2D = Camera::create();
	camera2D->setCameraFlag(CameraFlag::USER2);
	scene->addChild(camera2D);

	// add title
	auto label = LabelTTF::create("Terrain", "fonts/arial.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2).x, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height).y - 30);
	label->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(label);

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
			auto sp = Sprite3D::create("axe.c3b");
			player->getAttachNode("Bip001 R Hand")->addChild(sp);
			item1->setString("Detach");
		}
		else
		{
			player->removeAttachNode("Bip001 R Hand");
			item1->setString("Attach");
		}
		isAttach = !isAttach;
	});
	auto itemSize = item1->getContentSize();
	item1->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height));

	auto menuSelect = CCMenu::create(item1, NULL);
	menuSelect->setPosition(Vec2(0, 0));
	menuSelect->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(menuSelect, 1);

	TTFConfig ttfConfig("fonts/arial.ttf", 13);
	auto label2 = Label::createWithTTF(ttfConfig, "Hair");
	auto item2 = MenuItemLabel::create(label2, std::bind(Chapter9_10::menuCallback_reSkin, std::placeholders::_1, monster));
	auto label3 = Label::createWithTTF(ttfConfig, "Glasses");
	auto item3 = MenuItemLabel::create(label3, std::bind(Chapter9_10::menuCallback_reSkin, std::placeholders::_1, monster));
	auto label4 = Label::createWithTTF(ttfConfig, "Coat");
	auto item4 = MenuItemLabel::create(label4, std::bind(Chapter9_10::menuCallback_reSkin, std::placeholders::_1, monster));
	auto label5 = Label::createWithTTF(ttfConfig, "Pants");
	auto item5 = MenuItemLabel::create(label5, std::bind(Chapter9_10::menuCallback_reSkin, std::placeholders::_1, monster));
	auto label6 = Label::createWithTTF(ttfConfig, "Shoes");
	auto item6 = MenuItemLabel::create(label6, std::bind(Chapter9_10::menuCallback_reSkin, std::placeholders::_1, monster));
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
	scene->addChild(pMenu1, 10);

	//zoom in & zoom out
	auto label7 = Label::createWithTTF(ttfConfig, "Zoom Out");
	auto item7 = MenuItemLabel::create(label7);
	auto label8 = Label::createWithTTF(ttfConfig, "Zoom In");
	auto item8 = MenuItemLabel::create(label8);
	auto label9 = Label::createWithTTF(ttfConfig, "Test1");
	auto item9 = MenuItemLabel::create(label9);
	auto label10 = Label::createWithTTF(ttfConfig, "Test2");
	auto item10 = MenuItemLabel::create(label10);
	item7->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 7));
	item8->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 8));
	item9->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 9));
	item10->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 10));
	auto pMenu2 = Menu::create(item7, item8, item9, item10, nullptr);
	pMenu2->setPosition(Vec2(0, 0));
	pMenu2->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(pMenu2, 11);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);
	listener2->onTouchBegan = [](Touch* touch, Event* event) -> bool {
		auto target = static_cast<Label*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			zoomOutPressed = true;
			return true;
		}
		return false;
	};
	listener2->onTouchEnded = [](Touch* touch, Event* event) {
		zoomOutPressed = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, label7);

	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->setSwallowTouches(true);
	listener3->onTouchBegan = [](Touch* touch, Event* event) -> bool {
		auto target = static_cast<Label*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			zoomInPressed = true;
			return true;
		}
		return false;
	};
	listener3->onTouchEnded = [](Touch* touch, Event* event) {
		zoomInPressed = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, label8);

	auto listener4 = EventListenerTouchOneByOne::create();
	listener4->setSwallowTouches(true);
	listener4->onTouchBegan = [](Touch* touch, Event* event) -> bool {
		auto target = static_cast<Label*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			test1 = true;
			return true;
		}
		return false;
	};
	listener4->onTouchEnded = [](Touch* touch, Event* event) {
		test1 = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, label9);

	scene->schedule(CC_SCHEDULE_SELECTOR(Chapter9_10::updateCamera), 0.0f);

	//add the menu item for back to main menu
	label = LabelTTF::create("MainMenu", "Arial", 24);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		item1 = nullptr;
		isAttach = false;
		player = nullptr;
		monster = nullptr;
		Director::getInstance()->replaceScene(Chapter9::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width - 80, origin.y + 25));

	auto menu = Menu::create(menuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	menu->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(menu, 1);

    // return the scene
    return scene;
}

void Chapter9_10::applyCurSkin(Sprite3D* player)
{
	for (ssize_t i = 0; i < player->getMeshCount(); i++) {
		auto mesh = player->getMeshByIndex(static_cast<int>(i));
		bool isVisible = false;
		for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
			if (mesh->getName() == _skins[j].at(_curSkin[j]))
			{
				isVisible = true;
				break;
			}
		}
		player->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
	}
}

void Chapter9_10::menuCallback_reSkin(Ref* sender, Sprite3D* player)
{
	long index = (long)(((MenuItemLabel*)sender)->getUserData());
	if (index < (int)SkinType::MAX_TYPE)
	{
		_curSkin[index] = (_curSkin[index] + 1) % _skins[index].size();
		applyCurSkin(player);
	}
}

void Chapter9_10::updateCamera(float fDelta)
{
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
		if (zoomOutPressed == true)
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
		else if (zoomInPressed == true)
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
		else if (test1 == true)
		{
			//if (_cameraType == CameraType::Free || _cameraType == CameraType::FirstPerson)
			{
				//Vec3  rotation3D = camera->getRotation3D();
				//rotation3D.y += 1;//左右
				//rotation3D.x += 1;//上下
				//rotation3D.z += 1;//旋转
				//camera->setRotation3D(rotation3D);
				//Vec3  position3D = camera->getPosition3D();
				//position3D.y -= 1;//上限移动
				//position3D.x -= 1;//左右移动
				//position3D.z -= 1;//前后移动
				static float _angle = 0.f;
				_angle -= CC_DEGREES_TO_RADIANS(1.0);

				//camera->setPosition3D(Vec3(50.0f * sinf(_angle), 50.0f, 50.0f * cosf(_angle)));//OK
				camera->setPosition3D(Vec3(0.0f, 50.0f * sinf(_angle), 50.0f * cosf(_angle)));
				{
					camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
				}
				//else
				//{
				//	camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f));
				//}
				//camera->setPosition3D(position3D);
			}
		}
		/*
		if (_bRotateRight == true)
		{
			if (_cameraType == CameraType::Free || _cameraType == CameraType::FirstPerson)
			{
				Vec3  rotation3D = _camera->getRotation3D();
				rotation3D.y -= 1;
				_camera->setRotation3D(rotation3D);
			}
		}
		*/
	}
}