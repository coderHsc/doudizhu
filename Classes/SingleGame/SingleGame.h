/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:������Ϸ����
**************************************************/

#ifndef __SINGLEGAME__
#define __SINGLEGAME__
#include"cocos2d.h"
#include"PlayerLayer.h"
#include"LeftRobot.h"
#include"RightRobot.h"
#include"MenuScene.h"

//��������Ϸ������״̬��������״̬
enum{
	//����״γ��Ƶ�״̬
	First_Card_Player,
	//��ߵ����״γ��Ƶ�״̬
	First_Card_LeftRobot,
	//�ұߵ����״γ��Ƶ�״̬
	First_Card_RightRobot,
	//��Ҹ���״̬
	Follow_Card_Player,
	//��߸���״̬
	Follow_Card_LeftRobot,
	//�ұ߸���״̬
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
	//ϴ��
	void shuffled();
	void update(float dt);
	void setCurState(int state);
	void back(CCObject* pSender);
private:
	PlayerLayer*       m_playerLayer;
	LeftRobot*         m_leftAILayer;
	RightRoBot*        m_rightAILayer;

	int m_card[55];
	//��ǰ״̬
	int m_CurState;
	//��¼һ����Ϸ�����ӵ�һ�����ƿ�ʼ��m_cnt1=2��ÿ��һ����m_cn1-=1��
	int m_Cnt1;
	//��¼һ����Ϸ�У��м�����Ҹ����ˡ�
	int m_Cnt2;
	//��һ��˭�ȳ���
	int m_Next_First_Player;
	//����һ������������

	std::vector<int>   m_MaxCard;
	//˭�ǵ���
	int                m_whoIsRichMan;


	CCSprite *         m_dizhuWin;
	CCSprite *         m_nongmingWin;


	CCMenu*                   m_backMenu;
	CCSprite*                 m_backImage;
	//CCSprite*                 m_back_image;

	
};
#endif


