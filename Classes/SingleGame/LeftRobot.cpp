/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-15
Description:左边电脑
**************************************************/

#include "LeftRobot.h"
USING_NS_CC;

LeftRobot* LeftRobot::sharedLeftRobot()
{
	if(g_sharedLeftRobot==NULL)
	{
		g_sharedLeftRobot = LeftRobot::create();
	}
	return g_sharedLeftRobot;
}
LeftRobot* LeftRobot::g_sharedLeftRobot=NULL;

LeftRobot::LeftRobot()
{

}

LeftRobot::~LeftRobot()
{

}
bool LeftRobot::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_winSize = winSize;

	
	for(int i=1;i<=54;i++)
	{
		int color,num;
		if(i%13==0)
		{
			color = (i)/13;
			num   = 13;
		}
		else
		{
			color = (i)/13+1;
			num   = (i)%13;
		}
		char path[30];
		sprintf(path,"btn/%d%d.png",color,num);
		m_allNum[i] = CCSpriteFrame::create(path,CCRect(0,0,71,96));
		CC_SAFE_RETAIN(m_allNum[i]);
	}


	for(int i=1;i<=20;i++)
	{
		m_showNum[i]=CCSprite::create("btn/poke_back_small.png");
		m_showNum[i]->setScaleX(winSize.width /m_showNum[i]->getTextureRect().getMaxX()*0.07);
		m_showNum[i]->setScaleY(winSize.height/m_showNum[i]->getTextureRect().getMaxY()*0.15);
		m_showNum[i]->setPosition(ccp(m_winSize.width*0.17,winSize.height/2*0.9 ));
		//m_showNum[i]->setRotation(90.0);
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showNum[i]->setVisible(true);

		this->addChild(m_showNum[i]);
	}
	for(int i=1;i<=20;i++)
	{
		m_showLastCard[i]=CCSprite::create("btn/cardbg.png");
		m_showLastCard[i]->setScaleX(winSize.width /m_showLastCard[i]->getTextureRect().getMaxX()*0.05);
		m_showLastCard[i]->setScaleY(winSize.height/m_showLastCard[i]->getTextureRect().getMaxY()*0.1);
		m_showLastCard[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/44),winSize.height/3*1.25));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showLastCard[i]->setVisible(false);
		this->addChild(m_showLastCard[i]);
	}


	for(int i=1;i<=20;i++)
	{
		m_showLastCard[i]=CCSprite::create("btn/cardbg.png");
		m_showLastCard[i]->setScaleX(winSize.width /m_showLastCard[i]->getContentSize().width*0.05);
		m_showLastCard[i]->setScaleY(winSize.height/m_showLastCard[i]->getContentSize().height*0.1);
		m_showLastCard[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/44),winSize.height/2*1.1));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showLastCard[i]->setVisible(false);
		this->addChild(m_showLastCard[i]);
	}

	m_buchuImage = CCSprite::create("btn/text_pass.png");
	m_buchuImage->setScaleX(winSize.width /m_buchuImage->getContentSize().width*0.1);
	m_buchuImage->setScaleY(winSize.height/m_buchuImage->getContentSize().height*0.1);
	m_buchuImage->setPosition(ccp(winSize.width/2*0.6,winSize.height/2*1.1));
	m_buchuImage->setVisible(false);
	this->addChild(m_buchuImage);


	m_ShowCardNumLayer = ShowCardNumLayer::create();
	m_ShowCardNumLayer->setStartPosition(0.15f);
	this->addChild(m_ShowCardNumLayer);

	m_IsDealedCard=false;
	return true;
}


void LeftRobot::getCard( int card[],int start,int end )
{
	for(int i=start;i<=end;i++)
	{
		Card temp;
		if(card[i]%13==0)
		{
			temp.color = (card[i])/13;
			temp.num   = 13;
		}
		else
		{
			temp.color = (card[i])/13+1;
			temp.num   = (card[i])%13;
		}

		temp.colorPosition = card[i];
		temp.sortVal = temp.num ;
		temp.isSelect = false;
		temp.needDelete=false;
		//是大小王
		if(temp.color==5)
		{
			temp.sortVal=20+temp.num;
			temp.num = 15+temp.num;

		}
		else
		{
			if(temp.num==1||temp.num==2)
			{
				temp.sortVal=15+temp.num;
				if(temp.num==1)
					temp.num=14;

				if(temp.num==2)
					temp.num=15;
			}
		}

		temp.width=m_winSize.width/22;
		//////////////////////////////////
		temp.height=m_winSize.height/10;
		//////////////////////////////////
		m_card.push_back(temp);
	}
	m_card.sort();
	m_ShowCardNumLayer->coutNum(m_card.size());
	/*m_it= m_card.begin();
	while(m_it!=m_card.end())
	{
		CCLOG("%d %d",m_isleft,(*m_it).num);
		m_it++;
	}*/

}

