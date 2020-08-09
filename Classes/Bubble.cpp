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

	auto conf = Configuration::getInstance();

	m_bubbleScale = conf->getValue("bubbleScale", (Value)0.3f).asFloat();
	m_bubbleLifeTime = conf->getValue("bubbleLifeTime", (Value)2.0f).asFloat();
	m_bubbleOpacity = conf->getValue("bubbleOpacity", (Value)80).asInt();

	setScale(m_bubbleScale);
	setOpacity(m_bubbleOpacity);
	setOpacityModifyRGB(true);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setIgnoreAnchorPointForPosition(false);

	scheduleUpdate();


	return true;
}

void Bubble::update(float dt)
{
	m_bubbleLifeTime -= dt;

	if (m_bubbleLifeTime < 0.0f)
		if(getParent())
			getParent()->removeChild(this);
}
