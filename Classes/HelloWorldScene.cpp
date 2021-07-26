
#include "HelloWorldScene.h"
#include "UnderWaterScene.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "CraftScene.h"
USING_NS_CC;
Node* HelloWorld::cameraView = NULL;
Scene* HelloWorld::createScene()
{

	/*auto scene = Scene::create();
    auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;*/
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 

	_tileMap = TMXTiledMap::create("maps/test_new_tilesset.tmx");
	_background = _tileMap->getLayer("Background");
	//_blockage = _tileMap->getLayer("Blockage");
	//_blockage->setVisible(false);
	addChild(_tileMap, -1);
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Object");
	CCASSERT(NULL != objects, "'Object-Player' object group not found");
	auto playerShowUpPoint = objects->getObject("spawnpoint");
	CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");

	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();
	//init list item

	auto telePort = objects->getObject("teleport");

	int telePortX = telePort["x"].asInt();
	int telePortY = telePort["y"].asInt();

	tele = Sprite::create("teleport.png");
	tele->setPosition(telePortX, telePortY);
	tele->setScale(0.5f);
	addChild(tele, 1);
	//tele->setVisible(false);
	cameraView = Node::create();
	cameraView->setContentSize(visibleSize);

	for (int i = 1; i <= 20; i++) {
		char imageName[100] = { 0 };
		sprintf(imageName, "items/%d.png", i);
		auto sprite = Sprite::create(imageName);
		auto item = new Item(i, imageName, imageName, imageName, 0, imageName, sprite);
		addChild(item->getSprite(), 5);
		//this->addChild(item->getSprite(), 100);
		item->getSprite()->setVisible(false);
		listItem.push_back(item);
	}

	// spawn enemy
	auto groupEnemy = _tileMap->getObjectGroup("Monster");
	CCASSERT(NULL != groupEnemy, "'Enemy' object group not found");

	auto monster = groupEnemy->getObjects();
	auto iteratorMonster = monster.begin();
	for (; iteratorMonster != monster.end(); iteratorMonster++) {
		ValueMap& dict = (*iteratorMonster).asValueMap();
		if ("dragon" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyDragon(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x,y));
			enemySprite->type = "dragon";
			addChild(enemySprite, 1);
		}
		else if ("Medusa" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyMedusa(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x,y));
			enemySprite->type = "medusa";
			addChild(enemySprite, 1);
		}
		else if ("Medon" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyDemon(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x, y));
			enemySprite->type = "demon";
			addChild(enemySprite, 1);
		}
	}
	
	hero = Hero::create();
	hero->InitHeroSprite("character/hero_idle1.png");
	hero->setPosition(x,y);
	hero->setScale(2.2f);
	this->addChild(hero, 1);

	
	this->addChild(cameraView , 4);
	this->runAction(Follow::create(cameraView));
	setViewPointCenter(hero->getPosition());



	initHRocker();

	cameraView->addChild(rocker);
	
	auto characterInfo = Node::create();
	characterInfo->setPosition(Point(-320, 330));
	cameraView->addChild(characterInfo);

	view = new ProgressView();
	view->setScale(2.2f);
	view->setBackgroundTexture("character/xue_back.png");
	view->setForegroundTexture("character/xue_fore.png");
	view->setTotalProgress(100);
	view->setCurrentProgress(100);

	aroundCharacter = Sprite::create("character/kuang.png");
	character = Sprite::create("character/touxiang.png");
	character->setPosition(Point(-120, 0));

	characterInfo->addChild(character, 2);
	characterInfo->addChild(aroundCharacter, 2);
	characterInfo->addChild(view, 2);

	rocker->setQuickItem(listItem);
	enemyCount = enemy.size();
	this->scheduleUpdate();

    return true;
}

void HelloWorld::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getVisibleSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	if (viewPoint.x > winSize.width / 2) {
		cameraView->setPosition(viewPoint);
	}
	else cameraView->setPosition(actualPosition);
}

