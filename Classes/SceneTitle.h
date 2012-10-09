#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneTitle :
	public CCLayer
{
public:
	SceneTitle(void);
	~SceneTitle(void);

	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(SceneTitle);

	void buttonCallback(CCObject* pSender);
};

