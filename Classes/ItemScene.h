#ifndef __ITEM_SCENE_H__
#define __ITEM_SCENE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
USING_NS_CC;


class ItemScene : Scene {

public:
	static Scene* createScene(RenderTexture* sqr);
	virtual bool init();
	void exit(Ref* sender);
	void loadAllItem();
	virtual bool onTouchBegan(Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, cocos2d::Event *pEvent);

	CREATE_FUNC(ItemScene);
private:
	vector<Item*> listItem;
	bool isTouchItem;
};

#endif // __ITEM_SCENE_H__
