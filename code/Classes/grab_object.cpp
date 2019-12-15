#include "grab_objects.h"
#include <iostream>
#include<cstdlib>
#include<ctime>
GrabObject* GrabObject::create(const std::string& filename)//构造函数
{
	GrabObject *grabObject = new (std::nothrow) GrabObject();
	if (grabObject && grabObject->initWithFile(filename))
	{
		grabObject->autorelease();
		return grabObject;
	}
	CC_SAFE_DELETE(grabObject);
	return nullptr;
}

void GrabObject::init(short int gvalue,short int gbreed,  //初始化抓取物的属性
	short int gradius,float gbacktime)
{
	value = gvalue;
	breed = gbreed;
	radius = gradius;
	backtime = gbacktime;
}
 
void GrabObject::initbag()  //随机问号袋子的属性
{
	srand((unsigned)time(NULL));
	int t = rand() % 10; 
	if (t < 8)
	{
		value = rand() % 990 + 10;
	}
	else
	{
		if (t == 8)
		{
			breed = 5;    //表示袋子中是炸弹
		}
		else
			if (t == 9)
			{
				breed = 6;   //表示袋子中是大力水
			}
		value = 0;
	}
	backtime = rand() % 9 + 3;
	radius = 32;
}