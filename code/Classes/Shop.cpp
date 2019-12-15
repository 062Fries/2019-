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


#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Shop.h"
#include "One.h"
USING_NS_CC;
extern short int stage_number;
extern std::string socre;
short int bomb_number = 0;
bool ifStrength = false;
bool ifBook = false;
bool ifExpensive = false;
short int breed_item = 0;
short int strength_times = 1;
//1表示大力水,2表示炸弹,3表示钻石升值水,4表示石头收藏书
Label* label_tips;
Scene* _Shop::createScene()
{
    return _Shop::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool _Shop::init()
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
                                           CC_CALLBACK_1(_Shop::menuCloseCallback, this));

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

    auto label = Label::createWithTTF("Welcome to the Shop", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
	
	label_tips = Label::createWithTTF("You can choose it by clicking", "fonts/Marker Felt.ttf",40);
	label_tips->setPosition(Vec2(400, 400));
	this->addChild(label_tips,1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        sprite->setScale(1.5, 1.5);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    


    auto sprite1 = Sprite::create("shoper copy.png"); 
    sprite1->setPosition(Vec2(visibleSize.width*0.8,visibleSize.height*0.7));
    this->addChild(sprite1);
    
	
    auto button1 = cocos2d::ui::Button::create("huancun1 copy.png");
    button1->cocos2d::Node::setPosition(visibleSize.width*0.2,visibleSize.height*0.8);
    button1->setScale(1.5, 1.5);
	button1->addClickEventListener(CC_CALLBACK_1(_Shop::Event1, this));
	
    this->addChild(button1);


    auto button2 = cocos2d::ui::Button::create("huancun2 copy.png", 
		"selected_image.png", "disabled_image.png");
    button2->cocos2d::Node::setPosition(visibleSize.width * 0.1, visibleSize.height * 0.8);
    button2->setScale(1.5, 1.5);
	button2->addClickEventListener(CC_CALLBACK_1(_Shop::Event2, this));
    
    this->addChild(button2);


    auto button3 = cocos2d::ui::Button::create("huancun3 copy.png", 
		"selected_image.png", "disabled_image.png");
    button3->cocos2d::Node::setPosition(visibleSize.width * 0.3,visibleSize.height * 0.8);
    button3->setScale(1.5, 1.5);
	button3->addClickEventListener(CC_CALLBACK_1(_Shop::Event3, this));
    
    this->addChild(button3);


    auto button4 = cocos2d::ui::Button::create("huancun4 copy.png",
		"selected_image.png", "disabled_image.png");
    button4->cocos2d::Node::setPosition(visibleSize.width * 0.4, visibleSize.height * 0.8);
    button4->setScale(1.5, 1.5);
	button4->addClickEventListener(CC_CALLBACK_1(_Shop::Event4, this));
    
    this->addChild(button4);
	
    
	
	//加入切换场景的Label
	auto label_buy = Label::createWithSystemFont("Buy", "fonts/arial.ttf", 40);
	auto menuitem_buy = MenuItemLabel::create(label_buy,
		CC_CALLBACK_1(_Shop::Buy, this));
	auto menu_start_buy = Menu::create(menuitem_buy, NULL);
	//把菜单添加到MyFirstScene层中
	menu_start_buy->setPosition(Vec2(600, 100));
	this->addChild(menu_start_buy, 1);
	label_buy->setTextColor(Color4B(0, 0, 0, 255));

	auto label_next = Label::createWithSystemFont("Next", "fonts/arial.ttf", 40);//创建一个标签																							  //菜单条目的创建有多种，之前的HelloWorld.cpp中实现的是图片菜单条目(MenuItemImage)，即根据图片来创建菜单条目
																			 //这里是根据标签来创建菜单条目,然后设置回调函数
	auto menuitem_next = MenuItemLabel::create(label_next,
		CC_CALLBACK_1(_Shop::EnterSecondScene, this));
	//创建好了菜单条目，就需要加入菜单中，所以下面就是创建菜单
	auto menu_start_next = Menu::create(menuitem_next, NULL);
	//把菜单添加到MyFirstScene层中
	menu_start_next->setPosition(Vec2(600,200));
	this->addChild(menu_start_next, 1);
	label_next->setTextColor(Color4B(0, 0, 0, 255));
	
    return true;
}





void _Shop::menuCloseCallback(Ref* pSender)
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


void _Shop::EnterSecondScene(Ref *pSender)
{
	stage_number++;
	Director::getInstance()->replaceScene(Stageone::createScene());
}


void _Shop::Buy(Ref* pSender)
{
	if (breed_item == 1)
	{
		std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
		int i;
		is >> i; //从is流中读入一个int整数存入i中
		if (i >= 300)
		{
			ifStrength = true;
			strength_times = 2;
			i -= 300;
		}
		else
		{
			;
		}
		std::ostringstream os; //构造一个输出字符串流，流内容为空 
		os << i; //向输出字符串流中输出int整数i的内容 
		socre = os.str();
	}
	else
		if (breed_item == 2)
		{
			std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
			int i;
			is >> i; //从is流中读入一个int整数存入i中
			if (i >= 250)
			{
				bomb_number++;
				i -= 250;
			}
			else
			{
				;
			}
			std::ostringstream os; //构造一个输出字符串流，流内容为空 
			os << i; //向输出字符串流中输出int整数i的内容 
			socre = os.str();
		}
		else
			if (breed_item == 3)
			{
				std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
				int i;
				is >> i; //从is流中读入一个int整数存入i中
				if (i >= 400)
				{
					ifExpensive = true;
					
					i -= 400;
				}
				else
				{
					;
				}
				std::ostringstream os; //构造一个输出字符串流，流内容为空 
				os << i; //向输出字符串流中输出int整数i的内容 
				socre = os.str();
			}
			else
				if (breed_item == 4)
				{
					std::istringstream is(socre); //构造输入字符串流，流的内容初始化为“12”的字符串 
					int i;
					is >> i; //从is流中读入一个int整数存入i中
					if (i >= 100)
					{
						ifBook = true;
						i -= 100;
					}
					else
					{
						;
					}
					std::ostringstream os; //构造一个输出字符串流，流内容为空 
					os << i; //向输出字符串流中输出int整数i的内容 
					socre = os.str();
				}
				else
					;
	label_tips->setString("Complete!");
}

void _Shop::Event1(Ref* pSender)
{
	breed_item = 1;
	label_tips->setString("$300\nYou are supposed to strengthen your power\nthe speed will enhance two times");
}

void _Shop::Event2(Ref* pSender)
{
	breed_item = 2;
	label_tips->setString("$250\nYou will get a bomb\nBy using it you can destroy an item");
}

void _Shop::Event3(Ref* pSender)
{
	breed_item = 3;
	label_tips->setString("$400\nYou can enhance diamond`s value by buying it\nthe diamond`s value will enhance 1.5 times");
}

void _Shop::Event4(Ref* pSender)
{
	breed_item = 4;
	label_tips->setString("$100\nYou can enhance stone`s value by buying it\nthe stone`s value will enhance 5 times");
}
