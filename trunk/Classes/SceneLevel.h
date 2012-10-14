#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneLevel :
	public CCLayer
{
public:
	SceneLevel(void);
	~SceneLevel(void);

	virtual bool init();  
	static cocos2d::CCScene* scene(int cpt);
	CREATE_FUNC(SceneLevel);

	void buttonCallback(CCObject* pSender);

	void setChapter(int cpt);

	CCLabelTTF* txtTitle;
	int chapter;
};

