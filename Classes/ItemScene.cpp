#include "ItemScene.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* ItemScene::createScene(RenderTexture* sqr) {
	auto scene = Scene::create();
	auto layer = ItemScene::create();
	scene->addChild(layer, 1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	back_sqr->setFlippedY(true);
	back_sqr->setColor(Color3B::GRAY);
	scene->addChild(back_sqr);
	return scene;
}

bool ItemScene::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("items/itembackground.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(3);
	addChild(background, -1);
	auto exit = MenuItemImage::create("items/exit.png", "items/exit.png", CC_CALLBACK_1(ItemScene::exit, this) );
	exit->setPosition(Point(background->getContentSize().width * 1.5,  background->getContentSize().height * 1.5f));
	exit->setScale(0.6f);
	auto menu = Menu::create(exit, NULL);
	addChild(menu, 1);

	// Load item
	loadAllItem();
	listItem.at(0)->getSprite()->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(listItem.at(0)->getSprite());

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->onTouchBegan = CC_CALLBACK_2(ItemScene::onTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(ItemScene::onTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(ItemScene::onTouchEnded, this);
	TouchListener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);
	return true;
}
void ItemScene::exit(Ref* sender) {
	Director::getInstance()->popScene();
	
}
void ItemScene::loadAllItem() {
	for (int i = 1; i <= 20; i++) {
		char imageName[100] = { 0 };
		sprintf(imageName, "items/%d.png", i);
		auto sprite = Sprite::create(imageName);
		auto item = new Item(i, imageName, imageName, imageName, 0, imageName, sprite);
		listItem.push_back(item);
	}
}
bool ItemScene::onTouchBegan(Touch* touch, Event* event) {
	CCLOG("Touched");
	auto pointTouch = convertTouchToNodeSpace(touch);
	for (auto item : listItem) {
		if (item->getSprite()->getBoundingBox().containsPoint(pointTouch));
		isTouchItem = true;
	}
	return true;
}
void ItemScene::onTouchEnded(Touch* touch, Event* event) {

}
void ItemScene::onTouchMoved(Touch * touch, Event* event) {

}
