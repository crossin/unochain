#pragma once
#include "cocos2d.h"
#include "Block.h"

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

	void update(float dt);
	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

	void touchBlock(Block* block);
	void clearBlock(Block* block);
	void moveBlocks();
	
	CCLabelTTF* textTime;
	CCSprite* progressbar;
	Block* arena[COUNT_COL][COUNT_ROW];
	//Block* blockLast;
	CCArray* chainSelected;
	float gametime;
	int pointWin;
	int pointNow;
};


