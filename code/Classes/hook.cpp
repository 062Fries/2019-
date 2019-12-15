#include "hook.h"
#include "math.h"
#include "One.h"

using namespace cocos2d;

Hook* Hook::create(const std::string& filename)//���캯��
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


void Hook::runTargetAction()//���Ӱ�ָ�������ƶ�
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

void Hook::runRotateAction()//���ӿ�ʼת��
{
	auto rotate1 = cocos2d::CCRotateTo::create(1.0f, -75);
	auto rotate2 = cocos2d::CCRotateTo::create(1.0f, 0);
	auto rotate3 = cocos2d::CCRotateTo::create(1.0f, 75);
	auto rotate4 = cocos2d::CCRotateTo::create(1.0f, 0);
	//�������н���ת��������
	auto action = cocos2d::Sequence::create(rotate1, rotate2, rotate3, rotate4, NULL);
	//���������ظ�
	repeatRotate = cocos2d::RepeatForever::create(action);
	this->runAction(repeatRotate);
}

void Hook::runBack(float& Backtime)//���ӷ���
{	
	this->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto move = MoveTo::create(Backtime-0.1,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 + 287));
	this->runAction(move);
}

void Hook::stopRotate()//ֹͣת��
{
	Angle = this->getRotation();
	this->stopAction(repeatRotate);
}

