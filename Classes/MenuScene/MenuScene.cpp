/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:������
**************************************************/
#include"MenuScene.h"
#include"AudioEngine.h"
#include"SingleGame.h"

USING_NS_CC;

cocos2d::CCScene * MenuScene::scene()
{
	CCScene* scene = CCScene::create();
	CCLayer* menuScene = MenuScene::create();
	scene->addChild(menuScene);
	return scene;
}
bool MenuScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	//���ű�������
	AudioEngine::sharedEngine()->playBackgroundMusic("sounds/0.mp3",true);
	//��ȡ���ڴ�С
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//��������
	CCSprite* sprite = CCSprite::create("btn/menubg1.png");
	//�ñ����Ĵ�С�봰��һ��
	sprite->setScaleX(winSize.width/sprite->getContentSize().width);
	sprite->setScaleY(winSize.height/sprite->getContentSize().height);
	//λ��
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	//�Ѿ�����ӽ�������
	this->addChild(sprite);
	
	//////////////////////////////////////////////////////////
	//����ģʽ
	CCMenuItemImage* singleGame = CCMenuItemImage::create(
		"btn/startbtn_normal.png",
		"btn/startbtn_touched.png",
		this,
		menu_selector(MenuScene::singleGameCallBack));

	singleGame->setScaleY((winSize.height/singleGame->getContentSize().height*0.15));
	singleGame->setScaleX((winSize.width /singleGame->getContentSize().width)*0.15);
	

	CCMenu* pMenu1 = CCMenu::create(singleGame,NULL);
	pMenu1->setPosition(ccp(winSize.width/2,winSize.height/2));
	
	this->addChild(pMenu1, 2);

	CCSprite* start = CCSprite::create("btn/text_start.png");

	start->setScaleX(winSize.width/start->getContentSize().width*0.1);
	start->setScaleY(winSize.height/start->getContentSize().height*0.07);
	start->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(start,3);
	
	//////////////////////////////////////////////////////////
	//�˳�
	CCMenuItemImage* quit = CCMenuItemImage::create(
		"btn/startbtn_normal.png",
		"btn/startbtn_touched.png",
		this,
		menu_selector(MenuScene::quitCallBack));

	quit->setScaleY((winSize.height/quit->getContentSize().height*0.15));
	quit->setScaleX((winSize.width /quit->getContentSize().width)*0.15);


	CCMenu* pMenu2 = CCMenu::create(quit,NULL);
	pMenu2->setPosition(ccp(winSize.width/2,winSize.height/2*0.5));

	this->addChild(pMenu2, 2);

	CCSprite* quitImage = CCSprite::create("btn/quit.png");

	quitImage->setScaleX(winSize.width/quitImage->getContentSize().width*0.1);
	quitImage->setScaleY(winSize.height/quitImage->getContentSize().height*0.07);
	quitImage->setPosition(ccp(winSize.width/2,winSize.height/2*0.5));
	this->addChild(quitImage,3);

	//auto audioEngine=AudioEngine::getInstance();
	//audioEngine->playEffect("sounds/1000.ogg");

	
	return true;
}

void MenuScene::singleGameCallBack(CCObject* pSender)
{
	//AudioEngine::sharedEngine()->playEffect("sound/buttonsound1.mp3");
	CCScene* pScene = SingleGame::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,pScene));
}

void MenuScene::quitCallBack( CCObject* pSender )
{
	CCDirector::sharedDirector()->end();
}

