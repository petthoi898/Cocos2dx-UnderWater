#include "CraftScene.h"
#include "cocos2d.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"
#include <list>
USING_NS_CC;
using namespace ui;


vector<Item*> CraftScene::currentItem;
Scene* CraftScene::createScene(RenderTexture* sqr, vector<Item*> cur) {

	currentItem = cur;
	auto scene = Scene::create();
	auto layer = CraftScene::create();
	scene->addChild(layer, 1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	back_sqr->setFlippedY(true);
	back_sqr->setColor(Color3B::GRAY);
	scene->addChild(back_sqr);
	return scene;
}


bool CraftScene::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	getItemNeeded();
	
	auto back = Sprite::create("Crafting.png");
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	back->setScale(3);
	addChild(back);

	//add button items
	auto btn_items1 = Button::create("items/49.png");
	btn_items1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.5));
	btn_items1->setScale(2);

	btn_items1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			addDetail();
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	this->addChild(btn_items1, 1);

	items1 = Sprite::create("items/49.png");
	items1->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.5));
	items1->setVisible(false);
	addChild(items1, 2);

	auto btn_items2 = Button::create("items/106.png");
	btn_items2->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.75));
	//btn_items2->setScale(2);

	btn_items2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			addDetail1();
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	items2 = Sprite::create("items/49.png");
	items2->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 1.75));
	//items2->setVisible(false);

	this->addChild(btn_items2, 1);
	addChild(items2);

	
	//craftButton->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2);
	auto exit = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(CraftScene::exit, this));
	exit->setPosition(exit->getPositionX() + 250, exit->getPositionY() + 200);
	exit->setScale(0.7);
	auto menu = Menu::create(exit, NULL);
	menu->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 2);
	addChild(menu);


	this->scheduleUpdate();

	return true;
}
void CraftScene::getItemNeeded() {
	auto name = "items/19.png";
	auto name2 = "items/20.png";
	auto item = new Item(0, name, name, name, 1, name, Sprite::create(name));
	auto item2 = new Item(0, name2, name2, name2, 1, name2, Sprite::create(name2));
	itemNeeded.push_back(item);
	itemNeeded.push_back(item2);
}
void CraftScene::addDetail()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto detail = Sprite::create("detail/Sword.png");
	crafting = false;
	detail->setPosition(visibleSize.width / 1.6, visibleSize.height / 2);
	detail->setScale(2.2);
	addChild(detail, 1);
	//add btn_craft
	auto btn_Craft = Button::create("craft.png", "craft1.png");
	btn_Craft->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height / 4.5));
	btn_Craft->setScale(0.5);
	btn_Craft->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			CCLOG("Touch");
			crafting = true;
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			//crafting = false;
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	this->addChild(btn_Craft, 3);
}
void CraftScene::addDetail1()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto detail = Sprite::create("detail/Potion.png");
	crafting1 = false;
	detail->setPosition(visibleSize.width / 1.6, visibleSize.height / 2);
	detail->setScale(2.2);
	addChild(detail, 1);

	//add btn_craft
	auto btn_Craft = Button::create("craft.png", "craft1.png");
	btn_Craft->setPosition(Vec2(visibleSize.width / 1.4, visibleSize.height / 4.5));
	btn_Craft->setScale(0.5);
	btn_Craft->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			crafting1 = true;
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			crafting1 = false;
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	this->addChild(btn_Craft, 3);
}

void CraftScene::exit(Ref* sender) {
	Director::getInstance()->popScene();
	Director::getInstance()->resume();
}

bool CraftScene::checkItemInCurrentItem(Item* item) {
	for (auto it : currentItem) {
		if (it->getItemName() == item->getItemName()) return true;
	}
	return false;
}

void CraftScene::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	bool canCraft = true;
	if (crafting) {
		for (auto item : itemNeeded) {
			if (!checkItemInCurrentItem(item))
			{
				canCraft = false;
				break;
			}
		}
		if (canCraft) {
			auto notice = Sprite::create("craft done.png");
			notice->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			addChild(notice, 5);
			auto name = "items/49";
			auto item = new Item(0, name, name, name, 1, name, Sprite::create(name));
			for (auto item : itemNeeded) {
				auto it = currentItem.begin();
				for (int i = 0; i < currentItem.size(); i++) {
					it = it + 1;
					if (item->getItemName() == (*it)->getItemName()) {
						currentItem.erase(it, it + 1);
						++i;
					}

				}
			}
			currentItem.push_back(item);
			

		}
		else {
			auto notice = Sprite::create("craft fail.png");
			notice->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			addChild(notice, 5);
		}
		crafting = false;
	}
}
