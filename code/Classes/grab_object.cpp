#include "grab_objects.h"
#include <iostream>
#include<cstdlib>
#include<ctime>
GrabObject* GrabObject::create(const std::string& filename)//���캯��
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

void GrabObject::init(short int gvalue,short int gbreed,  //��ʼ��ץȡ�������
	short int gradius,float gbacktime)
{
	value = gvalue;
	breed = gbreed;
	radius = gradius;
	backtime = gbacktime;
}
 
void GrabObject::initbag()  //����ʺŴ��ӵ�����
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
			breed = 5;    //��ʾ��������ը��
		}
		else
			if (t == 9)
			{
				breed = 6;   //��ʾ�������Ǵ���ˮ
			}
		value = 0;
	}
	backtime = rand() % 9 + 3;
	radius = 32;
}