#include"diZhuWin.h"

bool DiZhuWin::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bg = CCSprite::create("btn/text_dizhu_win");
	bg->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(bg);
	return true;
}