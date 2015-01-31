/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-18
Description:玩家卡牌界面
**************************************************/

#ifndef __PLAYERCARDLAYER__
#define __PLAYERCARDLAYER__

#include"cocos2d.h"
#include"list"
#include"GlobalData.h"
#include<vector>
#include<algorithm>
#include"LeftRobot.h"
#include"RightRobot.h"

using namespace cocos2d;

class PlayerLayer : public cocos2d::CCLayer
{
public:
	static PlayerLayer* sharedPlayerLayer();
	static PlayerLayer* g_sharedPlayerLayer;
	PlayerLayer();
	~PlayerLayer();
	virtual bool init();
	CREATE_FUNC(PlayerLayer);
	void getCard(int card[],int start,int end);
	void dealCard(CCObject* pSender);
	void buchuCard(CCObject* pSender);
	void drawCard();
	//处理第一次出牌
	void doTheFirstCard();
	//处理跟牌
	void followCard(std::vector<int > lastPlayerCard);
	//洗牌玩家手牌
	void shuffledCard();
	//洗刚出去的牌
	void shuffledPreCard();
	//设置按钮是否可见
	void setMenuVisble(bool flag);

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	bool Card_rule();
	bool Card_rule_follow();

	std::vector<int> getSavePreCard();
	void setIsDealCard(bool flag);
	bool getIsDealCard();
	void setBuChuButtonState(bool flag);
	bool getBuChuButtonState();
	int  getTotalCardNum();
	
	/*
	

	void setDealCard(bool flag);
	std::vector<int> getSavePreCard();

	int  getID();
	void setID(int num);
	void setWhoPlayFirstCard(int num);
	int getWhoPlayFirstCard();*/

private:
	//存放牌
	std::list<Card>           m_card;
	std::list<Card>           m_preCard;
	std::list<Card>::iterator m_it;
	//存放所有数字牌
	cocos2d::CCSpriteFrame*	  m_allNum[55];
	//显示牌
	cocos2d::CCSprite*        m_showNum[21];
	cocos2d::CCSize			  m_winSize;
	//显示玩家当前出的牌
	cocos2d::CCSprite*		  m_showLastCard[21];

	CCMenu*                   m_dealCardMenu;
	CCMenu*                   m_buchuMenu;
	CCSprite*                 m_buchu_image;
	CCSprite*                 m_deal_image;
	//存放出的牌上的数字
	std::vector<int >		  m_preCardInt;

	//触摸牌时所需类
	bool					  m_tempMoveVal[21];
	bool					  m_isSelect[21];
	
	std::vector<float >		  m_X;
	std::vector<float >		  m_moveX,m_moveY;
	std::vector<int >         m_savepreCardInt;
	
	//判断是跟牌 还是出首牌
	bool                      m_isFirst;

	//已经出牌了
	bool                      m_IsDealedCard;

	std::vector<int>          m_lastPlayerCard;

	bool                      m_buchuButtonIsDown;

	//
	//bool                      m_dealCard;

	////m_ID代表谁出牌  m_ID=1代表 玩家出第一手牌，m_ID=4代表玩家跟牌
	////
	////m_ID = 2 代表 右边电脑出第一手牌， m_ID=5代表右边电脑跟牌
	////m_ID = 3 代表 左边电脑出第一手牌， m_ID=6代表左边电脑跟牌
	//int                       m_ID;

	////经过一轮谁最大下一轮谁出牌  1,代表玩家出牌，2代表右边电脑出牌，3代表左边电脑出牌
	//int                       m_whoPlayFirstCard;

	////上一个玩家出的牌
	//std::vector<int >         m_lastDealCard;
};
#endif


