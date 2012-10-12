#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class SceneMenuClassic :
	public CCLayer
{
public:
	SceneMenuClassic(void);
	~SceneMenuClassic(void);

	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(SceneMenuClassic);
};

