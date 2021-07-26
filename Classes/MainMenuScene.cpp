
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

bool MainMenuScene::isStart = false;
Scene* MainMenuScene::createScene() {
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init() {
		auto visibleSize = Director::getInstance()->getVisibleSize();


		auto background = Sprite::create("sea_background/sea_background.png");
		addChild(background, -4);
		auto farground = Sprite::create("sea_background/farground.png");
		addChild(farground, -3);
		auto midground = Sprite::create("sea_background/mid_background.png");
		addChild(midground, -2);
		auto foreground = Sprite::create("sea_background/foreground.png");
		addChild(foreground, -1);
		background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		farground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		midground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		foreground->setPosition(visibleSize.width / 2, visibleSize.height / 2);

		schedule(CC_SCHEDULE_SELECTOR(MainMenuScene::spawnBubble), 1, CC_REPEAT_FOREVER, 0.1f);

		auto buttonControls = MenuItemImage::create("gamecontrol/Controls Button.png", "gamecontrol/Controls Button.png",
			CC_CALLBACK_1(MainMenuScene::menuOptionGame, this));
		buttonControls->setScale(0.5f);
		buttonControls->setPosition(buttonControls->getPosition() - Point(0, 150));
		auto buttonExit = MenuItemImage::create("gamecontrol/Exit Button.png", "gamecontrol/Exit Button.png",
			CC_CALLBACK_1(MainMenuScene::menuExitGame, this));
		buttonExit->setScale(0.5f);
		buttonExit->setPosition(Point(buttonControls->getPositionX(), buttonControls->getPositionY() - 100));
		auto buttonStart = MenuItemImage::create("gamecontrol/New Game Button.png", "gamecontrol/New Game Button.png",
			CC_CALLBACK_1(MainMenuScene::menuStartGame, this));
		buttonStart->setScale(0.5f);
		buttonStart->setPosition(Point(buttonControls->getPositionX(), buttonControls->getPositionY() + 100));
		auto menu = Menu::create(buttonControls, buttonStart, buttonExit, NULL);
		addChild(menu);
		isStart = true;
		auto nameGame = Sprite::create("underocean.png");
		nameGame->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);
		nameGame->setScale(2);
		addChild(nameGame, 1);


	return true;
}
void MainMenuScene::menuExitGame(Ref* sender) {
	Director::getInstance()->end();
}
void MainMenuScene::menuOptionGame(Ref* sender) {
	// turn off or on music

}
void MainMenuScene::menuStartGame(Ref* sender) {
	auto scene = HelloWorld::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}
void MainMenuScene::spawnBubble(float dt) {
	auto bubble = Sprite::create("sea_background/bubble.png");
	auto random = CCRANDOM_0_1();
	if (random > 0.5) {
		bubble->setScale(random - 0.4f);
	}
	else {
		bubble->setScale(random);
	}
	bubble->setPosition(random * 1000, random * 200);
	auto moveUp = MoveBy::create(3, random * Vec2(0, random * 600));
	cocos2d::CallFunc* A = cocos2d::CallFunc::create([=]() {
		// do something
		bubble->setVisible(false);
	});
	auto seq = Sequence::create(moveUp, A, NULL);
	bubble->runAction(seq);
	addChild(bubble, -3);
}