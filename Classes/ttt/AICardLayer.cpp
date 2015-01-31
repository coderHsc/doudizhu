/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-19
Description:电脑卡牌
**************************************************/

#include "AICardLayer.h"
USING_NS_CC;

bool AICardLayer::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_winSize = winSize;

	m_showCardBg = CCSpriteFrame::create("btn/cardbg.png",CCRect(0,0,33.3f,45));
	CC_SAFE_RETAIN(m_showCardBg);

	for(int i=1;i<=20;i++)
	{
		m_showNum[i]=CCSprite::create("btn/cardbg.png");
		m_showNum[i]->setScaleX(winSize.width /m_showNum[i]->getContentSize().width*0.05);
		m_showNum[i]->setScaleY(winSize.height/m_showNum[i]->getContentSize().height*0.125);
		m_showNum[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/22),winSize.height/2*0.9 ));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showNum[i]->setVisible(true);

		this->addChild(m_showNum[i]);
	}
	for(int i=1;i<=20;i++)
	{
		m_showLastCard[i]=CCSprite::create("btn/cardbg.png");
		m_showLastCard[i]->setScaleX(winSize.width /m_showLastCard[i]->getContentSize().width*0.05);
		m_showLastCard[i]->setScaleY(winSize.height/m_showLastCard[i]->getContentSize().height*0.1);
		m_showLastCard[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/44),winSize.height/3*1.25));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showLastCard[i]->setVisible(false);
		this->addChild(m_showLastCard[i]);
	}

	return true;
}

void AICardLayer::setIsLeft( bool flag )
{
	m_isleft=flag;
	if(m_isleft)
	{
		for(int i=1;i<=20;i++)
		{
			m_showNum[i]->setPositionX(m_winSize.width*0.17);
			m_showNum[i]->setRotation(90.0);
		}
	}
	else
	{
		for(int i=1;i<=20;i++)
		{
			m_showNum[i]->setPositionX(m_winSize.width*0.83);
			m_showNum[i]->setRotation(-90.0);
		}

	}
}
void AICardLayer::getCard( int card[],int start,int end )
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
			temp.num = 14+temp.num;

		}
		else
		{
			if(temp.num==1||temp.num==2)
			{
				temp.sortVal=15+temp.num;
				if(temp.num==1)
					temp.num=14;
			}
		}

		temp.width=m_winSize.width/22;
		//////////////////////////////////
		temp.height=m_winSize.height/10;
		//////////////////////////////////
		m_card.push_back(temp);
	}
	m_card.sort();
	/*m_it= m_card.begin();
	while(m_it!=m_card.end())
	{
		CCLOG("%d %d",m_isleft,(*m_it).num);
		m_it++;
	}*/

}

void AICardLayer::update( float dt )
{
}

void AICardLayer::showLastCard()
{

}

