/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-4-20
Description:
**************************************************/
#include "ShowCardNumLayer.h"




ShowCardNumLayer::ShowCardNumLayer()
{

}

ShowCardNumLayer::~ShowCardNumLayer()
{
	for(int i=0;i<12;i++)
	{
		CC_SAFE_RELEASE(m_Num[i]);
	}
}

bool ShowCardNumLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSpriteBatchNode* NumNode = CCSpriteBatchNode::create("btn/timerdigits2.png");
		this->addChild(NumNode,2);

		for(int i=0;i<12;i++)
		{
			m_Num[i]=CCSpriteFrame::create("btn/timerdigits2.png",CCRectMake(i*24,0,18,24));
			CC_SAFE_RETAIN(m_Num[i]);
		}

		for(int i=0;i<2;i++)
		{
			m_showNum[i]=CCSprite::create("btn/timerdigits2.png",CCRectMake(i*24,0,24,24));
			m_showNum[i]->setScaleX(size.width /m_showNum[i]->getContentSize().width*0.04);
			m_showNum[i]->setScaleY(size.height/m_showNum[i]->getContentSize().height*0.04);
			m_showNum[i]->setPosition(ccp(size.width*0.925+i*(size.width)/13/5, size.height/2*0.9));
			NumNode->addChild(m_showNum[i]);
		}
		coutNum(10);

		bRet=true;
	} while (0);
	return bRet;

}
void ShowCardNumLayer::coutNum(int total)
{
	int a[2];

	a[0]=total/10+1;
	a[1]=total%10+1;
	
	for(int i=0;i<2;i++)
	{
		m_showNum[i]->setDisplayFrame(m_Num[ a[i] ]);
	}
}

void ShowCardNumLayer::setStartPosition( float dt )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	for(int i=0;i<2;i++)
	{
		m_showNum[i]->setPosition(ccp(size.width*dt+i*(size.width)/13/3, size.height/2*0.9));
	}
}
