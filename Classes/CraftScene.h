#ifndef __CRAFT_SCENE_H__
#define __CRAFT_SCENE_H__

#include "cocos2d.h"
#include "Item.h"
#include <vector>
#include "ui/UIButton.h"
USING_NS_CC;
using namespace ui;

class CraftScene : Scene {

public:
	static Scene* createScene(RenderTexture* sqr, vector<Item*> cur);
	virtual bool init();
	void exit(Ref* sender);
	void setCurrentItem(vector<Item*> listItem) { currentItem = listItem; };
	static vector<Item*> getCurrentItem() { return currentItem; }
	virtual void update(float delta);
	void setItemCrafted();
	CREATE_FUNC(CraftScene);
	void getItemNeeded();
	void getItemNeeded2();
	void addDetail();
	void addDetail1();
	
private:
	bool checkItemInCurrentItem(Item* item);
	bool isCanCraft;
	bool crafting;
	bool crafting1;
	Sprite* items1;
	Sprite* items2;
	vector<bool> vectorCraft;
	vector<Button*> buttonCraft;
	static vector<Item*> currentItem;
	vector<Item*> itemNeeded;
	vector<Item*> itemCrafted;
};

#endif // __CRAFT_SCENE_H__
