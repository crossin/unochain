#include "ScenePlay.h"
#include "SceneEnd.h"
#include "libxml\tree.h"

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
// 		LEUBlock* pSymbol;
// 		for (int i = 0; i < COUNT_COL; i++)
// 		{
// 			for(int j = 0; j < COUNT_ROW; j++)
// 			{
// 				pSymbol = LEUBlock::create();
// 				CC_BREAK_IF(!pSymbol);
// 				pSymbol->setCoord(i, j);
// 				addChild(pSymbol);
// 				arena[i][j] = pSymbol;
// 			}
// 		}

		chainSelected = CCArray::create();
		chainSelected->retain();



		bRet = true;
	} while (0);

	setTouchEnabled(true);

 	//schedule( schedule_selector(ScenePlay::update));
	scheduleUpdate();

	return bRet;
}


void ScenePlay::ccTouchesBegan( CCSet* touches, CCEvent* event )
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint m_tTouchPos = convertTouchToNodeSpace(touch);

	LEUBlock* pBlock;
	//CCRect rect;
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
		{
			if (pBlock = arena[i][j])
			{
				//rect = pBlock->getRect();
				if (pBlock->getRect().containsPoint(m_tTouchPos))
				{
					touchBlock(pBlock);
				}
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
	LEUBlock* pBlock;
	if (chainSelected->count() < 3)
	{
		CCARRAY_FOREACH(chainSelected, obj)
		{
			pBlock = (LEUBlock*)obj;
			pBlock->inChain = false;
			pBlock->sprite->setOpacity(255);
		}
	} 
	else
	{
		clearChain();
		checkNoMoves();
	}

	chainSelected->removeAllObjects();
}


void ScenePlay::clearChain()
{
	clearAndRefill(true);
}

void ScenePlay::clearAndRefill( bool refillable )
{
	CCObject* obj;
	LEUBlock* pBlock;
	CCARRAY_FOREACH(chainSelected, obj)
	{
		pBlock = (LEUBlock*)obj;
		removeChild(pBlock, true);
		clearBlock(pBlock, refillable);
	}
	moveBlocks();
}


void ScenePlay::touchBlock( LEUBlock* block )
{
	LEUBlock* blockLast;
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
			blockLast = (LEUBlock*)chainSelected->lastObject();
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
		blockLast = (LEUBlock*)chainSelected->lastObject();
		while ( blockLast != block)
		{
			chainSelected->removeLastObject(true);
			blockLast->inChain = false;
			blockLast->sprite->setOpacity(255);
			blockLast = (LEUBlock*)chainSelected->lastObject();
		}
	}
}


void ScenePlay::clearBlock( LEUBlock* block, bool refillable)
{
	int c = block->col;
	for (int i = block->row; i < COUNT_ROW-1; i++)
	{
		arena[c][i] = arena[c][i+1];
		if (arena[c][i])
		{
			arena[c][i]->row--;
		}
	}
	if (refillable)
	{
		LEUBlock* pBlock = LEUBlock::create();
		pBlock->setCoord(c, COUNT_ROW-1);
		pBlock->setPosAbove(arena[c][COUNT_ROW-2]);
		addChild(pBlock);
		arena[c][COUNT_ROW-1] = pBlock;	
	}
	else
	{
		arena[c][COUNT_ROW-1] = NULL;
	}
}

void ScenePlay::moveBlocks()
{
	//Block* pBlock;
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
		{
			//arena[i][j]->setCoord(i, j);
			if (arena[i][j])
			{
				arena[i][j]->moveToDest();
			}
		}
	}
}

void ScenePlay::checkNoMoves()
{
	int numSame;
	int tp;
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
		{
			if (arena[i][j])
			{
				numSame = 0;
				tp = arena[i][j]->type;
				if (j+1 < COUNT_ROW && arena[i][j+1] && arena[i][j+1]->type == tp)
				{
					numSame++;
				}
				if (i+1 < COUNT_COL && arena[i+1][j] && arena[i+1][j]->type == tp)
				{
					numSame++;
				}
				if (j-1 >= 0 && arena[i][j-1] && arena[i][j-1]->type == tp)
				{
					numSame++;
				}
				if (i-1 >= 0 && arena[i-1][j] && arena[i-1][j]->type == tp)
				{
					numSame++;
				}
				if (numSame > 1)
				{
					return;
				}
			}
		}
	}
	// mo move
	CCDirector::sharedDirector()->replaceScene(SceneEnd::scene());
}

void ScenePlay::loadMap( char* filename )
{
	xmlDocPtr doc;           
	xmlNodePtr curNode;

	doc = xmlReadFile(filename,"UTF-8",XML_PARSE_NOBLANKS);

	if (NULL == doc)
	{
		return;
	}

	curNode = xmlDocGetRootElement(doc); 
	if (NULL == curNode)
	{
		xmlFreeDoc(doc);
		return;
	}

	if (xmlStrcmp(curNode->name, BAD_CAST "level"))
	{
		xmlFreeDoc(doc);
		return;
	}

	curNode = curNode->xmlChildrenNode;

	while(curNode != NULL)
	{

		// get map
		if (!xmlStrcmp(curNode->name, (const xmlChar *)"map"))
		{
			CCString* str = new CCString((const char*)xmlNodeGetContent(curNode));
			const char* map = str->getCString();
			int tp;
			for (int i = 0; i < COUNT_COL; i++)
			{
				for(int j = 0; j < COUNT_ROW; j++)
				{
					if (arena[i][j])
					{
						removeChild(arena[i][j], true);
						arena[i][j] = NULL;
					}
					tp = map[i*COUNT_ROW+j] - '0';
					arena[i][j] = LEUBlock::create(tp);
					arena[i][j]->setCoord(i, j);
					addChild(arena[i][j]);
				}
			}
			str->release();
		}


		curNode = curNode->next;
	}

	xmlFreeDoc(doc);
}



// void ScenePlay::updateFrame( CCTime dt )
// {
// 
// }
