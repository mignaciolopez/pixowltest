#include "Fish.h"

USING_NS_CC;

Fish * Fish::createFish()
{
	return Fish::create();
}

bool Fish::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::initWithSpriteFrameName(TP::TP_graphics::fish01))
	{
		cocos2d::log("[Fish]::init() | Problem loading %s", TP::TP_graphics::fish01.c_str());
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto conf = Configuration::getInstance();

	m_fishScale = conf->getValue("fishScale", (Value)0.2f).asFloat();

	setScale(m_fishScale);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y);
	setRotation(-270.0f);

	return true;
}

void Fish::rotate(cocos2d::Vec2 touchLocation)
{
	auto pos = getPosition();

	float dx = touchLocation.x - pos.x;
	float dy = touchLocation.y - pos.y;

	float rot = CC_RADIANS_TO_DEGREES(std::atan2f(dy, dx));
	
	if (rot < 0.0f)
		rot += 360.0f;

	/*auto axn = RotateTo::create(0.2f, -rot);
	runAction(axn->clone());
	return;*/

	setRotation(-rot);

	//cocos2d::log("[Fish] rotation: %f", getRotation());
}
