#pragma once
#include "cocos2d.h"
#include "LEUBlock.h"

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
	static const int COUNT_ROW = 10;

	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	virtual void clearChain();
	void clearAndRefill(bool refillable);
	void touchBlock(LEUBlock* block);
	void clearBlock(LEUBlock* block, bool refillable);
	void moveBlocks();
	void checkNoMoves();
	
	
	LEUBlock* arena[COUNT_COL][COUNT_ROW];
	//Block* blockLast;
	CCArray* chainSelected;

};


