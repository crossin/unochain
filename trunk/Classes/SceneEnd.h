#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneEnd :
	public CCLayer
{
public:
	SceneEnd(void);
	~SceneEnd(void);

	virtual bool init();  
	static CCScene* scene(bool isWin = false);
	CREATE_FUNC(SceneEnd);

	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	CCLabelTTF* textDesc;
};

