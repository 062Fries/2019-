#pragma once
#ifndef __Hook__H__
#define __Hook__H__

#include "cocos2d.h"

using cocos2d::CCSprite;
//Hook类是Sprite的子类
class Hook : public CCSprite
{
private:
	cocos2d::RepeatForever* repeatRotate; //旋转序列,方便stopRotate()调用
	float Angle;//钩子停止时的角度
	//cocos2d::MoveTo* move;
	
public:
	bool Catch = false;
	//构造函数
	static Hook* create(const std::string& filename);
	//检测是否抓取到物体
	//bool isCatch(bool i);
	
	void stopRotate();
	//钩子伸出后返回
	void runBack(float& Backtime);

	void runTargetAction();
	//钩子来回摆动函数
	void runRotateAction();
	//
	//void stopRun();
};
#endif // !__Hook__H__

