#include "cocos2d.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;


Scene* GameOverScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameOverScene::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto retry = MenuItemImage::create("Retry Button Clicked.png", "Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::goToNewGame, this));
	retry->setPosition(Vec2(visibleSize.width / 8, visibleSize.height / 4));
	auto goToMenu = MenuItemImage::create("Play Button Clicked.png", "Play Button Clicked.png", CC_CALLBACK_1(GameOverScene::goToMainMenu, this));
	goToMenu->setPosition(Vec2(visibleSize.width * 3 / 8, visibleSize.height / 4));
	auto menu = Menu::create(retry, goToMenu, NULL);
	addChild(menu, 1000);
	return true;
}
void GameOverScene::goToNewGame(Ref* sender) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
void GameOverScene::goToMainMenu(Ref* sender) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}