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

	/************
	*3D
	*************/
	auto camera = scene->getDefaultCamera();
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
	player->getAttachNode("Bip001 L Hand")->addChild(handler);

	scene->addChild(player);

	static Sprite3D* monster = Sprite3D::create("chapter9/ReskinGirl.c3b");
	monster->setPosition3D(player->getPosition3D() + Vec3(-50, -50, 0));
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

	//applyCurSkin(monster);

	Sprite3D* monster2 = Sprite3D::create("model/dragon/dragon.c3b");
	monster2->setPosition3D(player->getPosition3D() + Vec3(50, -50, 0));
	monster2->setPositionY(terrain->getHeight(monster->getPositionX(), monster->getPositionZ()));
	auto animation3 = Animation3D::create("model/dragon/dragon.c3b");
	if (animation3)
	{
		auto animate = Animate3D::create(animation3);
		animate->setSpeed(0.6f);
		monster2->runAction(RepeatForever::create(animate));
	}

	scene->addChild(monster2);
	/************
	*2D
	*************/
	auto camera2D = Camera::create();
	camera2D->setCameraFlag(CameraFlag::USER2);
	scene->addChild(camera2D);

	// add title
	auto label = LabelTTF::create("Terrain", "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2).x, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height).y - 30);
	label->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(label);

	static bool isAttach = false;
	auto label1 = LabelTTF::create("Attach", "Arial", 13);
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