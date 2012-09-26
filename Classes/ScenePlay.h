#pragma once
#include "cocos2d.h"
#include "UnoBlock.h"

using namespace cocos2d;

class ScenePlay :
	public CCLayer
{
public:
	ScenePlay(void);
	~ScenePlay(void);

	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(ScenePlay);

	UnoBlock* arena[8][12];
};


