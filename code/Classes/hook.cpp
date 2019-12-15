#include "hook.h"
#include "math.h"
#include "One.h"

using namespace cocos2d;

Hook* Hook::create(const std::string& filename)//构造函数
{
	Hook *hook = new (std::nothrow) Hook();
	if (hook && hook->initWithFile(filename))
	{
		hook->autorelease();
		return hook;
	}
	CC_SAFE_DELETE(hook);
	return nullptr;
}


void Hook::runTargetAction()//钩子按指定方向移动
{
	float x = this->getPositionX();
	float y = this->getPositionY();
	if (x == 512.0f && y == 671.0f)
	{
		auto move = MoveTo::create(3, Vec2(x - 923 * sin(Angle*M_PI / 180),
			y - 923 * cos(Angle*M_PI / 180)));
		this->runAction(move);
	}
}

void Hook::runRotateAction()//钩子开始转动
{
	auto rotate1 = cocos2d::CCRotateTo::create(1.0f, -75);
	auto rotate2 = cocos2d::CCRotateTo::create(1.0f, 0);
	auto rotate3 = cocos2d::CCRotateTo::create(1.0f, 75);
	auto rotate4 = cocos2d::CCRotateTo::create(1.0f, 0);
	//创建序列将旋转动作加入
	auto action = cocos2d::Sequence::create(rotate1, rotate2, rotate3, rotate4, NULL);
	//序列无限重复
	repeatRotate = cocos2d::RepeatForever::create(action);
	this->runAction(repeatRotate);
}

void Hook::runBack(float& Backtime)//钩子返回
{	
	this->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto move = MoveTo::create(Backtime-0.1,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 + 287));
	this->runAction(move);
}

void Hook::stopRotate()//停止转动
{
	Angle = this->getRotation();
	this->stopAction(repeatRotate);
}

