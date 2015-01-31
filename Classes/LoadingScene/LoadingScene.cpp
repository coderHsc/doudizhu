/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:载入场景
**************************************************/
#include "LoadingScene.h"
USING_NS_CC;

CCScene* LoadingScene::scene()
{
	auto scene = CCScene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}
bool LoadingScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* sprite = CCSprite::create("btn/logo.png");
	//CCLOG("%f %f",visibleSize.width,visibleSize.height);
	sprite->setScaleY(size.height/sprite->getContentSize().height);
	sprite->setScaleX(size.width /sprite->getContentSize().width);
	sprite->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(sprite);

	//runParticle();

	//2秒后进入menuScene.
	this->LoadResource();
	sprite->runAction(CCSequence::create(CCDelayTime::create(2),CCCallFunc::create(this,callfunc_selector(LoadingScene::enterGameScene)),NULL));
	
	
	return true;
}
void LoadingScene::LoadResource()
{
	AudioEngine::sharedEngine();
}

void LoadingScene::enterGameScene()
{
	CCScene* pScene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, pScene));
}

