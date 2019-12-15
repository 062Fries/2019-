#include "One.h"
#include "SimpleAudioEngine.h"
#include "hook.h"
#include "HelloWorldScene.h"
#include <iostream>
#include "NameSpace.h"
#include <math.h>
#include "grab_objects.h"
#include <list>
#include <sstream>
#include "Shop.h"
USING_NS_CC;
//全局变量

using namespace Items;
short int stage_number = 0;
std::string socre = "0";
extern short int bomb_number;
extern bool ifStrength;

extern bool ifBook;
extern bool ifExpensive;
extern short int strength_times;


Scene* Stageone::createScene()
{
	auto Stageonescene = Stageone::create();
	//Stageonesence->initWithPhysics();
	//auto layer = Stageone::create();
	//Stageonesence->addChild(layer);
	//world = Stageonesence->getPhysicsWorld();
	//world->setGravity(Vec2::ZERO);
	//Stageonesence->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return Stageonescene;
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

	if (!Scene::init())
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

	//添加炸弹
	auto Bomb = MenuItemImage::create("huancun2 copy.png", "huancun2 copy.png",
		CC_CALLBACK_1(Stageone::explode, this));
	auto menuBomb = Menu::create(Bomb, NULL);
	menuBomb->setPosition(Vec2(800, 680));
	this->addChild(menuBomb, 3);
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
		this->addChild(label_socre, 3);
		label_socre->setTextColor(Color4B(0, 0, 0, 255));
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
		this->addChild(label_goal, 3);
		label_goal->setTextColor(Color4B(0, 0, 0, 255));
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
			visibleSize.height-40));

		// add the label as a child to this layer
		this->addChild(label_time, 3);
		label_time->setTextColor(Color4B(0, 0, 0, 255));
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
		playerbgsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height-65));
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
		playertopbgsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 65));

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
		stage1sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-70));
		stage1sprite->setScale(1.3);
		// add the sprite as a child to this layer
		this->addChild(stage1sprite, 1);
	}

	//创建人物
	miner_Action = Sprite::create("mAnimation1.png");
	miner_Action->setPosition(Vec2(535, 700));
	this->addChild(miner_Action, 2);


	//创建钩子、金块精灵
	myhook = Hook::create("hook.png");

	myhook->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.05f));//设置锚点
	myhook->setScale(1.2);
	myhook->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 287));
	this->addChild(myhook, 1);
	myhook->runRotateAction();//使钩子来回摆动

	inititem();
	schedule(schedule_selector(Stageone::timeReduce), 1.0f);
	scheduleOnce(schedule_selector(Stageone::checkTime), 60.0f);
	



	//添加点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(Stageone::runTarget, this, myhook,miner_Action);
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


bool Stageone::runTarget(Ref* pSender,Hook* phook, Sprite* psprite)
{
	auto mAnimation = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		char nameSize[100] = { 0 };
		sprintf(nameSize, "mAnimation%d.png", i);
		mAnimation->addSpriteFrameWithFile(nameSize);
	}
	mAnimation->setDelayPerUnit(0.1f);
	mAnimation->setLoops(1);
	mAnimation->setRestoreOriginalFrame(true);
	mAnimate = Animate::create(mAnimation);
	psprite->runAction(mAnimate);
	phook->stopRotate();
	phook->runTargetAction();
	this->scheduleUpdate();

	return true;

}


