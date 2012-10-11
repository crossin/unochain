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

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    //void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
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

