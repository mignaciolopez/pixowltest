#include "Bubble.h"

USING_NS_CC;

Bubble * Bubble::createBubble()
{
	return Bubble::create();
}

bool Bubble::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::initWithSpriteFrameName(TP::TP_graphics::bubble))
	{
		cocos2d::log("[Bubble]::init() | Problem loading %s", TP::TP_graphics::bubble.c_str());
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	setScale(0.3f);
	setOpacity(80.0f);
	setOpacityModifyRGB(true);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setIgnoreAnchorPointForPosition(false);

	scheduleUpdate();

	m_lifeTime = 2.0f;

	return true;
}

void Bubble::update(float dt)
{
	m_lifeTime -= dt;

	if (m_lifeTime < 0.0f)
		if(getParent())
			getParent()->removeChild(this);
}