void Stageone::update(float dt)
{
	if (numberBomb != NULL)
	{
		std::ostringstream os; //构造一个输出字符串流，流内容为空 
		os << bomb_number; //向输出字符串流中输出int整数i的内容 
						   //socre = std::to_string(temp);
		std::string s = os.str();
		numberBomb->setString(s);
	}

	float x = myhook->getPositionX();
	float y = myhook->getPositionY();
	//short int location = -1;
	for (int i = 0; i < 20; i++)
	{
		if ((pow(x - item[i]->getPositionX(), 2) +
			pow(y - item[i]->getPositionY(), 2) <= pow(item[i]->radius, 2)) && !isRunback
			&& !myhook->Catch&&item[i]->ifmove == 0)
		{
			
			if (item[i]->boom == 1)
			{
				explosion(i);
				item[i]->backtime = 1;
			}
			//location = i;//标记被抓取物的位置
			isRunback = true; //避免Runback重复执行
			myhook->stopAllActions();
			myhook->Catch = true;//使钩子不能抓取一个以上的物体

			float angle = myhook->getRotation();
			//if (item[i]->ifmove == 0)//标记该抓取物使之不能被再一次抓取
			auto itemMove = MoveTo::create(0.01, Vec2(x - 40 * sin(angle*M_PI / 180),
				y - 40 * cos(angle*M_PI / 180)));
			//使物体移到钩子所在直线后,随钩子一起回到发射点
			auto itemMoveBack = MoveTo::create(item[i]->backtime, Vec2(512, 671));
			auto action = cocos2d::Sequence::create(itemMove, itemMoveBack, NULL);
			item[i]->runAction(action);
			item[i]->ifmove = 1;//将物体标记为被抓取过
			myhook->runBack(item[i]->backtime);
			//加入人物收回钩子的动作
			auto mAnimation = Animation::create();
			for (int i = 1; i < 7; i++)
			{
				char nameSize[100] = { 0 };
				sprintf(nameSize, "mAnimation%d.png", i);
				mAnimation->addSpriteFrameWithFile(nameSize);
			}
			mAnimation->setDelayPerUnit(0.1f);
			mAnimation->setLoops(-1);
			mAnimation->setRestoreOriginalFrame(true);
			mAnimate = Animate::create(mAnimation);
			miner_Action->runAction(mAnimate);

		}
		else
			if ((x <= 0 || y <= 0 || x >= 1024) && !isRunback)
			{
				float a = 2;
				isRunback = true;
				myhook->runBack(a);
				//加入人物动作
				auto mAnimation = Animation::create();
				for (int i = 1; i < 7; i++)
				{
					char nameSize[100] = { 0 };
					sprintf(nameSize, "mAnimation%d.png", i);
					mAnimation->addSpriteFrameWithFile(nameSize);
				}
				mAnimation->setDelayPerUnit(0.1f);
				mAnimation->setLoops(-1);
				mAnimation->setRestoreOriginalFrame(true);
				mAnimate = Animate::create(mAnimation);
				miner_Action->runAction(mAnimate);
			}

	}
	if (x == 512.0f && y == 671.0f&&isRunback)
	{
		isRunback = false;
		myhook->Catch = false;//将钩子抓取状态置为否
		myhook->stopAllActions();
		this->stopAction(mAnimate);//停止人物动作
		for (int i = 0; i < 20; i++)
		{
			if (item[i]->ifmove == 1 && item[i]->boom != 2)
			{
				if (item[i]->breed == 5)
				{
					bomb_number++;
					item[i]->breed = 1;
				}
				else
					if (item[i]->breed == 6)
					{
						for (int m = 0; m < 20; m++)
						{
							item[m]->backtime /= 3;
						}
						item[i]->backtime *= 3;
						item[i]->breed = 1;
					}
				item[i]->setVisible(false);//隐藏已经被抓取的物体
				item[i]->setPosition(Vec2(1024, 768));
				std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
				int it;
				is >> it; //从is流中读入一个int整数存入i中
				int temp = it + item[i]->value;
				item[i]->value = 0;
				std::ostringstream os; //构造一个输出字符串流，流内容为空 
				os << temp; //向输出字符串流中输出int整数i的内容 
				socre = os.str();
				Socre->setString(socre);
			}
		}
		myhook->runRotateAction();//钩子再次旋转
	}
}


