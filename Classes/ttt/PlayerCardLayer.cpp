/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-02-18
Description:玩家卡牌界面
**************************************************/
#include "SingleGame/PlayerCardLayer.h"
USING_NS_CC;

PlayerCardLayer::PlayerCardLayer()
{

}
PlayerCardLayer::~PlayerCardLayer()
{
	for(int i=1;i<=54;i++)
	{
		CC_SAFE_RELEASE(m_allNum[i]);
	}
}

PlayerCardLayer* PlayerCardLayer::g_sharedPlayerCardLayer=NULL;
PlayerCardLayer* PlayerCardLayer::sharedPlayerCardLayer()
{
	if(g_sharedPlayerCardLayer==NULL)
	{
		g_sharedPlayerCardLayer = PlayerCardLayer::create();
	}
	return g_sharedPlayerCardLayer;

}



bool PlayerCardLayer::init()
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
		m_showNum[i]=CCSprite::create("btn/11.png");
		m_showNum[i]->setScaleX(winSize.width /m_showNum[i]->getContentSize().width*0.1);
		m_showNum[i]->setScaleY(winSize.height/m_showNum[i]->getContentSize().height*0.25);
		m_showNum[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/22),winSize.height/5 ));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showNum[i]->setVisible(false);

		this->addChild(m_showNum[i],4);
	}


	for(int i=1;i<=20;i++)
	{
		m_showLastCard[i]=CCSprite::create("btn/11.png");
		m_showLastCard[i]->setScaleX(winSize.width /m_showLastCard[i]->getContentSize().width*0.05);
		m_showLastCard[i]->setScaleY(winSize.height/m_showLastCard[i]->getContentSize().height*0.125);
		m_showLastCard[i]->setPosition(ccp(winSize.width-((i-11)*winSize.width/44),winSize.height/3*1.25));
		//m_timerdigits1->addChild(m_showNum1[i]);
		m_showLastCard[i]->setVisible(false);
		this->addChild(m_showLastCard[i],2);
	}

	this->setTouchEnabled(true);

	//添加发牌按钮
	CCMenuItemImage* deal = CCMenuItemImage::create(
		"btn/startbtn_normal.png",
		"btn/startbtn_touched.png",
		this,
		menu_selector(PlayerCardLayer::dealCard));
	deal->setScaleY((winSize.height/deal->getContentSize().height*0.1));
	deal->setScaleX((winSize.width /deal->getContentSize().width)*0.1);

	m_dealCardMenu = CCMenu::create(deal,NULL);
	m_dealCardMenu->setPosition(ccp(winSize.width / 2*1.2,winSize.height/3*1.2));
	m_deal_image = CCSprite::create("btn/text_sendcard.png");

	m_deal_image->setScaleY((winSize.height/m_deal_image->getContentSize().height*0.05));
	m_deal_image->setScaleX((winSize.width /m_deal_image->getContentSize().width)*0.05);
	m_deal_image->setPosition(ccp(winSize.width / 2*1.2,winSize.height/3*1.2));
	this->addChild(m_dealCardMenu, 2);
	this->addChild(m_deal_image,2);

	//添加发牌按钮
	CCMenuItemImage* buchu = CCMenuItemImage::create(
		"btn/startbtn_normal.png",
		"btn/startbtn_touched.png",
		this,
		menu_selector(PlayerCardLayer::buchuCard));
	buchu->setScaleY((winSize.height/buchu->getContentSize().height*0.1));
	buchu->setScaleX((winSize.width /buchu->getContentSize().width)*0.1);

	m_buchuMenu = CCMenu::create(buchu,NULL);
	m_buchuMenu->setPosition(ccp(winSize.width / 2*0.8,winSize.height/3*1.2));

	m_buchu_image = CCSprite::create("btn/text_pass.png");

	m_buchu_image->setScaleY((winSize.height/m_buchu_image->getContentSize().height*0.05));
	m_buchu_image->setScaleX((winSize.width /m_buchu_image->getContentSize().width)*0.05);
	m_buchu_image->setPosition(ccp(winSize.width / 2*0.8,winSize.height/3*1.2));

	this->addChild(m_buchuMenu, 2);
	this->addChild(m_buchu_image,2);

	//测试，让玩家先发牌
	m_dealCard = true;

	m_ID=1;
	m_whoPlayFirstCard=1;
	return true;
}
void PlayerCardLayer::getCard( int card[] ,int start,int end)
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
	//m_card.sort();
}
void PlayerCardLayer::shuffledCard()
{
	int len = m_card.size();
	int mid = len/2 ;
	if(len<=0) return;
	//重新放置牌的位置
	if(len%2)
	{
		mid++;
		float temp = m_winSize.width/2;
		for(int i=mid;i<=len;i++)
		{
			m_showNum[i]->setPositionX(temp);
			temp+=m_winSize.width/22;
		}
		temp = m_winSize.width/2-m_winSize.width/22;
		for(int i=mid-1;i>=1;i--)
		{
			m_showNum[i]->setPositionX(temp);
			temp-=m_winSize.width/22;
		}

	}
	else
	{
		float temp = m_winSize.width/2-m_winSize.width/44;
		for(int i=mid;i<=len;i++)
		{
			m_showNum[i]->setPositionX(temp);
			temp+=m_winSize.width/22;
		}
		temp = m_winSize.width/2-m_winSize.width/22-m_winSize.width/44;
		for(int i=mid-1;i>=1;i--)
		{
			m_showNum[i]->setPositionX(temp);
			temp-=m_winSize.width/22;
		}
	}

	m_preCardInt.clear();
	m_it = m_card.begin();
	int temp=1;
	while(m_it!=m_card.end())
	{
		if((*m_it).needDelete )
		{
			m_preCard.push_back((*m_it));
			m_card.erase(m_it);
			break;
		}
		if((*m_it).isSelect)
		{
			m_preCardInt.push_back( (*m_it).num );
			m_showNum[temp]->setPositionY(m_winSize.height/5+m_winSize.height/20);
		}
		else
		{
			m_showNum[temp]->setPositionY(m_winSize.height/5);
		}
		++temp;
		++m_it;
	}
	for(int i=1;i<=len;i++)
	{
		m_showNum[i]->setVisible(true);
	}
	for(int i=len+1;i<=20;i++)
	{
		m_showNum[i]->setVisible(false);
	}
}

