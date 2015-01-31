/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-11
Description:º”‘ÿ≥°æ∞
**************************************************/
#ifndef __LOADINGSCENE__
#define __LOADINGSCENE__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "MenuScene.h"

class LoadingScene : public cocos2d::CCLayer
{
public:
	void runParticle();
	void enterGameScene();
	void LoadResource();
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* sender);
	CREATE_FUNC(LoadingScene);
};

#endif