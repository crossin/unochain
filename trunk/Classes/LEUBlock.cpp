#include "LEUBlock.h"
#include "ScenePlay.h"


LEUBlock::LEUBlock(void)
{
}


LEUBlock::~LEUBlock(void)
{
}

LEUBlock* LEUBlock::create( int tp/*=0*/)
{
	LEUBlock* block = new LEUBlock;
	if (block && block->init(tp))
	{
		block->autorelease();
		return block;
	}
	return NULL;
}

bool LEUBlock::init( int tp )
{
	bool bRet = false;
	do{
		type = tp!=0 ? tp : int(CCRANDOM_0_1()*COUNT_TYPE)+1;
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

CCRect LEUBlock::getRect()
{
	CCRect box = sprite->boundingBox();
	return CCRectMake(getPosition().x + box.origin.x, getPosition().y + box.origin.y, box.size.width, box.size.height);
}

void LEUBlock::setCoord( int c, int r )
{
	col = c;
	row = r;
	setPosition(getPosInGame());
}

void LEUBlock::moveToDest()
{
	float dist = getPositionY() - getPosInGame().y;
	if (dist > 0)
	{
		runAction(CCMoveTo::create(dist/500, getPosInGame()));
	}
}

CCPoint LEUBlock::getPosInGame()
{
	return ccp(col*GRID_LENGTH+25, row*GRID_LENGTH+20);
}

void LEUBlock::setPosAbove( LEUBlock* blk )
{
	int yBase = blk->getPositionY();
	setPositionY(yBase>(ScenePlay::COUNT_ROW-1)*GRID_LENGTH+20 ? yBase+55 : yBase+90);
}
