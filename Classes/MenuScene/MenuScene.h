/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:Ö÷½çÃæ
**************************************************/
#ifndef __MENUSCENE__
#define __MENUSCENE__
#include "cocos2d.h"


class MenuScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene *scene();
	void singleGameCallBack(CCObject* pSender);
	void quitCallBack(CCObject* pSender);
	CREATE_FUNC(MenuScene);
};

#endif  
