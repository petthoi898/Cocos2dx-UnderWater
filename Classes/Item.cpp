#include "Item.h"
#include "cocos2d.h"

USING_NS_CC;


Item::Item() :  ID(-1), name(NULL), description(NULL), img(NULL), usable(false), type(NULL) {

}
Item& Item::operator=(const Item& item) {
	
	ID = item.ID;
	name = item.name;
	description = item.description;
	img = item.img;
	usable = item.usable;
	type = item.type;
	this->item = item.item;
	return *this;
}