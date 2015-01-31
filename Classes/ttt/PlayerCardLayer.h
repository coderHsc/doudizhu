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
#include"GlobalData/GlobalData.h"
#include<vector>
#include<algorithm>
#include"SingleGame/LeftRobot.h"
#include"SingleGame/RightRobot.h"

using namespace cocos2d;
class PlayerCardLayer : public cocos2d::CCLayer
{
public:
	static PlayerCardLayer* sharedPlayerCardLayer();
	static PlayerCardLayer* g_sharedPlayerCardLayer;
	PlayerCardLayer();
	~PlayerCardLayer();
	virtual bool init();
	CREATE_FUNC(PlayerCardLayer);
	void getCard(int card[],int start,int end);
	void drawCard();
	void update(float dt);

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	
	void dealCard(CCObject* pSender);
	void buchuCard(CCObject* pSender);

	void shuffledCard();
	void shuffledPreCard();
	bool Card_rule();


	void setDealCard(bool flag);
	std::vector<int> getSavePreCard();

	int  getID();
	void setID(int num);
	void setWhoPlayFirstCard(int num);
	int getWhoPlayFirstCard();

private:
	std::list<Card>           m_card;
	std::list<Card>           m_preCard;
	std::list<Card>::iterator m_it;

	cocos2d::CCSpriteFrame*	  m_allNum[55];
	cocos2d::CCSprite*        m_showNum[21];

	//显示玩家当前出的牌
	cocos2d::CCSprite*		  m_showLastCard[21];
	
	cocos2d::CCSize			  m_winSize;

	bool					  m_tempMoveVal[21];
	bool					  m_isSelect[21];
	std::vector<float >		  m_X;
	std::vector<float >		  m_moveX,m_moveY;
	std::vector<int >		  m_preCardInt;
	std::vector<int >         m_savepreCardInt;

	CCMenu*                   m_dealCardMenu;
	CCMenu*                   m_buchuMenu;
	CCSprite*                 m_buchu_image;
	CCSprite*                 m_deal_image;
	//
	bool                      m_dealCard;

	//m_ID代表谁出牌  m_ID=1代表 玩家出第一手牌，m_ID=4代表玩家跟牌
	//
	//m_ID = 2 代表 右边电脑出第一手牌， m_ID=5代表右边电脑跟牌
	//m_ID = 3 代表 左边电脑出第一手牌， m_ID=6代表左边电脑跟牌
	int                       m_ID;

	//经过一轮谁最大下一轮谁出牌  1,代表玩家出牌，2代表右边电脑出牌，3代表左边电脑出牌
	int                       m_whoPlayFirstCard;

	//上一个玩家出的牌
	std::vector<int >         m_lastDealCard;
	



};
#endif


