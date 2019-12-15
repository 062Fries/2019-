#pragma once
#ifndef __Grab__Object__H__
#define __Grab__Object__H__


#include "cocos2d.h"

using cocos2d::CCSprite;
class GrabObject : public CCSprite
{
public:
	short int value = 0;  
	short int breed = 0;
	bool ifmove = 0;
	short int radius = 0;
	float backtime = 1;
	short int boom = 0;


	static GrabObject* create(const std::string& filename);
	void init(short int gvalue, short int gbreed,short int gradius,float gbacktime);
	void initbag();
};


#endif // !__Grab__Object__H__