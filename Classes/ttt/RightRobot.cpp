/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-19
Description:�ұߵ���
**************************************************/

#include "RightRoBot.h"

USING_NS_CC;

RightRoBot* RightRoBot::g_sharedRightRoBot=NULL;
RightRoBot* RightRoBot::sharedRightRoBot()
{
	if(g_sharedRightRoBot==NULL)
	{
		g_sharedRightRoBot = RightRoBot::create();
	}
	return g_sharedRightRoBot;

}
RightRoBot::RightRoBot()
{

}
RightRoBot::~RightRoBot()
{
	for(int i=1;i<=54;i++)
	{
		CC_SAFE_RELEASE(m_allNum[i]);
	}
}


bool RightRoBot::init()
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
		m_showNum[i]->setScaleX(winSize.width /m_showNum[i]->getContentSize().width*0.07);
		m_showNum[i]->setScaleY(winSize.height/m_showNum[i]->getContentSize().height*0.15);
		m_showNum[i]->setPosition(ccp(m_winSize.width*0.83,winSize.height/2*0.9 ));
		//m_showNum[i]->setRotation(-90.0);
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showNum[i]->setVisible(true);

		this->addChild(m_showNum[i]);
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


	m_vis=false;
	m_ShowCardNumLayer = ShowCardNumLayer::create();
	m_ShowCardNumLayer->setStartPosition(0.81f);
	this->addChild(m_ShowCardNumLayer);
	return true;
}

void RightRoBot::getCard( int card[],int start,int end )
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
		//�Ǵ�С��
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


}

void RightRoBot::update( float dt )
{
	m_ID=PlayerCardLayer::sharedPlayerCardLayer()->getID();

	//�ұߵ������ȳ���
	if(m_ID==2)
	{
		m_preCard.clear();
		m_it =  m_card.begin();
		
		m_preCard.push_back( (*m_it) );

		m_card.erase(m_it);

		//������ƴ���
		m_savepreCardInt.clear();
		//��ŵ�ǰ������
		m_it=m_preCard.begin();
		while(m_it!=m_preCard.end())
		{
			m_savepreCardInt.push_back((*m_it).num);
			m_it++;
		}

		if(m_preCard.size()>0)
		{
			PlayerCardLayer::sharedPlayerCardLayer()->setWhoPlayFirstCard(2);
		}
		PlayerCardLayer::sharedPlayerCardLayer()->setID(6);
		LeftRobot::sharedLeftRobot()->setVis(false);

	}
	//�����һ����ҳ����ƣ��ж��ܷ����
	if(m_ID==5&&m_vis==false)
	{
		m_vis=true;
		m_lastDealCard = PlayerCardLayer::sharedPlayerCardLayer()->getSavePreCard();
		//�ҵ�����һ�ҳ����ƴ����
		m_preCard.clear();
		findCard();
		//������ƴ���
		m_savepreCardInt.clear();
		//��ŵ�ǰ������
		m_it=m_preCard.begin();
		while(m_it!=m_preCard.end())
		{
			m_savepreCardInt.push_back((*m_it).num);
			m_it++;
		}
		if(m_preCard.size()>0)
		{
			PlayerCardLayer::sharedPlayerCardLayer()->setID(2);
		}
		PlayerCardLayer::sharedPlayerCardLayer()->setID(6);
		LeftRobot::sharedLeftRobot()->setVis(false);
	}

	drawCard();

	m_ShowCardNumLayer->coutNum(m_card.size());

}

void RightRoBot::drawCard()
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
	//���·����Ƶ�λ��
	if(len<=0) return;
	if(len%2)
	{
		mid++;
		float temp = m_winSize.width/2*1.4;
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
		float temp = m_winSize.width/2*1.4-m_winSize.width/88;
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

void RightRoBot::showLastCard()
{

}
void RightRoBot::findCard()
{
	//����
	if(m_lastDealCard.size()==1)
	{
		m_it=m_card.end();
		m_it--;
		while(m_it!=m_card.begin())
		{
			if(  (*m_it).num>m_lastDealCard[0]  )
			{
				CCLOG("%d",  (*m_it).num );
				m_preCard.push_back((*m_it));
				m_card.erase(m_it);
				break;
			}
			m_it--;
		}
	}
	if(m_lastDealCard.size()==2)
	{
		//�������С����һ������ͣ���˫���ƣ����������ʲô���Ͷ����Դ�
		if(m_lastDealCard[0]==17&&m_lastDealCard[1]==16)
		{
			return;
		}
		//���ӣ�һ���ƣ�����ͬ��������������һ������ͣ�����55��
		if(m_lastDealCard[0]==m_lastDealCard[1])
		{
			m_it=m_card.begin();
			
			while(m_it!=m_card.end())
			{
				if(  (*m_it).num>m_lastDealCard[0]  )
				{

				//	CCLOG("%d",  (*m_it).num );
					m_it2 = m_it++;
					if( (*m_it2).num==(*m_it).num )
					{
						m_preCard.push_back((*m_it));
						m_preCard.push_back((*m_it2));
///////////////////////////////////////////////////////////////////////////
						m_card.erase(m_it2);
						m_card.erase(m_it);
						break;
					}
				}
				m_it++;
			}
		}
	}
	if(m_lastDealCard.size()==3)
	{

	}
	if(m_lastDealCard.size()==4)
	{
	}
	if(m_lastDealCard.size()==5)
	{

	}
	if(m_lastDealCard.size()==6)
	{
	}
	if(m_lastDealCard.size()==7)
	{

	}
}

void RightRoBot::setVis(bool flag)
{
	m_vis=flag;
}

std::vector<int> RightRoBot::getSavePreCard()
{
	return m_savepreCardInt;
}

