/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-19
Description:��ߵ���
**************************************************/

#ifndef __LEFTROBOT__
#define __LEFTROBOT__


#include"cocos2d.h"
#include"list"
#include"GlobalData/GlobalData.h"
#include"SingleGame/RightRobot.h"
#include"SingleGame/PlayerCardLayer.h"
#include"SingleGame/ShowCardNumLayer.h"

class LeftRobot:public cocos2d::CCLayer
{
public:
	LeftRobot();
	~LeftRobot();
	virtual bool init();
	CREATE_FUNC(LeftRobot);
	void update(float dt);
	void getCard(int card[],int start,int end);
	void showLastCard();
	static LeftRobot* sharedLeftRobot();
	static LeftRobot* g_sharedLeftRobot;
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

	//��ʾ��ҵ�ǰ������
	cocos2d::CCSprite*					m_showLastCard[21];
	cocos2d::CCSpriteFrame*	            m_allNum[55];

	//��һ����ҳ�����
	std::vector<int >                   m_lastDealCard;
	std::vector<int >                   m_savepreCardInt;
	bool                                m_vis;
	int                                 m_ID;

	ShowCardNumLayer*                   m_ShowCardNumLayer;
};

#endif
