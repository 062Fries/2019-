#pragma once
#ifndef __Hook__H__
#define __Hook__H__

#include "cocos2d.h"

using cocos2d::CCSprite;
//Hook����Sprite������
class Hook : public CCSprite
{
private:
	cocos2d::RepeatForever* repeatRotate; //��ת����,����stopRotate()����
	float Angle;//����ֹͣʱ�ĽǶ�
	//cocos2d::MoveTo* move;
	
public:
	bool Catch = false;
	//���캯��
	static Hook* create(const std::string& filename);
	//����Ƿ�ץȡ������
	//bool isCatch(bool i);
	
	void stopRotate();
	//��������󷵻�
	void runBack(float& Backtime);

	void runTargetAction();
	//�������ذڶ�����
	void runRotateAction();
	//
	//void stopRun();
};
#endif // !__Hook__H__

