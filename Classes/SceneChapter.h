#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneChapter :
	public CCLayer
{
public:
	SceneChapter(void);
	~SceneChapter(void);

	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(SceneChapter);

	void buttonCallback(CCObject* pSender);
};

