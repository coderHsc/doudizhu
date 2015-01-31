/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:单机游戏界面
**************************************************/

#ifndef __SINGLEGAME__
#define __SINGLEGAME__
#include"cocos2d.h"
#include"PlayerLayer.h"
#include"LeftRobot.h"
#include"RightRobot.h"
#include"MenuScene.h"

//斗地主游戏，有限状态机的所有状态
enum{
	//玩家首次出牌的状态
	First_Card_Player,
	//左边电脑首次出牌的状态
	First_Card_LeftRobot,
	//右边电脑首次出牌的状态
	First_Card_RightRobot,
	//玩家跟牌状态
	Follow_Card_Player,
	//左边跟牌状态
	Follow_Card_LeftRobot,
	//右边跟牌状态
	Follow_Card_RightRobot
};

//#ifdef WIN32
//#define CCSleep(t)  Sleep(t)
//#elif defined (IOS || ANDROID )
//#define CCSleep(t)  USleep(t)
//#endif

class SingleGame : public cocos2d::CCLayer
{
public:
	static SingleGame* sharedSingleGame();
	static SingleGame* g_sharedSingleGame;
	virtual bool init();
	static cocos2d::CCScene *scene();
	CREATE_FUNC(SingleGame);
	//洗牌
	void shuffled();
	void update(float dt);
	void setCurState(int state);
	void back(CCObject* pSender);
private:
	PlayerLayer*       m_playerLayer;
	LeftRobot*         m_leftAILayer;
	RightRoBot*        m_rightAILayer;

	int m_card[55];
	//当前状态
	int m_CurState;
	//记录一轮游戏，当从第一个出牌开始，m_cnt1=2。每跟一次牌m_cn1-=1；
	int m_Cnt1;
	//记录一轮游戏中，有几个玩家跟牌了。
	int m_Cnt2;
	//下一轮谁先出牌
	int m_Next_First_Player;
	//保存一轮牌中最大的牌

	std::vector<int>   m_MaxCard;
	//谁是地主
	int                m_whoIsRichMan;


	CCSprite *         m_dizhuWin;
	CCSprite *         m_nongmingWin;


	CCMenu*                   m_backMenu;
	CCSprite*                 m_backImage;
	//CCSprite*                 m_back_image;

	
};
#endif


