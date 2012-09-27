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

	//void updateFrame(CCTime dt);
	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	void touchBlock(UnoBlock* block);
	
	UnoBlock* arena[8][12];
	//UnoBlock* blockLast;
	CCArray* chainSelected;
};


