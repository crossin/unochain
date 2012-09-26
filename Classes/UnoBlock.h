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

	CCSprite* sprite;
	int m_index;
	int m_color;
};