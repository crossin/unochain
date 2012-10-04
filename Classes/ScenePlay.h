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

	static const int COUNT_COL = 7;
	static const int COUNT_ROW = 12;

	void update(float dt);
	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	void touchBlock(UnoBlock* block);
	void clearBlock(UnoBlock* block);
	void moveBlocks();
	

	UnoBlock* arena[COUNT_COL][COUNT_ROW];
	//UnoBlock* blockLast;
	CCArray* chainSelected;
	float gametime;
};