void Stageone::inititem()
{
	if (stage_number == 1)
	{
		//初始化
		goalSocre = Label::createWithTTF("700", "fonts/Marker Felt.ttf", 40);//目标分数
		target_socre = 700;
		goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
		this->addChild(goalSocre, 3);
		goalSocre->setTextColor(Color4B(0, 0, 0, 255));

		item[0] = GrabObject::create("smallgold.png");
		item[1] = GrabObject::create("middlegold.png");
		item[2] = GrabObject::create("smallgold.png");
		item[3] = GrabObject::create("biggold.png");
		item[4] = GrabObject::create("smallgold.png");
		item[5] = GrabObject::create("smallgold.png");
		item[6] = GrabObject::create("biggold.png");
		item[7] = GrabObject::create("smallstone.png");
		item[8] = GrabObject::create("smallstone.png");
		item[9] = GrabObject::create("smallstone.png");
		item[10] = GrabObject::create("bigstone.png");
		item[11] = GrabObject::create("bigstone.png");
		for (int i = 13; i < 20; i++)
		{
			item[i] = GrabObject::create("smallgold.png");
			item[i]->setPosition(Vec2(1020, 760));
			item[i]->setVisible(false);
		}
		item[12] = GrabObject::create("bag.png");
		for (int i = 0; i < 12; i++)
			item[i]->setScale(0.5);
		item[12]->setScale(1.5);
		item[0]->setPosition(Vec2(1024 - 103, 483));
		item[1]->setPosition(Vec2(1024 - 95, 366));
		item[2]->setPosition(Vec2(1024 - 228, 271));
		item[3]->setPosition(Vec2(1024 - 234, 172));
		item[4]->setPosition(Vec2(1024 - 271, 415));
		item[5]->setPosition(Vec2(1024 - 497, 245));
		item[6]->setPosition(Vec2(1024 - 786, 323));
		item[7]->setPosition(Vec2(1024 - 209, 416));
		item[8]->setPosition(Vec2(1024 - 216, 324));
		item[9]->setPosition(Vec2(1024 - 751, 458));
		item[10]->setPosition(Vec2(1024 - 591, 376));
		item[11]->setPosition(Vec2(1024 - 383, 283));
		item[12]->setPosition(Vec2(1024 - 528, 76));

		item[0]->init(50, 1, 20, 3);
		item[1]->init(200, 1, 32, 5);
		item[2]->init(50, 1, 20, 3);
		item[3]->init(500, 1, 64, 8);
		item[4]->init(50, 1, 20, 1.5);
		item[5]->init(50, 1, 20, 2);
		item[6]->init(500, 1, 64, 6);
		item[7]->init(10, 2, 20, 5);
		item[8]->init(10, 2, 20, 6);
		item[9]->init(10, 2, 20, 4);
		item[10]->init(20, 2, 48, 7);
		item[11]->init(20, 2, 48, 9);

		item[12]->initbag();//待处理
		for (int i = 0; i < 20; i++)
		{
			this->addChild(item[i], 1);
		}
	}
	else
		if (stage_number == 2)
		{
			goalSocre = Label::createWithTTF("1500", "fonts/Marker Felt.ttf", 40);//目标分数
			
			target_socre = 1500;
			goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
			this->addChild(goalSocre, 3);
			goalSocre->setTextColor(Color4B(0, 0, 0, 255));

			item[0] = GrabObject::create("biggold.png");
			item[1] = GrabObject::create("smallgold.png");
			item[2] = GrabObject::create("smallgold.png");
			item[3] = GrabObject::create("bigstone.png");
			item[4] = GrabObject::create("smallgold.png");
			item[5] = GrabObject::create("bag.png");
			item[6] = GrabObject::create("smallstone.png");
			item[7] = GrabObject::create("middlegold.png");
			item[8] = GrabObject::create("biggold.png");
			item[9] = GrabObject::create("bigstone.png");
			item[10] = GrabObject::create("bigstone.png");
			item[11] = GrabObject::create("bag.png");
			item[12] = GrabObject::create("smallstone.png");
			item[13] = GrabObject::create("diamond.png");
			item[14] = GrabObject::create("biggold.png");
			for (int e = 15; e <= 19; e++) {
				item[e] = GrabObject::create("biggold.png");
				item[e]->setVisible(false);
				item[e]->setPosition(Vec2(0, 0));
			}
			for (int i = 0; i < 15; i++)
				item[i]->setScale(0.5);
			item[5]->setScale(1.5);
			item[11]->setScale(1.5);
			item[13]->setScale(1.5);
			item[0]->setPosition(Vec2(1024 - 94, 143));
			item[1]->setPosition(Vec2(1024 - 178, 344));
			item[2]->setPosition(Vec2(1024 - 244, 275));
			item[3]->setPosition(Vec2(1024 - 249, 200));
			item[4]->setPosition(Vec2(1024 - 281, 432));
			item[5]->setPosition(Vec2(1024 - 328, 180));
			item[6]->setPosition(Vec2(1024 - 376, 180));
			item[7]->setPosition(Vec2(1024 - 406, 229));
			item[8]->setPosition(Vec2(1024 - 439, 1));
			item[9]->setPosition(Vec2(1024 - 512, 126));
			item[10]->setPosition(Vec2(1024 - 525, 362));
			item[11]->setPosition(Vec2(1024 - 579, 59));
			item[12]->setPosition(Vec2(1024 - 596, 262));
			item[13]->setPosition(Vec2(1024 - 653, 222));
			item[14]->setPosition(Vec2(1024 - 1017, 253));

			item[0]->init(500, 1, 64, 10);
			item[1]->init(50, 1, 20, 2);
			item[2]->init(50, 1, 20, 2.5);
			item[3]->init(20, 2, 48, 9);
			item[4]->init(50, 1, 20, 1.5);
			item[5]->initbag();// 初始化问号袋子
			item[6]->init(10, 2, 20, 4);
			item[7]->init(200, 1, 32, 5);
			item[8]->init(500, 1, 64, 10);
			item[9]->init(20, 2, 48, 9);
			item[10]->init(200, 1, 32, 6);
			item[11]->initbag();//??????
			item[12]->init(10, 2, 20, 5);
			item[13]->init(600, 3, 20, 5);
			item[14]->init(500, 1, 64, 11);

			for (int i = 0; i < 20; i++)
			{
				this->addChild(item[i], 1);
			}
		}
		else
			if (stage_number == 3)
			{
				goalSocre = Label::createWithTTF("2400", "fonts/Marker Felt.ttf", 40);//目标分数
				
				target_socre = 2400;
				goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
				this->addChild(goalSocre, 3);
				goalSocre->setTextColor(Color4B(0, 0, 0, 255));

				item[0] = GrabObject::create("biggold.png");
				item[1] = GrabObject::create("diamond.png");
				item[2] = GrabObject::create("biggold.png");
				item[3] = GrabObject::create("smallstone.png");
				item[4] = GrabObject::create("bigstone.png");
				item[5] = GrabObject::create("biggold.png");
				item[6] = GrabObject::create("bag.png");
				item[7] = GrabObject::create("middlegold.png");
				item[8] = GrabObject::create("diamond.png");
				item[9] = GrabObject::create("smallgold.png");
				item[10] = GrabObject::create("bigstone.png");
				item[11] = GrabObject::create("bag.png");
				item[12] = GrabObject::create("biggold.png");
				item[13] = GrabObject::create("middlegold.png");
				item[14] = GrabObject::create("bigstone.png");
				item[15] = GrabObject::create("diamond.png");
				for (int e = 16; e <= 19; e++) {
					item[e] = GrabObject::create("biggold.png");
					item[e]->setVisible(false);
					item[e]->setPosition(Vec2(0, 0));
				}
				for (int i = 0; i < 15; i++)
					item[i]->setScale(0.5);
				item[1]->setScale(1.5);
				item[6]->setScale(1.5);
				item[8]->setScale(1.5);
				item[11]->setScale(1.5);
				item[15]->setScale(1.5);
				item[0]->setPosition(Vec2(1024 - 3, 323));
				item[1]->setPosition(Vec2(1024 - 61, 204));
				item[2]->setPosition(Vec2(1024 - 108, 11));
				item[3]->setPosition(Vec2(1024 - 112, 136));
				item[4]->setPosition(Vec2(1024 - 207, 394));
				item[5]->setPosition(Vec2(1024 - 266, 162));
				item[6]->setPosition(Vec2(1024 - 418, 30));
				item[7]->setPosition(Vec2(1024 - 488, 234));
				item[8]->setPosition(Vec2(1024 - 547, 3));
				item[9]->setPosition(Vec2(1024 - 586, 379));
				item[10]->setPosition(Vec2(1024 - 597, 101));
				item[11]->setPosition(Vec2(1024 - 707, 194));
				item[12]->setPosition(Vec2(1024 - 743, 8));
				item[13]->setPosition(Vec2(1024 - 796, 296));
				item[14]->setPosition(Vec2(1024 - 837, 162));
				item[15]->setPosition(Vec2(1024 - 943, 139));

				item[0]->init(500, 1, 64, 8);
				item[1]->init(600, 3, 20, 5);
				item[2]->init(500, 1, 64, 10);
				item[3]->init(10, 2, 20, 5);
				item[4]->init(20, 2, 48, 5);
				item[5]->init(500, 1, 64, 8);
				item[6]->initbag();//?????
				item[7]->init(200, 1, 32, 6);
				item[8]->init(600, 3, 20, 6);
				item[9]->init(50, 1, 20, 2);
				item[10]->init(20, 2, 48, 7);
				item[11]->initbag();//??????
				item[12]->init(500, 1, 64, 9);
				item[13]->init(200, 1, 32, 4);
				item[14]->init(20, 2, 48, 7);
				item[15]->init(600, 3, 20, 6);

				for (int i = 0; i < 20; i++)
				{
					this->addChild(item[i], 1);
				}
			}

			else
				if (stage_number == 4)
				{
					goalSocre = Label::createWithTTF("3400", "fonts/Marker Felt.ttf", 40);//目标分数
					
					target_socre = 3400;
					goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
					this->addChild(goalSocre, 3);
					goalSocre->setTextColor(Color4B(0, 0, 0, 255));

					item[0] = GrabObject::create("middlegold.png");
					item[1] = GrabObject::create("diamond.png");
					item[2] = GrabObject::create("diamond.png");
					item[3] = GrabObject::create("bomb.png");//TNT
					item[4] = GrabObject::create("biggold.png");
					item[5] = GrabObject::create("smallgold.png");
					item[6] = GrabObject::create("biggold.png");
					item[7] = GrabObject::create("bigstone.png");
					item[8] = GrabObject::create("middlegold.png");
					item[9] = GrabObject::create("bag.png");
					item[10] = GrabObject::create("diamond.png");
					item[11] = GrabObject::create("bomb.png");//TNT
					item[12] = GrabObject::create("bigstone.png");
					item[13] = GrabObject::create("diamond.png");
					item[14] = GrabObject::create("bag.png");
					item[15] = GrabObject::create("biggold.png");
					for (int e = 16; e <= 19; e++) {
						item[e] = GrabObject::create("biggold.png");
						item[e]->setVisible(false);
						item[e]->setPosition(Vec2(0, 0));
					}
					for (int i = 0; i <= 15; i++)
						item[i]->setScale(0.5);
					item[1]->setScale(1.5);
					item[2]->setScale(1.5);
					item[9]->setScale(1.5);
					item[10]->setScale(1.5);
					item[13]->setScale(1.5);
					item[14]->setScale(1.5);
					item[0]->setPosition(Vec2(1024 - 67, 220));
					item[1]->setPosition(Vec2(1024 - 161, 92));
					item[2]->setPosition(Vec2(1024 - 162, 326));
					item[3]->setPosition(Vec2(1024 - 275, 324));
					item[4]->setPosition(Vec2(1024 - 298, 198));
					item[5]->setPosition(Vec2(1024 - 371, 369));
					item[6]->setPosition(Vec2(1024 - 458, 1));
					item[7]->setPosition(Vec2(1024 - 505, 157));
					item[8]->setPosition(Vec2(1024 - 627, 258));
					item[9]->setPosition(Vec2(1024 - 630, 51));
					item[10]->setPosition(Vec2(1024 - 687, 171));
					item[11]->setPosition(Vec2(1024 - 748, 225));
					item[12]->setPosition(Vec2(1024 - 825, 393));
					item[13]->setPosition(Vec2(1024 - 860, 239));
					item[14]->setPosition(Vec2(1024 - 889, 58));
					item[15]->setPosition(Vec2(1024 - 995, 113));

					item[0]->init(200, 1, 32, 6);
					item[1]->init(600, 3, 20, 5);
					item[2]->init(600, 3, 20, 3);
					item[3]->init(0, 2, 48, 6);
					item[4]->init(500, 1, 64, 7);
					item[5]->init(50, 1, 20, 4);
					item[6]->init(500, 1, 64, 8);
					item[7]->init(20, 2, 48, 7);
					item[8]->init(200, 1, 32, 6);
					item[9]->initbag();//???????
					item[10]->init(600, 3, 20, 5);
					item[11]->init(0, 2, 48, 7);
					item[12]->init(20, 2, 48, 6);
					item[13]->init(600, 3, 20, 5);
					item[14]->initbag();//???????
					item[15]->init(500, 1, 64, 10);

					item[3]->boom = 1;
					item[11]->boom = 1;

					for (int i = 0; i < 20; i++)
					{
						this->addChild(item[i], 1);
					}
				}
				else
					if (stage_number == 5)
					{
						goalSocre = Label::createWithTTF("4200", "fonts/Marker Felt.ttf", 40);//目标分数
						
						target_socre = 4200;
						goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
						this->addChild(goalSocre, 3);
						goalSocre->setTextColor(Color4B(0, 0, 0, 255));

						item[0] = GrabObject::create("diamond.png");
						item[1] = GrabObject::create("bag.png");
						item[2] = GrabObject::create("smallstone.png");
						item[3] = GrabObject::create("bigstone.png");
						item[4] = GrabObject::create("biggold.png");
						item[5] = GrabObject::create("smallgold.png");
						item[6] = GrabObject::create("bigstone.png");
						item[7] = GrabObject::create("smallstone.png");//pig
						item[8] = GrabObject::create("biggold.png");
						item[9] = GrabObject::create("biggold.png");
						item[10] = GrabObject::create("bomb.png");//TNT
						item[11] = GrabObject::create("diamond.png");
						item[12] = GrabObject::create("bag.png");
						item[13] = GrabObject::create("bigstone.png");
						for (int e = 14; e <= 19; e++) {
							item[e] = GrabObject::create("biggold.png");
							item[e]->setVisible(false);
							item[e]->setPosition(Vec2(0, 0));
						}
						for (int i = 0; i <= 13; i++)
							item[i]->setScale(0.5);
						item[0]->setScale(1.5);
						item[1]->setScale(1.5);
						item[11]->setScale(1.5);
						item[12]->setScale(1.5);
						item[0]->setPosition(Vec2(1024 - 161, 68));
						item[1]->setPosition(Vec2(1024 - 174, 171));
						item[2]->setPosition(Vec2(1024 - 236, 236));
						item[3]->setPosition(Vec2(1024 - 238, 337));
						item[4]->setPosition(Vec2(1024 - 294, 5));
						item[5]->setPosition(Vec2(1024 - 348, 258));
						item[6]->setPosition(Vec2(1024 - 394, 149));
						item[7]->setPosition(Vec2(1024 - 551, 425));
						item[8]->setPosition(Vec2(1024 - 558, 279));
						item[9]->setPosition(Vec2(1024 - 656, 62));
						item[10]->setPosition(Vec2(1024 - 737, 223));
						item[11]->setPosition(Vec2(1024 - 861, 191));
						item[12]->setPosition(Vec2(1024 - 941, 315));
						item[13]->setPosition(Vec2(1024 - 968, 45));

						item[0]->init(600, 3, 20, 5);
						item[1]->initbag();//????????
						item[2]->init(10, 2, 20, 5);
						item[3]->init(20, 2, 48, 6);
						item[4]->init(500, 1, 64, 7);
						item[5]->init(50, 1, 20, 4);
						item[6]->init(20, 2, 48, 6);
						item[7]->init(20, 2, 48, 4);
						item[8]->init(500, 1, 64, 5);
						item[9]->init(500, 1, 64, 8);
						item[10]->init(0, 2, 48, 6);
						item[11]->init(600, 3, 20, 5);
						item[12]->initbag();//???????
						item[13]->init(500, 1, 64, 9);

						item[10]->boom = 1;

						for (int i = 0; i < 20; i++)
						{
							this->addChild(item[i], 1);
						}
					}
					else
						if (stage_number == 6)
						{
							goalSocre = Label::createWithTTF("5300", "fonts/Marker Felt.ttf", 40);//目标分数
							
							target_socre = 5300;
							goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
							this->addChild(goalSocre, 3);
							goalSocre->setTextColor(Color4B(0, 0, 0, 255));

							item[0] = GrabObject::create("bigstone.png");
							item[1] = GrabObject::create("biggold.png");
							item[2] = GrabObject::create("smallstone.png");
							item[3] = GrabObject::create("bomb.png");//TNT
							item[4] = GrabObject::create("smallstone.png");
							item[5] = GrabObject::create("diamond.png");
							item[6] = GrabObject::create("smallgold.png");
							item[7] = GrabObject::create("bigstone.png");
							item[8] = GrabObject::create("middlegold.png");
							item[9] = GrabObject::create("smallgold.png");
							item[10] = GrabObject::create("smallgold.png");
							item[11] = GrabObject::create("middlegold.png");
							item[12] = GrabObject::create("bigstone.png");
							item[13] = GrabObject::create("smallgold.png");
							item[14] = GrabObject::create("bag.png");
							item[15] = GrabObject::create("bomb.png");//TNT

							item[16] = GrabObject::create("bigstone.png");
							item[17] = GrabObject::create("biggold.png");
							item[18] = GrabObject::create("diamond.png");
							item[19] = GrabObject::create("biggold.png");

							for (int i = 0; i <= 19; i++)
								item[i]->setScale(0.5);
							item[5]->setScale(1.5);
							item[14]->setScale(1.5);
							item[18]->setScale(1.5);
							item[0]->setPosition(Vec2(1024 - 175, 200));
							item[1]->setPosition(Vec2(1024 - 208, 11));
							item[2]->setPosition(Vec2(1024 - 233, 301));
							item[3]->setPosition(Vec2(1024 - 293, 229));
							item[4]->setPosition(Vec2(1024 - 318, 338));
							item[5]->setPosition(Vec2(1024 - 328, 43));
							item[6]->setPosition(Vec2(1024 - 366, 268));
							item[7]->setPosition(Vec2(1024 - 409, 191));
							item[8]->setPosition(Vec2(1024 - 434, 407));
							item[9]->setPosition(Vec2(1024 - 493, 360));
							item[10]->setPosition(Vec2(1024 - 502, 83));
							item[11]->setPosition(Vec2(1024 - 511, 175));
							item[12]->setPosition(Vec2(1024 - 560, 290));
							item[13]->setPosition(Vec2(1024 - 617, 376));
							item[14]->setPosition(Vec2(1024 - 633, 91));
							item[15]->setPosition(Vec2(1024 - 683, 376));
							item[16]->setPosition(Vec2(1024 - 758, 380));
							item[17]->setPosition(Vec2(1024 - 778, 105));
							item[18]->setPosition(Vec2(1024 - 865, 168));
							item[19]->setPosition(Vec2(1024 - 998, 185));

							item[0]->init(20, 2, 18, 7);
							item[1]->init(500, 1, 64, 8);
							item[2]->init(10, 2, 20, 4);
							item[3]->init(0, 1, 48, 6);
							item[4]->init(10, 2, 20, 3);
							item[5]->init(600, 3, 20, 6);
							item[6]->init(50, 1, 48, 7);
							item[7]->init(20, 2, 48, 7);
							item[8]->init(200, 1, 32, 5);
							item[9]->init(50, 1, 20, 2);
							item[10]->init(50, 1, 20, 6);
							item[10]->init(200, 1, 32, 6);
							item[11]->init(20, 2, 48, 6);
							item[12]->init(50, 1, 20, 2);
							item[13]->init(20, 1, 48, 5);
							item[14]->initbag();//???????
							item[15]->init(0, 1, 48, 7);
							item[16]->init(20, 1, 48, 6);
							item[17]->init(500, 1, 64, 8);
							item[18]->init(600, 3, 20, 5);
							item[19]->init(500, 1, 64, 8);
							item[3]->boom = 1;
							item[15]->boom = 1;
							for (int i = 0; i < 20; i++)
							{
								this->addChild(item[i], 1);
							}
						}
						else
							if (stage_number == 7)
							{
								goalSocre = Label::createWithTTF("6700", "fonts/Marker Felt.ttf", 40);//目标分数
								target_socre = 6700;
								goalSocre->setPosition(Vec2(200, 768 - 80));//目标分数
								this->addChild(goalSocre, 3);
								goalSocre->setTextColor(Color4B(0, 0, 0, 255));

								item[0] = GrabObject::create("biggold.png");
								item[1] = GrabObject::create("middlegold.png");
								item[2] = GrabObject::create("bigstone.png");
								item[3] = GrabObject::create("bomb.png");//TNT
								item[4] = GrabObject::create("smallgold.png");
								item[5] = GrabObject::create("diamond.png");
								item[6] = GrabObject::create("smallstone.png");
								item[7] = GrabObject::create("bag.png");
								item[8] = GrabObject::create("diamond.png");
								item[9] = GrabObject::create("smallgold.png");
								item[10] = GrabObject::create("bomb.png");//TNT
								item[11] = GrabObject::create("bigstone.png");
								item[12] = GrabObject::create("middlegold.png");
								item[13] = GrabObject::create("biggold.png");
								for (int e = 14; e <= 19; e++) {
									item[e] = GrabObject::create("biggold.png");
									item[e]->setVisible(false);
									item[e]->setPosition(Vec2(0, 0));
								}
								for (int i = 0; i <= 13; i++)
									item[i]->setScale(0.5);
								item[5]->setScale(1.5);
								item[7]->setScale(1.5);
								item[8]->setScale(1.5);
								item[0]->setPosition(Vec2(1024 - 174, 111));
								item[1]->setPosition(Vec2(1024 - 244, 239));
								item[2]->setPosition(Vec2(1024 - 289, 380));
								item[3]->setPosition(Vec2(1024 - 300, 128));
								item[4]->setPosition(Vec2(1024 - 408, 281));
								item[5]->setPosition(Vec2(1024 - 463, 212));
								item[6]->setPosition(Vec2(1024 - 499, 333));
								item[7]->setPosition(Vec2(1024 - 509, 128));
								item[8]->setPosition(Vec2(1024 - 549, 212));
								item[9]->setPosition(Vec2(1024 - 595, 281));
								item[10]->setPosition(Vec2(1024 - 748, 128));
								item[11]->setPosition(Vec2(1024 - 772, 380));
								item[12]->setPosition(Vec2(1024 - 804, 240));
								item[13]->setPosition(Vec2(1024 - 873, 111));

								item[0]->init(500, 1, 64, 8);
								item[1]->init(200, 1, 32, 6);
								item[2]->init(20, 2, 48, 6);
								item[3]->init(0, 1, 48, 8);
								item[4]->init(50, 1, 20, 4);
								item[5]->init(600, 3, 20, 5);
								item[6]->init(20, 2, 20, 4);
								item[7]->initbag();//????????
								item[8]->init(600, 3, 20, 5);
								item[9]->init(50, 1, 20, 4);
								item[10]->init(0, 1, 48, 8);
								item[11]->init(20, 2, 48, 6);
								item[12]->init(200, 1, 43, 6);
								item[13]->init(500, 1, 64, 8);
								item[3]->boom = 1;
								item[10]->boom = 1;
								for (int i = 0; i < 20; i++)
								{
									this->addChild(item[i], 1);
								}
							}

	if (ifStrength)     //减少钩子收回时间
	{
		for (int i = 0; i < 20; i++)
		{
			item[i]->backtime /= strength_times;
		}
		if (ifBook)
		{
			for (int i = 0; i < 20; i++)  //增加石头价值
			{
				if (item[i]->breed == 2)
					item[i]->value *= 5;
			}
		}
		if (ifExpensive)   //增加钻石价值
		{
			for (int i = 0; i < 20; i++)
			{
				if (item[i]->breed == 3)
					item[i]->value *= 1.5;
			}
		}
	}
	
	std::ostringstream os; //构造一个输出字符串流，流内容为空 
	os << bomb_number; //向输出字符串流中输出int整数i的内容 
				 //socre = std::to_string(temp);
	std::string s = os.str();
	numberBomb = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 40);//分数
	numberBomb->setPosition(Vec2(850, 680));
	this->addChild(numberBomb,3);
	numberBomb->setTextColor(Color4B(0, 0, 0, 255));

	Socre = Label::createWithTTF(socre, "fonts/Marker Felt.ttf", 40);//分数
	Socre->setPosition(Vec2(200, 768 - 40));
	this->addChild(Socre, 3);
	Socre->setTextColor(Color4B(0, 0, 0, 255));

	Times = Label::createWithTTF("60", "fonts/Marker Felt.ttf", 40);//时间
	Times->setPosition(Vec2(900, 768 - 40));
	this->addChild(Times, 3);
	Times->setTextColor(Color4B(0, 0, 0, 255));
}


