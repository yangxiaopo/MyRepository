#include "Chapter9_10.h"
#include "Chapter9.h"
//#include "Particle3D/CCParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

USING_NS_CC;

static int TerrainTag = 100;
static int PlayerTag = 101;

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
	camera->initPerspective(60, (GLfloat)winSize.width / winSize.height, 1.0f, 1000.0f);
	camera->setPosition3D(Vec3(0.0, 10, 10));
	camera->lookAt(Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));

	Terrain::DetailMap r("chapter9/dirt.jpg"), g("chapter9/Grass2.jpg"), b("chapter9/road.jpg"), a("chapter9/GreenSkin.jpg");
    Terrain::TerrainData data("chapter9/heightmap16.jpg","chapter9/alphamap.png",r,g,b,a);
    auto terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
	scene->addChild(terrain);

	static Sprite3D* player = nullptr;
    if(player == nullptr)
		player = Sprite3D::create("chapter9/orc.c3b");
	player->setRotation3D(Vec3(0, 180, 0));
	player->setScale(0.15f);
    player->setPositionY(terrain->getHeight(player->getPositionX(),player->getPositionZ()));
    auto animation = Animation3D::create("chapter9/orc.c3b");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
		animate->setSpeed(0.6f);
        player->runAction(RepeatForever::create(animate));
    }

	auto handler = PUParticleSystem3D::create("blackHole.pu", "pu_mediapack_01.material");
	handler->setScale(0.06f);
	handler->startParticleSystem();
	player->getAttachNode("Bip001 L Hand")->addChild(handler);

	scene->addChild(player);

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
	auto label1 = LabelTTF::create("Attach", "Arial", 24);
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
	item1->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - itemSize.height * 2));

	auto menuSelect = CCMenu::create(item1, NULL);
	menuSelect->setPosition(Vec2(0, 0));
	menuSelect->setCameraMask((unsigned short)CameraFlag::USER2);
	scene->addChild(menuSelect, 1);

	//add the menu item for back to main menu
	label = LabelTTF::create("MainMenu", "Arial", 24);
	auto menuItem = MenuItemLabel::create(label);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		item1 = nullptr;
		isAttach = false;
		player = nullptr;
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