void PlayerCardLayer::shuffledPreCard()
{
	int len = m_preCard.size();
	int mid = len/2 ;
	//重新放置牌的位置
	if(len<=0) return;
	if(len%2)
	{
		mid++;
		float temp = m_winSize.width/2;
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
		float temp = m_winSize.width/2-m_winSize.width/88;
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
	for(int i=1;i<=len;i++)
	{
		m_showLastCard[i]->setVisible(true);
	}
	for(int i=len+1;i<=20;i++)
	{
		m_showLastCard[i]->setVisible(false);
	}
}


void PlayerCardLayer::update(float dt)
{
	this->shuffledCard();
	this->shuffledPreCard();
	this->drawCard();
}

void PlayerCardLayer::drawCard()
{
	//如果轮到玩家发牌，显示发牌按钮
	
	if(m_ID==1||m_ID==4)
	{
		m_dealCardMenu->setVisible(true);
		m_buchu_image->setVisible(true);
		m_buchuMenu->setVisible(true);
		m_deal_image->setVisible(true);
	}
	else
	{
		m_dealCardMenu->setVisible(false);
		m_buchu_image->setVisible(false);
		m_buchuMenu->setVisible(false);
		m_deal_image->setVisible(false);
	}
	//显示
	m_it = m_card.begin();
	int len=1;
	while(m_it!=m_card.end())
	{
		//重新获取坐标，X坐标左边起始位置为:
		(*m_it).x = m_showNum[len]->getPositionX()-(m_winSize.width*0.1)*0.5;
		//左下角Y坐标
		(*m_it).y = m_showNum[len]->getPositionY()-(m_winSize.height*0.25)*0.5;

		m_showNum[len]->setDisplayFrame(m_allNum[(*m_it).colorPosition]);

	//	m_showNum[len]->setSpriteFrame(m_allNum[(*m_it).colorPosition]);
		++m_it;  
		++len;
	}

	m_it = m_preCard.begin();
	len=1;
	while(m_it!=m_preCard.end())
	{
		//m_showLastCard[len]->setSpriteFrame(m_allNum[(*m_it).colorPosition]);
		m_showLastCard[len]->setDisplayFrame(m_allNum[(*m_it).colorPosition]);

		//CCLOG("%d",(*m_it).num);
		++m_it;     
		++len;
	}
}

void PlayerCardLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	
	CCSetIterator ite=pTouches->begin();
	CCTouch* touch=(CCTouch*)(*ite);
	CCPoint touchLocation=touch->getLocation();

	m_it = m_card.begin();
	int len = 1;
	int max_len = m_card.size();
	while(m_it!=m_card.end())
	{
		m_tempMoveVal[len]=(*m_it).isSelect;
		m_isSelect[len]=false;

		if(len==max_len)
		{
			if((*m_it).x<=touchLocation.x&&(*m_it).x+(m_winSize.width*0.1)>=touchLocation.x
				&&(*m_it).y<=touchLocation.y&&(*m_it).y+(m_winSize.height*0.25)>=touchLocation.y)
			{
				m_isSelect[len]=true;
				m_tempMoveVal[len]=!m_tempMoveVal[len];
			}
		}
		else
		{
			if((*m_it).x<=touchLocation.x&&(*m_it).x+m_winSize.width/22>=touchLocation.x
				&&(*m_it).y<=touchLocation.y&&(*m_it).y+(m_winSize.height*0.25)>=touchLocation.y)
			{
				m_isSelect[len]=true;
				m_tempMoveVal[len]=!m_tempMoveVal[len];
			}
		}
		len++;
		m_it++;
	}
}

void PlayerCardLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	
	//CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCSetIterator ite=pTouches->begin();
	CCTouch* touch=(CCTouch*)(*ite);
	CCPoint touchLocation=touch->getLocation();//原来getLocation函数就是直接转换为了GL坐标
	m_it = m_card.begin();
	m_X.clear();
	while(m_it!=m_card.end())
	{
		m_X.push_back( (*m_it).x );
		m_it++;
	}
	int len=lower_bound(m_X.begin(),m_X.end(),touchLocation.x)-m_X.begin();

	m_it = m_card.begin();
	int temp=len-1;
	while((temp--)>0) m_it++;

	int max_len = m_card.size();

	if(len>=1&&len<=max_len&&!m_isSelect[len])
	{
		if(len==max_len)
		{
			if((*m_it).x<=touchLocation.x&&(*m_it).x+(m_winSize.width*0.1)>=touchLocation.x
				&&(*m_it).y<=touchLocation.y&&(*m_it).y+(m_winSize.height*0.25)>=touchLocation.y)
			{
				m_isSelect[len]=true;
				m_tempMoveVal[len]=!m_tempMoveVal[len];
			}
		}
		else
		{
			if((*m_it).x<=touchLocation.x&&(*m_it).x+m_winSize.width/22>=touchLocation.x
				&&(*m_it).y<=touchLocation.y&&(*m_it).y+(m_winSize.height*0.25)>=touchLocation.y)
			{
				m_isSelect[len]=true;
				m_tempMoveVal[len]=!m_tempMoveVal[len];
			}
		}
	}

	
}

void PlayerCardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCSetIterator ite=pTouches->begin();
	CCTouch* touch=(CCTouch*)(*ite);
	CCPoint touchLocation=touch->getLocation();//原来getLocation函数就是直接转换为了GL坐标
	//显示
	m_it = m_card.begin();
	int len = 1;
	int max_len = m_card.size();
	while(m_it!=m_card.end())
	{
		(*m_it).isSelect=m_tempMoveVal[len];
		len++;
		m_it++;     
	}
}
void PlayerCardLayer::buchuCard( CCObject* pSender )
{
	m_ID=m_whoPlayFirstCard;
}


void PlayerCardLayer::dealCard( CCObject* pSender )
{
	if(Card_rule())
	{
		//让玩家不能发牌
		m_whoPlayFirstCard=1;
		m_ID=5;
		RightRoBot::sharedRightRoBot()->setVis(false);
		m_dealCard=false;
		m_preCard.clear();
		m_savepreCardInt.clear();
		for(int i=0;i<m_preCardInt.size();i++)
		{
			m_savepreCardInt.push_back(m_preCardInt[i]);
		}

		m_preCardInt.clear();
		m_it = m_card.begin();
		while(m_it!=m_card.end())
		{
			if((*m_it).isSelect)
			{
				(*m_it).needDelete=true;
			}
			m_it++;
		}
	}
	//else
	//{
	//	m_preCard.clear();
	//	m_preCardInt.clear();
	//	CCLOG("test");
	//}
}

