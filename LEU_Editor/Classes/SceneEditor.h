#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "LEUBlock.h"
#include "ScenePlay.h"

using namespace cocos2d;

class SceneEditor : public CCLayer
{
public:
	SceneEditor(void);
	~SceneEditor(void);

    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(SceneEditor);

	void ccTouchesEnded( CCSet* touches, CCEvent* event );
	void buttonCallback(CCObject* pSender);

	bool loadFromFile();
	bool saveToFile();

	LEUBlock* arena[ScenePlay::COUNT_COL][ScenePlay::COUNT_ROW];
	CCArray* sampleBlocks;
	LEUBlock* blockSelected;
	CCTextFieldTTF* txtFile;
};

#endif  // __HELLOWORLD_SCENE_H__

