/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-2-17
Description:¼ÓÔØÒôÀÖ
**************************************************/
#include "AudioEngine.h"
//using namespace CocosDenshion;

//USING_NS_CC;

AudioEngine* AudioEngine::g_sharedEngine=NULL;

AudioEngine* AudioEngine::sharedEngine()
{
	if (g_sharedEngine==NULL)
	{
		g_sharedEngine=new AudioEngine();
		g_sharedEngine->init();
	}
	return g_sharedEngine;
}

bool AudioEngine::init()
{
	g_sharedEngine->preloadEffect("sounds/1000.ogg");
	g_sharedEngine->preloadBackgroundMusic("sounds/0.mp3");

	return true;
}