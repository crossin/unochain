#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Block :
	public CCNode
{
public:
	Block(void);
	~Block(void);

	static Block* create(int tp=0);
	virtual bool init(int tp);
	//CREATE_FUNC(Block);

	CCRect getRect();
	void setCoord(int c, int r);
	void moveToDest();
	CCPoint getPosInGame();
	void setPosAbove(Block* blk);

	CCSprite* sprite;
	int type;
	bool inChain;
	int col;
	int row;
};