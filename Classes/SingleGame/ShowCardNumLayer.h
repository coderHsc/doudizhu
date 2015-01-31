/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-4-20
Description:Êä³öÊ£Óà¸öÊý
**************************************************/
#ifndef __SHOWCARDNUMLAYER__
#define __SHOWCARDNUMLAYER__

#include "cocos2d.h"
using namespace cocos2d;
class ShowCardNumLayer:public cocos2d::CCLayer
{
public:
	CREATE_FUNC(ShowCardNumLayer);

	virtual bool init(); 
	void    coutNum(int total);
	void    setStartPosition(float dt);

	ShowCardNumLayer();
	~ShowCardNumLayer();
private:
	cocos2d::CCSpriteFrame*  m_Num[12];
	cocos2d::CCSprite*       m_showNum[2];
};

#endif