bool PlayerCardLayer::Card_rule()
{
	if(m_preCardInt.size()==0) return false;
	//单牌
	if(m_preCardInt.size()==1) return true;
	if(m_preCardInt.size()==2)
	{
		//火箭：大小王在一起的牌型，即双王牌，此牌型最大，什么牌型都可以打。
		if(m_preCardInt[0]==17&&m_preCardInt[1]==16) return true;
		//对子（一手牌）：相同点数的两张牌在一起的牌型，比如55。
		if(m_preCardInt[0]==m_preCardInt[1])         return true;
	}
	if(m_preCardInt.size()==3)
	{
		//三条：相同点数的三张牌在一起的牌型，比如三条4。
		if(m_preCardInt[0]==m_preCardInt[2])         return true;

	}
	if(m_preCardInt.size()==4)
	{
		//炸弹：相同点数的四张牌在一起的牌型，比如四条A。除火箭外，它可以打任何牌型，炸弹对炸弹时，要比大小。
		if(m_preCardInt[0]==m_preCardInt[3])         return true;

		//三带一手：三条 ＋ 一手牌的牌型，比如AAA+9
		if(m_preCardInt[0]==m_preCardInt[2]||m_preCardInt[1]==m_preCardInt[3])
		{
			return true;
		}
	}
	if(m_preCardInt.size()==5)
	{
		//三带一对：AAA+77
		if((m_preCardInt[0]==m_preCardInt[2]&&m_preCardInt[3]==m_preCardInt[4])
		 ||(m_preCardInt[2]==m_preCardInt[4]&&m_preCardInt[0]==m_preCardInt[1]))
		{
			return true;
		}
	}

	if(m_preCardInt.size()>=5)
	{
		bool flag=false;
		//含有大小王或者2一定不是顺子
		for(int i=0;i<(int)m_preCardInt.size();i++) 
		{
			if(m_preCardInt[i]==17||m_preCardInt[i]==16||m_preCardInt[i]==15) 
			{
				flag=true;
				break;
			}
		}

		if(!flag)
		{
			//单顺：五张或更多的连续单支牌组成的牌型，比如45678或345678910JQKA。
			int val = m_preCardInt[0],index=1;
			while(index<(int)m_preCardInt.size())
			{
				if((val-1)!=m_preCardInt[index])  break;
				val = m_preCardInt[index];
				index++;
			}
			if(index==m_preCardInt.size())     return true;
			//双顺：三对或更多的连续对子组成的牌型，比如334455或445566778899
			if(m_preCardInt.size()>=6&&(m_preCardInt.size()%2==0))
			{ 
				bool find=true;
				val = m_preCardInt[0]; index=0;

				while(index<(int)m_preCardInt.size())
				{
					if(m_preCardInt[index]!=m_preCardInt[index+1])  find=false;
					index+=2;
					if(index<(int)m_preCardInt.size())
					{
						if((val-1)!=m_preCardInt[index])   find=false;
						val = m_preCardInt[index];
					}
				}
				if(find) return true;
			}

			//三顺子:二个或更多的连续三条组成的牌型，比如777888或444555666777
			if(m_preCardInt.size()>=6&&(m_preCardInt.size()%3==0))
			{
				bool find = true;
				val = m_preCardInt[0]; index=0;

				while(index<(int)m_preCardInt.size())
				{
					if(m_preCardInt[index]!=m_preCardInt[index+1]||m_preCardInt[index]!=m_preCardInt[index+2])  find=false;
					index+=3;
					if(index<(int)m_preCardInt.size())
					{
						if((val-1)!=m_preCardInt[index])   find=false;
						val = m_preCardInt[index];
					}
				}
				if(find) return true;
			}

			//飞机带翅膀：三顺 ＋ 同数量的一手牌,比如777888+3+6或444555666+33+77+88
			if(m_preCardInt.size()>=8)
			{
				int arr[20];
				memset(arr,0,sizeof(arr));
				for(int i=0;i<(int)m_preCardInt.size();i++)
				{
					arr[  m_preCardInt[i] ]++;
				}
				int cnt_3=0,cnt_2=0,cnt_1=0,cnt_other=0;
				std::vector<int > tempArr; 
				tempArr.clear();
				for(int i=1;i<=19;i++)
				{
					if(arr[i]==1)
					{
						cnt_1++;
					}
					else if(arr[i]==2)
					{
						cnt_2++;
					}
					else if(arr[i]==3)
					{
						cnt_3++;
						tempArr.push_back(i);
					}
					else if(arr[i]>0)
					{
						cnt_other++;
					}
				}

				if(cnt_3>=2&&cnt_other==0)
				{
					//判断是不是顺子
					bool find = true;
					val = tempArr[0]; index=1;
					while(index<(int)tempArr.size())
					{
						if((val+1)!=tempArr[index])   find=false;
						val=tempArr[index];
						index+=1;		
					}
					if(find)
					{
						int temp = cnt_3;
						if(cnt_1==0&&cnt_2==cnt_3)
						{
							return true;
						}
						if(cnt_2==0&&cnt_1==cnt_3)
						{
							return true;
						}
					}

				}
			}
		}
	}

	if(m_preCardInt.size()>=6)
	{
		//四带二：四条+两手牌。比如AAAA+7+9或9999+33+55。
		int hash[20],cnt_4=0,cnt_1=0,cnt_2=0,cnt_other=0;
		memset(hash,0,sizeof(hash));
		for(int i=0;i<(int)m_preCardInt.size();i++)
		{
			hash[ m_preCardInt[i] ]++;
		}
		for(int i=1;i<=19;i++)
		{
			if(hash[i]==1)
			{
				cnt_1++;
			}
			else if(hash[i]==2)
			{
				cnt_2++;
			}
			else if(hash[i]==4)
			{
				cnt_4++;
			}
			else if(hash[i]>0)
			{
				cnt_other++;
			}
		}
		if(cnt_4==1&&cnt_other==0)
		{
			if(cnt_1==2&&cnt_2==0) return true;

			if(cnt_2==2&&cnt_1==0) return true;
		}
	}

	return false;
}

void PlayerCardLayer::setDealCard( bool flag )
{
	m_dealCard=flag;
}

std::vector<int> PlayerCardLayer::getSavePreCard()
{
	return m_savepreCardInt;
}

int PlayerCardLayer::getID()
{
	return m_ID;
}

void PlayerCardLayer::setID( int num )
{
	m_ID = num;
}

void PlayerCardLayer::setWhoPlayFirstCard( int num )
{
	m_whoPlayFirstCard=num;
}

int PlayerCardLayer::getWhoPlayFirstCard()
{
	return m_whoPlayFirstCard;
}



