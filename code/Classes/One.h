#pragma once
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

#ifndef __Stageone_SCENE_H__
#define __Stageone_SCENE_H__

#include "cocos2d.h"
#include "hook.h"


class Stageone : public cocos2d::Scene
{
public:
	bool isRunback = false;

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	bool runTarget(Ref* pSender,Hook* phook,cocos2d::Sprite* psprite);
	//钩子收回函数
	//void runBack_Control();
	//拿回金矿

	void update(float dt);

	void timeReduce(float dt);

	void checkTime(float dt);

	void toShop(cocos2d::Ref* pSender);

	void explode(Ref* pSender);

	void explosion(int& pos);

	void inititem();

	// implement the "static create()" method manually
	CREATE_FUNC(Stageone);
};


#endif // __HELLOWORLD_SCENE_H__

