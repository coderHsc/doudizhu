/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-19
Description:右边电脑
**************************************************/

#ifndef __RIGHTROBOT__
#define __RIGHTROBOT__


#include"cocos2d.h"
#include"list"
#include"GlobalData/GlobalData.h"
#include "SingleGame/LeftRobot.h"
#include "SingleGame/PlayerCardLayer.h"
#include"SingleGame/ShowCardNumLayer.h"

class RightRoBot:public cocos2d::CCLayer
{
public:
	~RightRoBot();
	RightRoBot();
	virtual bool init();
	CREATE_FUNC(RightRoBot);
	void update(float dt);
	void getCard(int card[],int start,int end);
	void showLastCard();
	static RightRoBot* sharedRightRoBot();
	static RightRoBot* g_sharedRightRoBot;
	void drawCard();
	void findCard();
	void setVis(bool flag);
	std::vector<int> getSavePreCard();
private:
	std::list<Card>						m_card;
	std::list<Card>::iterator           m_it,m_it2;

	std::list<Card>                     m_preCard;


	cocos2d::CCSize						m_winSize;
	cocos2d::CCSpriteFrame*             m_showCardBg;
	cocos2d::CCSprite*					m_showNum[21];
	//显示玩家当前出的牌
	cocos2d::CCSprite*					m_showLastCard[21];
	cocos2d::CCSpriteFrame*	            m_allNum[55];
	//上一个玩家出的牌
	std::vector<int >                   m_lastDealCard;
	//
	std::vector<int >                   m_savepreCardInt;
	bool                                m_vis;

	int                                 m_ID;

	ShowCardNumLayer*                   m_ShowCardNumLayer;
};

#endif
