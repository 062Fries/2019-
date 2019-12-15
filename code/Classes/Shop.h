

#ifndef __Shop_SCENE_H__
#define __Shop_SCENE_H__

#include "cocos2d.h"

class _Shop : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void EnterSecondScene(Ref* pSender);

	void Buy(Ref* pSender);
    // implement the "static create()" method manually

	void Event1(Ref* pSender);

	void Event2(Ref* pSender);

	void Event3(Ref* pSender);

	void Event4(Ref* pSender);

    CREATE_FUNC(_Shop);
};

#endif // __Shop_SCENE_H__
