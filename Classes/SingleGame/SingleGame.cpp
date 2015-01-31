/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-17
Description:单机游戏界面
**************************************************/
#include "SingleGame.h"
USING_NS_CC;

SingleGame* SingleGame::sharedSingleGame()
{
	if(g_sharedSingleGame==NULL)
	{
		g_sharedSingleGame = SingleGame::create();
	}
	return g_sharedSingleGame;
}

SingleGame* SingleGame::g_sharedSingleGame=NULL;

cocos2d::CCScene * SingleGame::scene()
{
	auto scene = CCScene::create();
	auto singleGame = SingleGame::sharedSingleGame();
	scene->addChild(singleGame);

	return scene;


}

bool SingleGame::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	//背景
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* sprite = CCSprite::create("btn/bg1.png");
	sprite->setScaleX(winSize.width/sprite->getContentSize().width);
	sprite->setScaleY(winSize.height/sprite->getContentSize().height);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2) );
	this->addChild(sprite);

	//地主胜利
	m_dizhuWin = CCSprite::create("btn/text_dizhu_win.png");
	m_dizhuWin->setScaleX(winSize.width/m_dizhuWin->getContentSize().width*0.3);
	m_dizhuWin->setScaleY(winSize.height/m_dizhuWin->getContentSize().height*0.3);
	m_dizhuWin->setPosition(ccp(winSize.width/2,winSize.height/2));
	m_dizhuWin->setVisible(false);
	this->addChild(m_dizhuWin,3);
	//农民胜利
	m_nongmingWin = CCSprite::create("btn/text_nongmin_win.png");
	m_nongmingWin->setScaleX(winSize.width/m_nongmingWin->getContentSize().width*0.3);
	m_nongmingWin->setScaleY(winSize.height/m_nongmingWin->getContentSize().height*0.3);
	m_nongmingWin->setPosition(ccp(winSize.width/2,winSize.height/2));
	m_nongmingWin->setVisible(false);
	this->addChild(m_nongmingWin,3);
	//////////////////////////////////////////////////////////////////////////////////
	//添加发牌按钮
	CCMenuItemImage* back = CCMenuItemImage::create(
		"btn/startbtn_normal.png",
		"btn/startbtn_touched.png",
		this,
		menu_selector(SingleGame::back));
	back->setScaleY((winSize.height/back->getContentSize().height*0.1));
	back->setScaleX((winSize.width /back->getContentSize().width)*0.1);
	m_backMenu = CCMenu::create(back,NULL);
	m_backMenu->setPosition(ccp(winSize.width / 2,winSize.height*0.7));
	m_backMenu->setVisible(false);
	this->addChild(m_backMenu, 2);
	m_backImage = CCSprite::create("btn/back.png");
	

	m_backImage->setScaleY((winSize.height/m_backImage->getContentSize().height*0.05));
	m_backImage->setScaleX((winSize.width /m_backImage->getContentSize().width)*0.05);
	m_backImage->setPosition(ccp(winSize.width / 2,winSize.height*0.7));
	m_backImage->setVisible(false);
	this->addChild(m_backImage,3);

	//玩家类
	/////////////////////////////////////////////////////////////////////////
	m_playerLayer = PlayerLayer::sharedPlayerLayer();
	this->addChild(m_playerLayer);
	////////////////////////////////////////////////////////////
	m_leftAILayer = LeftRobot::sharedLeftRobot();
	this->addChild(m_leftAILayer);
	////////////////////////////////////////////////////////////////
	m_rightAILayer=RightRoBot::sharedRightRoBot();
	this->addChild(m_rightAILayer);

	shuffled();
	//给玩家发牌
	m_playerLayer->getCard(m_card,1,17);
	m_leftAILayer->getCard(m_card,18,34);
	m_rightAILayer->getCard(m_card,35,51);


	//随机产生地主
	srand((unsigned)time(NULL));
	m_whoIsRichMan = rand()%3+1;

	if(m_whoIsRichMan==1)
	{
		m_CurState = First_Card_Player;
		m_playerLayer->getCard(m_card,52,54);
	}
	else if(m_whoIsRichMan==2)
	{
		m_CurState = First_Card_LeftRobot;
		m_leftAILayer->getCard(m_card,52,54);
	}
	else
	{
		m_CurState = First_Card_RightRobot;
		m_rightAILayer->getCard(m_card,52,54);
	}

	//开始更新
	this->scheduleUpdate();
	return true;

}
//洗牌
void SingleGame::shuffled()
{
	for(int i=1;i<=54;i++) m_card[i]=i;
	//获取随机种子
	srand((unsigned)time(NULL));
	for(int i=1;i<=1000;i++)
	{
		int rand1 = rand()%54+1;
		int rand2 = rand()%54+1;
		int t=m_card[rand1];
		m_card[rand1]=m_card[rand2];
		m_card[rand2]=t;
	}
	//m_card[1]=3;m_card[2]=13+3;m_card[3]=26+3;
	//m_card[4]=4;m_card[5]=13+4;m_card[6]=26+4;
	//for(int i=1;i<=52;i++) CCLOG("%d\n",card[i]);
}
void SingleGame::update(float dt)
{	
	int total1=m_playerLayer->getTotalCardNum();
	int total2=m_leftAILayer->getTotalCardNum();
	int total3=m_rightAILayer->getTotalCardNum();
	//判断是否结束游戏。
	if((total1==0)||(total2==0)||(total3==0))
	{
		if((m_whoIsRichMan==1&&total1==0)||(m_whoIsRichMan==2&&total2==0)||(m_whoIsRichMan==3&&total3==0)   )
		{
			m_playerLayer->setMenuVisble(false);
			m_backMenu->setVisible(true);
			m_backImage->setVisible(true);
			m_dizhuWin->setVisible(true);
		}
		else
		{
			m_playerLayer->setMenuVisble(false);
			m_backMenu->setVisible(true);
			m_backImage->setVisible(true);
			m_nongmingWin->setVisible(true);
		}
	}
	else
	{
		//有限状态机的实现
		switch (m_CurState)
		{
		case First_Card_Player:
			{
				//
				m_playerLayer->doTheFirstCard();
				//查看玩家是否已经出牌了
				bool flag = m_playerLayer->getIsDealCard();
				//玩家出完，右边电脑出牌
				if(flag)
				{
					m_CurState = Follow_Card_RightRobot;
					//获取玩家出的牌
					m_MaxCard.clear();
					m_MaxCard= m_playerLayer->getSavePreCard();
					m_rightAILayer->setIsDealCard(false);
				}
				m_playerLayer->setBuChuButtonState(false);
			}
			break;
		case First_Card_LeftRobot:
			{
				m_leftAILayer->doTheFirstCard(dt);

				//查看电脑是否已经出牌了
				bool flag = m_leftAILayer->getIsDealCard();
				//玩家出完，右边电脑出牌
				if(flag)
				{
					m_CurState = Follow_Card_Player;
					//获取玩家出的牌
					m_MaxCard.clear();
					m_MaxCard= m_leftAILayer->getSavePreCard();

					m_playerLayer->setIsDealCard(false);
				}
			}
			break;
		case First_Card_RightRobot:
			{
				m_rightAILayer->doTheFirstCard(dt);

				//查看电脑是否已经出牌了
				bool flag = m_rightAILayer->getIsDealCard();
				//玩家出完，右边电脑出牌
				if(flag)
				{
					m_CurState = Follow_Card_LeftRobot;
					//获取玩家出的牌
					m_MaxCard.clear();
					m_MaxCard= m_rightAILayer->getSavePreCard();
					m_leftAILayer->setIsDealCard(false);
				}
			}
			break;
		case Follow_Card_Player:
			{
				bool flag1 = m_leftAILayer->getIsDealCard();
				bool flag2 = m_rightAILayer->getIsDealCard();
				//如果其他两家都没有出牌
				if(!flag1&&!flag2)
				{
					m_playerLayer->setIsDealCard(false);

					m_CurState = First_Card_Player;
					return ;
				}
				//其它两家有玩家出牌了，继续这轮跟牌。
				else
				{
					m_playerLayer->followCard(m_MaxCard);
					//查看玩家是否已经出牌了
					bool flag = m_playerLayer->getIsDealCard();
					//玩家出完，右边电脑出牌
					if(flag)
					{
						m_MaxCard.clear();
						m_MaxCard= m_playerLayer->getSavePreCard();
						m_playerLayer->setMenuVisble(false);


						m_rightAILayer->setIsDealCard(false);
						//玩家出完，右边电脑出牌
						m_CurState = Follow_Card_RightRobot;
					}
					else
					{

					}
					bool buttonState = m_playerLayer->getBuChuButtonState();
					if(buttonState)
					{
						//玩家不出，右边电脑出牌
						m_CurState = Follow_Card_RightRobot;
						m_playerLayer->setBuChuButtonState(false);
						m_rightAILayer->setIsDealCard(false);
					}
				}
			}
			break;
		case Follow_Card_LeftRobot:
			{
				//CCSleep(200);
				bool flag1 = m_playerLayer->getIsDealCard();
				bool flag2 = m_rightAILayer->getIsDealCard();

				//如果其他两家都没有出牌
				if(!flag1&&!flag2)
				{
					m_leftAILayer->setIsDealCard(false);
					m_CurState = First_Card_LeftRobot;
					return ;
				}
				//其它两家有玩家出牌了，继续这轮跟牌。
				else
				{
					m_leftAILayer->setIsDealCard(false);
					m_leftAILayer->followCard(dt,m_MaxCard);
					bool flag = m_leftAILayer->getIsDealCard();
					//如果出牌了
					if(flag)
					{
						m_MaxCard.clear();
						//跟新最大的牌
						m_MaxCard= m_leftAILayer->getSavePreCard();
						//左边电脑出完，玩家出牌

						m_playerLayer->setIsDealCard(false);

						m_CurState = Follow_Card_Player;
					}
					else
					{
						m_playerLayer->setIsDealCard(false);
						//左边电脑不出，玩家出牌
						m_CurState = Follow_Card_Player;
					}

				}
			}
			break;
		case Follow_Card_RightRobot:
			{
				//CCSleep(200);
				bool flag1 = m_playerLayer->getIsDealCard();
				bool flag2 = m_leftAILayer->getIsDealCard();

				//如果其他两家都没有出牌
				if(!flag1&&!flag2)
				{
					m_rightAILayer->setIsDealCard(false);
					m_CurState = First_Card_RightRobot;
					return ;
				}
				//其它两家有玩家出牌了，继续这轮跟牌。
				else
				{
					m_rightAILayer->followCard(dt,m_MaxCard);

					bool flag = m_rightAILayer->getIsDealCard();

					//如果出牌了
					if(flag)
					{
						m_MaxCard.clear();
						//跟新最大的牌
						m_MaxCard= m_rightAILayer->getSavePreCard();

						m_leftAILayer->setIsDealCard(false);
						//右边电脑出完，左边电脑出牌
						m_CurState = Follow_Card_LeftRobot;
					}
					else
					{
						m_leftAILayer->setIsDealCard(false);
						//右边电脑不出，左边电脑出牌
						m_CurState = Follow_Card_LeftRobot;
					}

				}
			}
			break;
		}

	}
	//画面重绘
	m_playerLayer->drawCard();
	m_rightAILayer->drawCard();
	m_leftAILayer->drawCard();
}

void SingleGame::setCurState( int state )
{
	m_CurState=state;
}

void SingleGame::back( CCObject* pSender )
{
	this->unscheduleUpdate();
	m_playerLayer->g_sharedPlayerLayer=NULL;
	m_leftAILayer->g_sharedLeftRobot=NULL;
	m_rightAILayer->g_sharedRightRoBot=NULL;
	this->g_sharedSingleGame=NULL;

	CCScene* pScene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}



