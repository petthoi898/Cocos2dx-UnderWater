/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PauseGameScene.h"
#include "Definitions.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "MainMenuScene.h"
using namespace ui;
USING_NS_CC;

Scene* PauseGame::createScene(RenderTexture* sqr) {
	auto scene = Scene::create();
	auto layer = PauseGame::create();
	scene->addChild(layer, 1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	back_sqr->setFlippedY(true);
	back_sqr->setColor(Color3B::GRAY);
	scene->addChild(back_sqr);
	return scene;
}
bool PauseGame::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

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
	
	auto buttonContinue = MenuItemImage::create("gamecontrol/Continue Button.png", "gamecontrol/Continue Button.png",
		CC_CALLBACK_1(PauseGame::menuContinueGame, this));
	buttonContinue->setScale(0.5f);
	auto buttonRestart = MenuItemImage::create("gamecontrol/Start Button.png", "gamecontrol/Start Button.png",
		CC_CALLBACK_1(PauseGame::menuRestartGame, this));
	buttonRestart->setPosition(Point(buttonContinue->getPositionX(), buttonContinue->getPositionY() + 100));
	buttonRestart->setScale(0.5f);
	auto buttonControl = MenuItemImage::create("gamecontrol/Controls Button.png", "gamecontrol/Controls Button.png",
		CC_CALLBACK_1(PauseGame::menuGoToMainMenu, this));
	buttonControl->setScale(0.5f);
	buttonControl->setPosition(Point(buttonContinue->getPositionX(), buttonContinue->getPositionY() - 100));


	auto menu = Menu::create(buttonContinue, buttonControl,buttonRestart, NULL);
	this->addChild(menu, 1);
	
	return true;
}
void PauseGame::menuContinueGame(Ref* sender) {
	Director::getInstance()->popScene();
	Director::getInstance()->resume();
}
void PauseGame::menuGoToMainMenu(Ref* sender) {

}

void PauseGame::menuRestartGame(Ref* sender) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	Director::getInstance()->resume();

}