#pragma once
#include "sceneplay.h"
class ScenePlayEndless :
	public ScenePlay
{
public:
	ScenePlayEndless(void);
	~ScenePlayEndless(void);

	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(ScenePlayEndless);

	void clearChain();

	CCLabelTTF* textScore;
	int pointNow;
};

