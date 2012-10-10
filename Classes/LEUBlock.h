#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class LEUBlock :
	public CCNode
{
public:
	LEUBlock(void);
	~LEUBlock(void);

	static LEUBlock* create(int tp=0);
	virtual bool init(int tp);
	//CREATE_FUNC(Block);

	static const int COUNT_TYPE = 3;

	CCRect getRect();
	void setCoord(int c, int r);
	void moveToDest();
	CCPoint getPosInGame();
	void setPosAbove(LEUBlock* blk);

	CCSprite* sprite;
	int type;
	bool inChain;
	int col;
	int row;
};