void LeftRobot::doTheFirstCard( float dt )
{
	m_IsDealedCard=true;
	m_preCard.clear();
	m_savepreCardInt.clear();
	//m_it=m_card.begin();
	//m_preCard.push_back( (*m_it));
	//m_card.erase( m_card.begin());
	//找出最好的第一次出牌策略
	findBestFirstCard();

	//存放当前出的牌
	m_it=m_preCard.begin();
	while(m_it!=m_preCard.end())
	{
		m_savepreCardInt.push_back((*m_it).num);
		m_it++;
	}

	m_ShowCardNumLayer->coutNum(m_card.size());
}
void LeftRobot::findBestFirstCard()
{
	bool find=false;
	int k;

	m_tempVector.clear();
	//找对子
	m_it=m_card.begin();
	while(m_it!=m_card.end())
	{
		m_tempVector.push_back( (*m_it).num );
		m_it++;
	}
	for(int i=1;i<m_tempVector.size();i++)
	{
		if(m_tempVector[i]==m_tempVector[i-1])
		{
			find=true;
			k=i;
			break;
		}
	}
	if(find)
	{
		m_it = m_card.begin();
		int cnt=k-1;
		while(cnt)
		{
			m_it++;
			cnt--;
		}
		m_preCard.push_back( (*m_it) );
		m_it++;
		m_preCard.push_back((*m_it));
		m_it = m_card.begin();
		m_it2 = m_card.begin();
		cnt=k-1;
		while(cnt)
		{
			m_it++;
			m_it2++;
			cnt--;
		}
		m_it2++;
		m_card.erase(m_it2); 
		m_card.erase(m_it);
	}
	else
	{
		m_it=m_card.begin();
		m_preCard.push_back( (*m_it));
		m_card.erase( m_card.begin());

	}

}


void LeftRobot::followCard( float dt ,std::vector<int > lastPlayerCard)
{
	//获得上一个玩家出的牌，判断能否跟牌
	m_lastPlayerCard = lastPlayerCard;
	//找到比上一家出的牌大的牌
	m_preCard.clear();
	findCard();
	//如果跟牌打不起
	m_savepreCardInt.clear();
	//存放当前出的牌
	m_it=m_preCard.begin();
	while(m_it!=m_preCard.end())
	{
		m_savepreCardInt.push_back((*m_it).num);
		m_it++;
	}
	//出牌了
	if(m_preCard.size()>0)
	{
		m_buchuImage->setVisible(false);
		m_IsDealedCard=true;
	}
	else
	{
		m_buchuImage->setVisible(true);
	}
	m_ShowCardNumLayer->coutNum(m_card.size());
}
void LeftRobot::setIsDealCard( bool flag )
{
	m_IsDealedCard=flag;
}

bool LeftRobot::getIsDealCard()
{
	return m_IsDealedCard;
}

//void LeftRobot::update( float dt )
//{
	//m_ID=PlayerCardLayer::sharedPlayerCardLayer()->getID();

	////左边电脑最先出牌
	//if(m_ID==3)
	//{
	//	m_preCard.clear();
	//	m_it =  m_card.begin();
	//	
	//	m_preCard.push_back((*m_it) );

	//	m_card.erase(m_it);

	//	m_savepreCardInt.clear();
	//	//存放当前出的牌
	//	m_it=m_preCard.begin();
	//	while(m_it!=m_preCard.end())
	//	{

	//		m_savepreCardInt.push_back((*m_it).num);
	//		m_it++;
	//	}

	//	if(m_preCard.size()>0)
	//	{
	//		PlayerCardLayer::sharedPlayerCardLayer()->setID(3);
	//	}

	//	PlayerCardLayer::sharedPlayerCardLayer()->setID(4);

	//}
	////获得上一个玩家出的牌，判断能否跟牌
	//if(m_ID==6&&m_vis==false)
	//{
	//	m_vis=true;
	//	m_lastDealCard = RightRoBot::sharedRightRoBot()->getSavePreCard();

	//	
	//	//	for(int i=0;i<m_lastDealCard.size();i++)
	//	//	{
	//	//		CCLOG("%d",m_lastDealCard[i]);
	//	//	}
	//	//找到比上一家出的牌大的牌
	//	m_preCard.clear();
	//	findCard();
	//	m_savepreCardInt.clear();
	//	//存放当前出的牌
	//	m_it=m_preCard.begin();
	//	while(m_it!=m_preCard.end())
	//	{

	//		m_savepreCardInt.push_back((*m_it).num);
	//		m_it++;
	//	}
	//	if(m_preCard.size()>0)
	//	{
	//		PlayerCardLayer::sharedPlayerCardLayer()->setWhoPlayFirstCard(3);
	//	}
	//	
	//	PlayerCardLayer::sharedPlayerCardLayer()->setID(4);

	//
	//}

	//drawCard();
	//m_ShowCardNumLayer->coutNum(m_card.size());

