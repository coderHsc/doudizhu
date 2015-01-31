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
#include"GlobalData.h"
#include"RightRobot.h"
#include"PlayerLayer.h"
#include"ShowCardNumLayer.h"

class LeftRobot:public cocos2d::CCLayer
{
public:
	LeftRobot();
	~LeftRobot();
	virtual bool init();
	CREATE_FUNC(LeftRobot);
	//�����һ�γ���
	void doTheFirstCard(float dt);
	//�������
	void followCard(float dt,std::vector<int > lastPlayerCard);

	//void update(float dt);
	void getCard(int card[],int start,int end);
	void showLastCard();
	static LeftRobot* sharedLeftRobot();
	static LeftRobot* g_sharedLeftRobot;
	void drawCard();
	void findCard();
	std::vector<int> getSavePreCard();

	void setIsDealCard(bool flag);
	bool getIsDealCard();

	//�ҳ���õĵ�һ�γ��Ʋ���
	void findBestFirstCard();
	int  getTotalCardNum();
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

	
	std::vector<int >                   m_savepreCardInt;
	//��һ����ҳ�����
	std::vector<int >                   m_lastPlayerCard;
	std::vector<int >                   m_tempVector;

	ShowCardNumLayer*                   m_ShowCardNumLayer;

	bool                                m_IsDealedCard; 

	CCSprite*                           m_buchuImage;
};

#endif
