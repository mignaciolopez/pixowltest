#include "BadFish.h"

#include <cstdlib>
#include <ctime>

USING_NS_CC;

BadFish * BadFish::createBadFish()
{
	return BadFish::create();
}

bool BadFish::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Sprite::initWithSpriteFrameName(TP::TP_graphics::badFish))
	{
		cocos2d::log("[BadFish]::init() | Problem loading %s", TP::TP_graphics::badFish.c_str());
		return false;
	}

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	auto conf = Configuration::getInstance();

	m_badFishMinVel = conf->getValue("badFishMinVel", (Value)4).asUnsignedInt();
	m_badFishMaxVel = conf->getValue("badFishMaxVel", (Value)8).asUnsignedInt();
	m_badFishScale = conf->getValue("badFishScale", (Value)0.2f).asFloat();


	setScale(m_badFishScale);
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setRandomPosition();

	runAxnToCenter();

	return true;
}

void BadFish::setRandomPosition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto random = std::rand() % 4;

	Vec2 pos = Vec2::ZERO;

	switch (random)
	{
	case 0:
		pos.x = origin.x - getContentSize().width * getScale();
		pos.y = std::rand() % (int)(visibleSize.height + getContentSize().height * getScale()) + origin.y - (getContentSize().height * getScale());
		break;
	case 1:
		pos.x = visibleSize.width + getContentSize().width * getScale();
		pos.y = std::rand() % (int)(visibleSize.height + getContentSize().height * getScale()) + origin.y - (getContentSize().height * getScale());
		break;
	case 2:
		pos.x = std::rand() % (int)(visibleSize.width + getContentSize().width * getScale()) + origin.x - (getContentSize().width * getScale());
		pos.y = origin.y - getContentSize().height * getScale();
		break;
	case 3:
		pos.x = std::rand() % (int)(visibleSize.width + getContentSize().width * getScale()) + origin.x - (getContentSize().width * getScale());
		pos.y = visibleSize.height + getContentSize().height * getScale();
		break;
	}

	setPosition(pos);

	//cocos2d::log("");
	//cocos2d::log("[BadFish]::setRandomPosition() | case: %d", random);
	//cocos2d::log("[BadFish]::setRandomPosition() | position X: %f", pos.x);
	//cocos2d::log("[BadFish]::setRandomPosition() | position Y: %f", pos.y);
}

void BadFish::runAxnToCenter()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto duration = std::rand() % m_badFishMaxVel + m_badFishMinVel;
	//cocos2d::log("[BadFish]::runAxnToCenter() | duration: %d", duration);
	auto axn = MoveTo::create(duration, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	runAction(axn);
}