void Stageone::timeReduce(float dt)
{
	times--;
	std::ostringstream os; //构造一个输出字符串流，流内容为空 
	os << times; //向输出字符串流中输出int整数i的内容 
				//socre = std::to_string(temp);
	std::string s = os.str();
	Times->setString(s);
}

void Stageone::toShop(Ref* pSender)
{
	Director::getInstance()->replaceScene(_Shop::createScene());//进入商店场景
}

void Stageone::checkTime(float dt)
{
	//isChange = true;
	this->unscheduleAllSelectors();
	times = 60;
	isChange = false;
	ifStrength = false;
	ifBook = false;
	ifExpensive = false;
	strength_times = 1;
	std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
	int i;
	is >> i; //从is流中读入一个int整数存入i中
	//if(i >= target_socre)
		toShop(this);
}


void Stageone::explode(Ref* pSender)//炸弹
{
	if (bomb_number > 0)
	{
		bomb_number--;
		for (int i = 0; i < 20; i++)
			if (item[i]->ifmove)
			{
				item[i]->value = 0;
				item[i]->setVisible(false);
				item[i]->setPosition(Vec2(1024, 768));
			}
		myhook->stopAllActions();
		float t = 1.0;
		myhook->runBack(t);
	}
}


void Stageone::explosion(int& pos)//炸药桶
{
	float x = item[pos]->getPositionX();
	float y = item[pos]->getPositionY();
	for (int j = 0; j < 20; j++)
		if (pow(x - item[j]->getPositionX(), 2) +
			pow(y - item[j]->getPositionY(), 2) <= pow(128, 2))
		{
			item[j]->setPosition(Vec2(1024, 768));
			item[j]->setVisible(false);//隐藏已经被抓取的物体
			item[j]->value = 0;
		}
}