//}

void LeftRobot::showLastCard()
{

}

void LeftRobot::drawCard()
{

	int len = m_preCard.size();
	int mid = len/2 ;
	for(int i=1;i<=len;i++)
	{
		m_showLastCard[i]->setVisible(true);
	}
	for(int i=len+1;i<=20;i++)
	{
		m_showLastCard[i]->setVisible(false);
	}

	//重新放置牌的位置
	if(len<=0) return;
	if(len%2)
	{
		mid++;
		float temp = m_winSize.width/2*0.6;
		for(int i=mid;i<=len;i++)
		{
			m_showLastCard[i]->setPositionX(temp);
			temp+=m_winSize.width/44;
		}
		temp = m_winSize.width/2-m_winSize.width/44;
		for(int i=mid-1;i>=1;i--)
		{
			m_showLastCard[i]->setPositionX(temp);
			temp-=m_winSize.width/44;
		}

	}
	else
	{
		float temp = m_winSize.width/2*0.6-m_winSize.width/88;
		for(int i=mid;i<=len;i++)
		{
			m_showLastCard[i]->setPositionX(temp);
			temp+=m_winSize.width/44;
		}
		temp = m_winSize.width/2-m_winSize.width/44-m_winSize.width/88;
		for(int i=mid-1;i>=1;i--)
		{
			m_showLastCard[i]->setPositionX(temp);
			temp-=m_winSize.width/44;
		}
	}
	
	m_it = m_preCard.begin();
	len=1;
	while(m_it!=m_preCard.end())
	{
		//m_showLastCard[len]->setSpriteFrame(m_allNum[(*m_it).colorPosition]);
		m_showLastCard[len]->setDisplayFrame(m_allNum[(*m_it).colorPosition]);
		++m_it;     
		++len;
	}
}

void LeftRobot::findCard()
{
	//单牌
	if(m_lastPlayerCard.size()==1)
	{
		m_it=m_card.end();
		m_it--;
		while(m_it!=m_card.begin())
		{
			if(  (*m_it).num>m_lastPlayerCard[0]  )
			{
				CCLOG("%d",  (*m_it).num );
				m_preCard.push_back((*m_it));
				m_card.erase(m_it);

				break;
			}
			m_it--;
		}
	}
	if(m_lastPlayerCard.size()==2)
	{
		//火箭：大小王在一起的牌型，即双王牌，此牌型最大，什么牌型都可以打。
		if(m_lastPlayerCard[0]==17&&m_lastPlayerCard[1]==16)
		{
			return;
		}
		//对子（一手牌）：相同点数的两张牌在一起的牌型，比如55。
		if(m_lastPlayerCard[0]==m_lastPlayerCard[1])
		{
			m_it=m_card.begin();
			m_it2 = m_card.begin();
			m_it2++;

			while(m_it2!=m_card.end())
			{
				if(  (*m_it).num>m_lastPlayerCard[0]  )
				{
					if( (*m_it2).num==(*m_it).num )
					{
						m_preCard.push_back((*m_it));
						m_preCard.push_back((*m_it2));
						m_card.erase(m_it2);
						m_card.erase(m_it);
						break;
					}
				}
				m_it++;
				m_it2++;
			}
		}
	}
	if(m_lastPlayerCard.size()==3)
	{

	}
	if(m_lastPlayerCard.size()==4)
	{
	}
	if(m_lastPlayerCard.size()==5)
	{

	}
	if(m_lastPlayerCard.size()==6)
	{
	}
	if(m_lastPlayerCard.size()==7)
	{

	}
}



std::vector<int> LeftRobot::getSavePreCard()
{
	return m_savepreCardInt;
}

int LeftRobot::getTotalCardNum()
{
	return m_card.size();
}






