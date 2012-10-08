#pragma once
#include "sceneplay.h"
class ScenePlayPuzzle :
	public ScenePlay
{
public:
	ScenePlayPuzzle(void);
	~ScenePlayPuzzle(void);

	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(ScenePlayPuzzle);

	void clearChain();
};

