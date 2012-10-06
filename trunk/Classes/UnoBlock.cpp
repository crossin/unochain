#include "UnoBlock.h"


UnoBlock::UnoBlock(void)
{
}


UnoBlock::~UnoBlock(void)
{
}

UnoBlock* UnoBlock::unoblock( int tp/*=0*/)
{
	UnoBlock* block = new UnoBlock;
	if (block && block->init(tp))
	{
		block->autorelease();
		return block;
	}
	return NULL;
}

bool UnoBlock::init( int tp )
{
	bool bRet = false;
	do{
		type = tp!=0 ? tp : int(CCRANDOM_0_1()*3)+1;
		switch (type)
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
		addChild(sprite);

		inChain = false;
		col = 0;
		row = 0;

		bRet=true;
	}while(0);
	return bRet;
}

CCRect UnoBlock::getRect()
{
	CCRect box = sprite->boundingBox();
	return CCRectMake(getPosition().x + box.origin.x, getPosition().y + box.origin.y, box.size.width, box.size.height);
}

void UnoBlock::setCoord( int c, int r )
{
	col = c;
	row = r;
	setPosition(getPosInGame());
}

void UnoBlock::moveToDest()
{
	float dist = getPositionY() - getPosInGame().y;
	if (dist > 0)
	{
		runAction(CCMoveTo::create(dist/500, getPosInGame()));
	}
}

CCPoint UnoBlock::getPosInGame()
{
	return ccp(col*45+25, row*40+20);
}