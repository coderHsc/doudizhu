/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-18
Description:��ҿ��ƽ���
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

	//��ʾ��ҵ�ǰ������
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

	//m_ID����˭����  m_ID=1���� ��ҳ���һ���ƣ�m_ID=4������Ҹ���
	//
	//m_ID = 2 ���� �ұߵ��Գ���һ���ƣ� m_ID=5�����ұߵ��Ը���
	//m_ID = 3 ���� ��ߵ��Գ���һ���ƣ� m_ID=6������ߵ��Ը���
	int                       m_ID;

	//����һ��˭�����һ��˭����  1,������ҳ��ƣ�2�����ұߵ��Գ��ƣ�3������ߵ��Գ���
	int                       m_whoPlayFirstCard;

	//��һ����ҳ�����
	std::vector<int >         m_lastDealCard;
	



};
#endif


