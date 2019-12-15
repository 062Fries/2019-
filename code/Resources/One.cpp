#include "One.h"
#include "SimpleAudioEngine.h"
#include "hook.h"

USING_NS_CC;

bool if_stop = false;

Scene* Stageone::createScene()
{
	auto Stageonesence = Stageone::create();
	Stageonesence->initWithPhysics();
	auto world = Stageonesence->getPhysicsWorld();
	world->setGravity(Vec2::ZERO);
	Stageonesence->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return Stageonesence;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}



// on "init" you need to initialize your instance
bool Stageone::init()
{
	//////////////////////////////
	// 1. super init first

	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Stageone::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//加入分数标签
	auto label_socre = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 40);
	if (label_socre == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_socre->setPosition(Vec2(60,visibleSize.height - 40));

		// add the label as a child to this layer
		this->addChild(label_socre, 1);
		label_socre->setTextColor(Color4B(255, 215, 0, 255));
	}
	//加入过关目标标签
	auto label_goal = Label::createWithTTF("goal:", "fonts/Marker Felt.ttf", 40);
	if (label_goal == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_goal->setPosition(Vec2(50,visibleSize.height-80));

		// add the label as a child to this layer
		this->addChild(label_goal, 2);
		label_goal->setTextColor(Color4B(255, 215, 0, 255));
	}
	//加入时间标签
	auto label_time = Label::createWithTTF("Time:", "fonts/Marker Felt.ttf", 40);
	if (label_time == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label_time->setPosition(Vec2(visibleSize.width-200,
			visibleSize.height-60));

		// add the label as a child to this layer
		this->addChild(label_time, 2);
		label_time->setTextColor(Color4B(255, 215, 0, 255));
	}
	//加入人物背景
	auto playerbgsprite = Sprite::create("topbg.png");
	if (playerbgsprite == nullptr)
	{
		problemLoading("'topbg.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		playerbgsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height-205));

		// add the sprite as a child to this layer
		this->addChild(playerbgsprite, 0);
	}
	//遮盖钩子上端的线
	auto playertopbgsprite = Sprite::create("topbg4.png");
	if (playertopbgsprite == nullptr)
	{
		problemLoading("'topbg4.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		playertopbgsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 205));

		// add the sprite as a child to this layer
		this->addChild(playertopbgsprite, 2);
	}

	//加入地底背景
	auto stage1sprite = Sprite::create("stage1.png");
	if (stage1sprite == nullptr)
	{
		problemLoading("'stage1.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		stage1sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-135));

		// add the sprite as a child to this layer
		this->addChild(stage1sprite, 1);
	}
	auto myhook = Hook::create("hook.png");
	auto gold = Sprite::create("menugold.png");
	//创建物理事件
	auto physicsBody1 = PhysicsBody::createBox(Size(65.0f, 81.0f),
		PhysicsMaterial(0.1f, 1.0f, 0.0f),Vec2(0,-380));
	physicsBody1->setDynamic(true);
	myhook->addComponent(physicsBody1);

	auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	gold->addComponent(physicsBody);

	//Hook类创建钩子

	myhook->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.035f));//设置锚点
	myhook->setScale(1.2);
	myhook->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+140));
	this->addChild(myhook, 1);
	myhook->runRotateAction();//使钩子来回摆动

	gold->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-140));
	addChild(gold, 1);
	/*
	//测试钩子移动过程中是否旋转
	auto move = MoveTo::create(3, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	myhook->runAction(move);
	*/
	
	//auto launch = Label::createWithSystemFont("shoot", "fonts/arial.ttf", 40);
	//auto menu_launch = MenuItemLabel::create(launch, CC_CALLBACK_1(Stageone::runTarget,this,myhook));
	//创建好了菜单条目，就需要加入菜单中，所以下面就是创建菜单
	//auto menu_shoot = Menu::create(menu_launch, NULL);
	//把菜单添加到MyFirstScene层中
	//menu_shoot->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	//this->addChild(menu_shoot, 1);
	//launch->setTextColor(Color4B(0, 0, 0, 255));

	//添加点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(Stageone::runTarget, this, myhook);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;




}


void Stageone::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


bool Stageone::runTarget(Ref* pSender,Hook* phook)
{
	phook->stopRotate();
	//auto move = MoveTo::create(10, Vec2(200, 200));
	phook->runTargetAction();
	//phook->runAction(move);
	return true;
	//phook->runRotateAction();
}