void HelloWorld::update(float delta)
{
	setViewPointCenter(hero->getPosition());
	
	auto heroX = hero->getPositionX();
	auto heroY = hero->getPositionY();
	usingItem(rocker->scaleAt);
	if (rocker->isInAttack) {
		hero->getAttackAmination();
		for (int i = 0; i < enemy.size(); i++) {
			if (!enemy.at(i)->isDead) {
				auto position = enemy.at(i)->enemySprite->getPositionY();
				if (std::abs(hero->getPositionY() - position) < 30)
				{
					if (isRectCollision(Rect(heroX, heroY, 32, 32),
						Rect(enemy.at(i)->enemySprite->getPositionX(), enemy.at(i)->enemySprite->getPositionY(), 256, 256)))
					{
						combat(enemy.at(i));
						enemy.at(i)->isHurt = true;
					}
				}
			}
			else {
				auto itemX = enemy.at(i)->itemEnemy->getSprite()->getPositionX();
				auto itemY = enemy.at(i)->itemEnemy->getSprite()->getPositionY();
				auto ene = enemy.at(i);
				if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
							//rocker->setQuickItem(listItem);
						}

					}
				}
			}
			rocker->isInAttack = false;
		}

	}
	if (enemyCount != 0) {
		tele->setVisible(true);
		if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(tele->getPositionX(), tele->getPositionY(), tele->getContentSize().width, tele->getContentSize().height))) {
			auto infor = new Information(rocker, hero, cameraView, view, listItem);
			auto scene = UnderWater::createScene(infor);
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
		}
	}
	//load item
	rocker->loadQuickItem(cameraView->getPosition(), cameraView->getContentSize());
	// run 
	switch (rocker->rocketDirection)
	{
	case 1:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x + 5, hero->getPosition().y)); // right away  
		break;
	case  2:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y + 5));   // go up  
		break;
	case 3:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x - 5, hero->getPosition().y));   //turn left  
		break;
	case 4:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y - 5));   // go down  
		break;
	default:
		hero->StopAnimation();
		break;

	}
}
bool HelloWorld::isRectCollision(Rect rect1, Rect rect2) {

	float x1 = rect1.origin.x;
	float y1 = rect1.origin.y;
	float w1 = rect1.size.width;
	float h1 = rect1.size.height;
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1 + w1 * 0.5 < x2 - w2 * 0.5)
		return false;
	else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)
		return false;
	else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)
		return false;
	else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
		return false;

	return true;
}
void HelloWorld::combat(Enemy* ene) {
	auto position = ene->enemySprite->getPositionY();
	auto heroX = hero->getPositionX();
	auto heroY = hero->getPositionY();
	if (std::abs(hero->getPositionY() - position) < 30)
	{
		if (isRectCollision(Rect(heroX, heroY, 32, 32),
			Rect(ene->enemySprite->getPositionX(), ene->enemySprite->getPositionY(), 256, 256)))
		{
			if ("dragon" == ene->type) {
				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getDragonDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				auto a = view->getCurrentProgress();
				if (view->getCurrentProgress() <= 0) {
					auto scene = GameOverScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
				}
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
						}

					}
					enemyCount--;
				}
			}
			else if ("medusa" == ene->type) {
				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getMedusaDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				if (view->getCurrentProgress() <= 0) {
					auto scene = GameOverScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
				}
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
							//rocker->setQuickItem(listItem);
						}

					}
					enemyCount--;

				}
			}
			else if ("demon" == ene->type) {
				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getDemonDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				if (view->getCurrentProgress() <= 0) {
					auto scene = GameOverScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
				}
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
						}

					}
					enemyCount--;

				}
			}
		}
	}
}

void HelloWorld::initHRocker() {
	rocker = HRocker::createHRocker("joystick_center.png", "joystick_bg.png", Point(100, 100), listItem);// where the first picture is a rocker button, the second as the background  
	rocker->setPosition(-cameraView->getContentSize().width / 2, -cameraView->getContentSize().height / 2);
	rocker->setTag(50);
	rocker->startRocker(true);
}
void HelloWorld::usingItem(int scaleAt) {
	auto quickSlot = rocker->quickItem;
	if (rocker->isCraft) {
		collectedItem = CraftScene::getCurrentItem();
	}
	if (scaleAt < 0) return;
	if ("weapon" != quickSlot.at(scaleAt)->getItemType()) rocker->isInAttack = false;
	else {
		hero->setHeroDamage(hero->getHeroDamage() + quickSlot.at(scaleAt)->getItemID());
	}

	if ("items/1.png" == quickSlot.at(scaleAt)->getItemName()) {
		switch (rocker->facePos)
		{
		case 1:
			hero->setVisible(false);

			hero->setPosition(Point(hero->getPosition().x + ITEMHIDE, hero->getPosition().y)); // right away  

			hero->setVisible(true);
			break;
		case  2:
			hero->setVisible(false);

			hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y + ITEMHIDE));   // go up 
			hero->setVisible(true);

			break;
		case 3:
			hero->setVisible(false);

			hero->setPosition(Point(hero->getPosition().x - ITEMHIDE, hero->getPosition().y));   //turn left  
			hero->setVisible(true);

			break;
		case 4:
			hero->setVisible(false);

			hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y - ITEMHIDE));   // go down  
			hero->setVisible(true);

			break;
		default:
			break;

		}
		auto it = quickSlot.begin();
		for (int i = 0; i < scaleAt; i++) {
			it++;
		}
		scaleAt = -1;
		(*it)->getSprite()->setVisible(false);
		quickSlot.erase(it);
		collectedItem = quickSlot;
		rocker->setQuickItem(quickSlot);
		rocker->setQuickItem(collectedItem);
		rocker->facePos = -1;
		CCLOG("In here");
	}

}
