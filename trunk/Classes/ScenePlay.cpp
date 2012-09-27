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
		UnoBlock* pSymbol;
		for (int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 12; j++)
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
	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 12; j++)
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
	CCARRAY_FOREACH(chainSelected, obj)
	{
		pBlock = (UnoBlock*)obj;
		pBlock->inChain = false;
		pBlock->sprite->setOpacity(255);
	}
	chainSelected->removeAllObjects();
}

void ScenePlay::touchBlock( UnoBlock* block )
{
	if (!block->inChain)
	{
		if (chainSelected->count() == 0)
		{
			//blockLast = block;
			chainSelected->addObject(block);
			block->inChain = true;
			block->sprite->setOpacity(122);
		} 
		else
		{
			UnoBlock* blockLast = (UnoBlock*)chainSelected->lastObject();
			// adjacent && (same color/index)
			if (((block->col==blockLast->col && abs(block->row-blockLast->row)==1)
					|| (block->row==blockLast->row && abs(block->col-blockLast->col)==1))
				&& (block->unoColor == blockLast->unoColor || block->unoIndex == blockLast->unoIndex))
			{
				chainSelected->addObject(block);
				block->inChain = true;
				block->sprite->setOpacity(122);
			}
		}
	}
}



// void ScenePlay::updateFrame( CCTime dt )
// {
// 
// }
