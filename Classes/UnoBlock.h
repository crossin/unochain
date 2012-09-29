#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class UnoBlock :
	public CCNode
{
public:
	UnoBlock(void);
	~UnoBlock(void);

	static UnoBlock* unoblock(int idx=0, int clr=0);
	virtual bool init(int idx, int clr);
	//CREATE_FUNC(UnoBlock);

	CCRect getRect();
	void setCoord(int c, int r);
	void moveToDest();

	CCSprite* sprite;
	int unoIndex;
	int unoColor;
	bool inChain;
	int col;
	int row;
};