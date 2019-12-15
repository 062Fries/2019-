
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "One.h"
//#include "NameSpace.h"

USING_NS_CC;
extern short int stage_number;
Scene* Start::createScene()
{
	auto Stageonesence = Start::create();
	//Stageonesence->initWithPhysics();
    return Start::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}



// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
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
                                           CC_CALLBACK_1(Start::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	//auto txtsprite = Sprite::create("goldminertxt.png");
	//if (txtsprite == nullptr)
	//{
	//	problemLoading("'goldminertxt.png'");
	//}
	//else
	//{
		// position the sprite on the center of the screen
	//	txtsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 198));

		// add the sprite as a child to this layer
	//	this->addChild(txtsprite, 2);
	//}
	//加入矿工人物图片
	auto minersprite = Sprite::create("miner.png");
	if (minersprite == nullptr)
	{
		problemLoading("'miner.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		minersprite->setPosition(Vec2(visibleSize.width / 2+200, visibleSize.height / 2 - 70));

		// add the sprite as a child to this layer
		this->addChild(minersprite, 1);
	}
	//加入金块图片
	auto goldsprite = Sprite::create("menugold.png");
	if (goldsprite == nullptr)
	{
		problemLoading("'menugold.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		goldsprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 250));

		// add the sprite as a child to this layer
		this->addChild(goldsprite, 1);
	}

    // 加入主背景
    auto sprite = Sprite::create("mainscene.png");
    if (sprite == nullptr)
    {
        problemLoading("'mainscene.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-148));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	//加入背景
	auto skysprite = Sprite::create("mainscenes.png");
	if (skysprite == nullptr)
	{
		problemLoading("'mainscenes.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		skysprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+350));

		// add the sprite as a child to this layer
		this->addChild(skysprite, 0);
	}
	//加入切换场景的Label
	auto label = Label::createWithSystemFont("START", "fonts/arial.ttf", 50);//创建一个标签																							  //菜单条目的创建有多种，之前的HelloWorld.cpp中实现的是图片菜单条目(MenuItemImage)，即根据图片来创建菜单条目
																								  //这里是根据标签来创建菜单条目,然后设置回调函数
	auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(Start::EnterSecondScene, this));
	//创建好了菜单条目，就需要加入菜单中，所以下面就是创建菜单
	auto menu_start = Menu::create(menuitem, NULL);
	//把菜单添加到MyFirstScene层中
	menu_start->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	this->addChild(menu_start,1);
	label->setTextColor(Color4B(0, 0, 0, 255));

    return true;
}


void Start::menuCloseCallback(Ref* pSender)
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

void Start::EnterSecondScene(Ref *pSender)
{
	stage_number++;
	Director::getInstance()->replaceScene(Stageone::createScene());
}
