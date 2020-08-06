#include "BadFish.h"

#include <cstdlib>
#include <ctime>

USING_NS_CC;

BadFish::BadFish(cocos2d::Node* parent)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 position = Vec2::ZERO;

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	m_sprite = Sprite::create("badFish.png");
	if (!m_sprite)
		cocos2d::log("[BadFish]::BadFish() | Problem loading badFish.png");
	else
	{
		auto scale = 0.2f;
		m_sprite->setScale(scale);
		m_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

		auto leftOrRight = std::rand() % 2;

		switch (leftOrRight)
		{
		case 0:
			position.x = (origin.x - m_sprite->getContentSize().width * scale) + std::rand() / ((RAND_MAX + 1u) / (origin.x + m_sprite->getContentSize().width * scale / 2.0f));
			break;
		case 1:
			position.x = visibleSize.width + std::rand() / ((RAND_MAX + 1u) / (visibleSize.width + m_sprite->getContentSize().width * scale));
			break;
		default:
			m_sprite = nullptr;
			return;
		}

		position.x = (origin.x - m_sprite->getContentSize().width * scale) - std::rand() % (int)(visibleSize.width + m_sprite->getContentSize().width * scale);
		position.y = (origin.y - m_sprite->getContentSize().height * scale) + std::rand() / ((RAND_MAX + 1u) / (visibleSize.height + m_sprite->getContentSize().height * scale));

		cocos2d::log("[BadFish]::BadFish() | position X: %f", position.x);
		cocos2d::log("[BadFish]::BadFish() | position Y: %f", position.y);

		m_sprite->setPosition(position);

		m_sprite->setOnExitCallback(CC_CALLBACK_0(BadFish::onExitCallBack, this));

		parent->addChild(m_sprite, 1);

		auto duration = 2 + std::rand() / ((RAND_MAX + 1u) / 8);
		cocos2d::log("[BadFish]::BadFish() | duration: %d", duration);
		cocos2d::log("");
		auto axn = MoveTo::create(duration, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		m_sprite->runAction(axn);
	}
}

BadFish::~BadFish()
{
	if (m_sprite)
	{
		if (m_sprite->getParent())
			m_sprite->getParent()->removeChild(m_sprite);
	}
}

void BadFish::onExitCallBack()
{
	m_sprite = nullptr;
}
