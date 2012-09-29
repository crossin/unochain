#include "ScenePlay.h"

ScenePlay::ScenePlay(void)
{
}


ScenePlay::~ScenePlay(void)
{
	if (chainSelected)
	{
		chainSelected->release();
		chainSelected = NULL;
	}
}

CCScene* ScenePlay::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlay *layer = ScenePlay::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlay::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// init game
		countCol = 8;
		countRow = 12;
		UnoBlock* pSymbol;
		for (int i = 0; i < countCol; i++)
		{
			for(int j = 0; j < countRow; j++)
			{
				pSymbol = UnoBlock::unoblock();
				CC_BREAK_IF(!pSymbol);
				pSymbol->setCoord(i, j);
				addChild(pSymbol);
				arena[i][j] = pSymbol;
			}
		}

		chainSelected = CCArray::create();
		chainSelected->retain();

		//blockLast = NULL;





		bRet = true;
	} while (0);

	setTouchEnabled(true);

	//schedule( schedule_selector(ScenePlay::updateFrame));

	return bRet;
}


void ScenePlay::ccTouchesBegan( CCSet* touches, CCEvent* event )
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint m_tTouchPos = convertTouchToNodeSpace(touch);

	UnoBlock* pBlock;
	CCRect rect;
	for (int i = 0; i < countCol; i++)
	{
		for(int j = 0; j < countRow; j++)
		{
			pBlock = arena[i][j];
			rect = pBlock->getRect();
			if (rect.containsPoint(m_tTouchPos))
			{
				touchBlock(pBlock);
			}
		}
	}
}

void ScenePlay::ccTouchesMoved( CCSet* touches, CCEvent* event )
{
	ccTouchesBegan(touches, event);
}

void ScenePlay::ccTouchesEnded( CCSet* touches, CCEvent* event )
{
	CCObject* obj;
	UnoBlock* pBlock;

	if (chainSelected->count() < 3)
	{
		CCARRAY_FOREACH(chainSelected, obj)
		{
			pBlock = (UnoBlock*)obj;
			pBlock->inChain = false;
			pBlock->sprite->setOpacity(255);
		}
	} 
	else
	{
		CCARRAY_FOREACH(chainSelected, obj)
		{
			pBlock = (UnoBlock*)obj;
			removeChild(pBlock, true);
			clearBlock(pBlock);
			moveBlocks();
		}
	}

	chainSelected->removeAllObjects();
}

void ScenePlay::touchBlock( UnoBlock* block )
{
	UnoBlock* blockLast;
	if (!block->inChain)
	{
		if (chainSelected->count() == 0)
		{
			//blockLast = block;
			chainSelected->addObject(block);
			block->inChain = true;
			block->sprite->setOpacity(127);
		} 
		else
		{
			blockLast = (UnoBlock*)chainSelected->lastObject();
			// adjacent && (same color/index)
			if (((block->col==blockLast->col && abs(block->row-blockLast->row)==1)
					|| (block->row==blockLast->row && abs(block->col-blockLast->col)==1))
				&& (block->unoColor == blockLast->unoColor || block->unoIndex == blockLast->unoIndex))
			{
				chainSelected->addObject(block);
				block->inChain = true;
				block->sprite->setOpacity(127);
			}
		}
	}
	else
	{
		blockLast = (UnoBlock*)chainSelected->lastObject();
		while ( blockLast != block)
		{
			chainSelected->removeLastObject(true);
			blockLast->inChain = false;
			blockLast->sprite->setOpacity(255);
			blockLast = (UnoBlock*)chainSelected->lastObject();
		}
	}
}

void ScenePlay::clearBlock( UnoBlock* block )
{
	int c = block->col;
	for (int i = block->row; i < countRow-1; i++)
	{
		arena[c][i] = arena[c][i+1];
		arena[c][i]->row--;
	}
	UnoBlock* pBlock = UnoBlock::unoblock();
	pBlock->setCoord(c, countRow-1);
	pBlock->setPositionY(arena[c][countRow-2]->getPositionY()+40);
	addChild(pBlock);
	arena[c][countRow-1] = pBlock;
}

void ScenePlay::moveBlocks()
{
	//UnoBlock* pBlock;
	for (int i = 0; i < countCol; i++)
	{
		for(int j = 0; j < countRow; j++)
		{
			//arena[i][j]->setCoord(i, j);
			arena[i][j]->moveToDest();
		}
	}
}



// void ScenePlay::updateFrame( CCTime dt )
// {
// 
// }
