#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class UnoBlock :
	public CCNode
{
public:
	UnoBlock(void);
	~UnoBlock(void);

	static UnoBlock* unoblock(int tp=0);
	virtual bool init(int tp);
	//CREATE_FUNC(UnoBlock);

	CCRect getRect();
	void setCoord(int c, int r);
	void moveToDest();
	CCPoint getPosInGame();
	void setPosAbove(UnoBlock blk);
	CCSprite* sprite;
	int type;
	bool inChain;
	int col;
	int row;
};