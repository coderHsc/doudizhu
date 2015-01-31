/*************************************************
Copyright:hushencheng
Author:hushencheng
Date:2014-2-17
Description:º”‘ÿ“Ù¿÷
**************************************************/
#ifndef __AudioEngine__
#define __AudioEngine__

#include"SimpleAudioEngine.h"

class AudioEngine:public CocosDenshion::SimpleAudioEngine
{
public:
	static AudioEngine* sharedEngine();
	static AudioEngine* g_sharedEngine;
	bool init();
};
#endif