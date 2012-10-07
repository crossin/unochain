#include "ScenePlay.h"
#include "SceneEnd.h"

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
		UnoBlock* pSymbol;
		for (int i = 0; i < COUNT_COL; i++)
		{
			for(int j = 0; j < COUNT_ROW; j++)
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
		gametime = 30;
		pointWin = 50;
		pointNow = 0;

		// ui
		textTime = CCLabelTTF::create("", "Arial", 24);
		CC_BREAK_IF(!textTime);
		textTime->setPosition(ccp(300, 460));
		addChild(textTime);
		
		progressbar = CCSprite::create("bar.png");
		CC_BREAK_IF(!progressbar);
		progressbar->setPosition(ccp(20, 450));
		progressbar->setAnchorPoint(CCPointZero);
		progressbar->setTextureRect(CCRectMake(0,0,0,20));
		addChild(progressbar);

		bRet = true;
	} while (0);

	setTouchEnabled(true);

 	//schedule( schedule_selector(ScenePlay::update));
	scheduleUpdate();

	return bRet;
}

void ScenePlay::update(float dt)
{
	gametime -= dt;
	char strTime[4];
	sprintf(strTime, "%d", (int)gametime);
	textTime->setString(strTime);
	if (gametime < 0)
	{
		CCDirector::sharedDirector()->replaceScene(SceneEnd::scene());
	}
};


void ScenePlay::ccTouchesBegan( CCSet* touches, CCEvent* event )
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint m_tTouchPos = convertTouchToNodeSpace(touch);

	UnoBlock* pBlock;
	CCRect rect;
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
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
		// add point
		pointNow += chainSelected->count();
		if (pointNow >= pointWin)
		{
			CCDirector::sharedDirector()->replaceScene(SceneEnd::scene(true));
		}
		progressbar->setTextureRect(CCRectMake(0,0,240.0*pointNow/pointWin,20));
	}

	chainSelected->removeAllObjects();
}

void ScenePlay::touchBlock( UnoBlock* block )
{
	UnoBlock* blockLast;
	if (!block->inChain)
	{
		// add to chain
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
				/*&& block->type == blockLast->type*/)
			{
				chainSelected->addObject(block);
				block->inChain = true;
				block->sprite->setOpacity(127);
			}
		}
	}
	else
	{
		// remove from chain
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
	for (int i = block->row; i < COUNT_ROW-1; i++)
	{
		arena[c][i] = arena[c][i+1];
		arena[c][i]->row--;
	}
	UnoBlock* pBlock = UnoBlock::unoblock();
	pBlock->setCoord(c, COUNT_ROW-1);
	pBlock->setPositionY(arena[c][COUNT_ROW-2]->getPositionY()+40);
	addChild(pBlock);
	arena[c][COUNT_ROW-1] = pBlock;
}

void ScenePlay::moveBlocks()
{
	//UnoBlock* pBlock;
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
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
