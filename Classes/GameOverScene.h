
#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;

class GameOverScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);
private:
	void goToNewGame(Ref* sender);
	void goToMainMenu(Ref* sender);

};

#endif // __GAME_OVER_SCENE_H__
