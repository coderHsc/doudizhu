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
#include"GlobalData.h"
#include"LeftRobot.h"
#include"PlayerLayer.h"
#include"ShowCardNumLayer.h"

class RightRoBot:public cocos2d::CCLayer
{
public:
	~RightRoBot();
	RightRoBot();
	virtual bool init();
	CREATE_FUNC(RightRoBot);
	//处理第一次出牌
	void doTheFirstCard(float dt);
	//处理跟牌
	void followCard(float dt,std::vector<int> lastPlayerCard);

	void getCard(int card[],int start,int end);
	void showLastCard();
	static RightRoBot* sharedRightRoBot();
	static RightRoBot* g_sharedRightRoBot;
	void drawCard();
	void findCard();
	void setIsDealCard(bool flag);
	bool getIsDealCard();
	std::vector<int> getSavePreCard();


	//找出最好的第一次出牌策略
	void findBestFirstCard();
	
	int  getTotalCardNum();

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
	std::vector<int >                   m_lastPlayerCard;
	//
	std::vector<int >                   m_savepreCardInt;

	std::vector<int >                   m_tempVector;

	ShowCardNumLayer*                   m_ShowCardNumLayer;

	bool                                m_IsDealedCard;

	CCSprite*                           m_buchuImage;

	
};

#endif
