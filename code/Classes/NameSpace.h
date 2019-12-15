#pragma once
#ifndef __NAme__H__
#define __NAme__H__

#include "hook.h"
#include "cocos2d.h"
#include "grab_objects.h"
#include <iostream>
#include <string.h>

using cocos2d::Sprite;
namespace Items
{
	static Hook* myhook;
	static GrabObject* item[20];
	static cocos2d::Label* Socre;
	//static std::string socre = "0";
	static cocos2d::Label* Times;
	static cocos2d::Sprite* miner_Action;
	static cocos2d::Animate* mAnimate;
	static int times = 60;
	static bool isChange = false;
	int target_socre = 700;
	static cocos2d::Label* goalSocre;
	static cocos2d::Label* numberBomb;
	//static short int stage_number = 0;
}

#endif // !__NAme__H__

