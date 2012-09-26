#include "UnoBlock.h"


UnoBlock::UnoBlock(void)
{
}


UnoBlock::~UnoBlock(void)
{
}

UnoBlock* UnoBlock::unoblock( int idx/*=0*/, int clr/*=0*/ )
{
	UnoBlock* block = new UnoBlock;
	if (block && block->init(idx, clr))
	{
		block->autorelease();
		return block;
	}
	return NULL;
}

bool UnoBlock::init( int idx, int clr )
{
	bool bRet = false;
	do{
		m_index = idx!=0 ? idx : int(CCRANDOM_0_1()*3)+1;
		m_color = clr!=0 ? clr : int(CCRANDOM_0_1()*3)+1;
		switch (m_index)
		{
		case 1:
		default:
			sprite = CCSprite::create("symbol1.png");
			break;
		case 2:
			sprite = CCSprite::create("symbol2.png");
			break;
		case 3:
			sprite = CCSprite::create("symbol3.png");
			break;
		}
		switch (m_color)
		{
		case 1:
		default:
			sprite->setColor(ccc3(200,100,100));
			break;
		case 2:
			sprite->setColor(ccc3(100,200,100));
			break;
		case 3:
			sprite->setColor(ccc3(100,100,200));
			break;
		}
		addChild(sprite);

		bRet=true;
	}while(0);
	return bRet;
}

cocos2d::CCRect UnoBlock::getRect()
{
	CCRect box = sprite->boundingBox();
	return CCRectMake(getPosition().x + box.origin.x, getPosition().y + box.origin.y, box.size.width, box.size.height);
}
