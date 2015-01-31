/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-19
Description:电脑卡牌
**************************************************/

#ifndef __AICARDLAYER__
#define __AICARDLAYER__


#include"cocos2d.h"
#include"list"
#include"GlobalData/GlobalData.h"


class AICardLayer:public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(AICardLayer);
	void setIsLeft(bool flag);
	void update(float dt);
	void getCard(int card[],int start,int end);
	void showLastCard();

private:
	bool                                m_isleft;
	std::list<Card>						m_card;
	std::list<Card>::iterator           m_it;
	cocos2d::CCSize						m_winSize;
	cocos2d::CCSpriteFrame*               m_showCardBg;
	cocos2d::CCSprite*					m_showNum[21];
	//显示玩家当前出的牌
	cocos2d::CCSprite*					m_showLastCard[21];


};

#endif
