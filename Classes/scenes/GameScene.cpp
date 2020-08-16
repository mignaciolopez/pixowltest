#include "scenes/GameScene.h"
#include "scenes/MainMenuScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	/////////////////////////////
	// 3. add your codes below...

	auto conf = Configuration::getInstance();

	m_gameFPS = conf->getValue("gameFPS", (Value)60).asInt();
	m_gameOverFPS = conf->getValue("gameOverFPS", (Value)30).asInt();
	m_fishAnimationTime = conf->getValue("fishAnimationTime", (Value)0.2f).asFloat();
	m_badFishSpawnInterval = conf->getValue("badFishSpawnInterval", (Value)1.0f).asFloat();
	m_bubbleUnitVector = conf->getValue("bubbleUnitVector", (Value)2.5f).asFloat();
	m_bubblesSpawnInterval = conf->getValue("bubblesSpawnInterval", (Value)0.2f).asFloat();
	m_bubbleAxnTime = conf->getValue("bubbleAxnTime", (Value)2.0f).asFloat();

	auto sprBackground = Sprite::createWithSpriteFrameName(TP::TP_graphics::background);
	if (!sprBackground)
		cocos2d::log("[MainMenuScene]::init() | Problem loading %s", TP::TP_graphics::background.c_str());
	else
	{
		sprBackground->setContentSize(visibleSize);
		sprBackground->setAnchorPoint(Vec2(0.0f, 0.0f));
		sprBackground->setPosition(origin);
		addChild(sprBackground, 0);
	}

	m_btnQuit = ui::Button::create("buttonRed.png", "buttonRedPressed.png", "buttonRed.png");
	if (!m_btnQuit)
		cocos2d::log("[GameScene]::init() | Problem creating ui::Button 'Quit'");
	else
	{
		m_btnQuit->setScale9Enabled(true);
		m_btnQuit->setContentSize(Size(m_btnQuit->getContentSize().width * 5.0f, m_btnQuit->getContentSize().height * 2.5f));
		m_btnQuit->setTitleFontSize(48.0f);
		m_btnQuit->setAnchorPoint(Vec2(0.5f, 0.5f));
		//m_btnQuit->setPosition(Vec2(visibleSize.width + origin.x - m_btnQuit->getContentSize().width / 2.0f, origin.y + m_btnQuit->getContentSize().height / 2.0f));
		m_btnQuit->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y - 150.0f));
		m_btnQuit->addTouchEventListener(CC_CALLBACK_2(GameScene::btnTouchEvent, this));
		m_btnQuit->setZoomScale(0.4f);
		m_btnQuit->setPressedActionEnabled(true);
		m_btnQuit->setTitleText("Back");
		m_btnQuit->setName("btnQuit");
		//m_btnQuit->setOpacity(100.0f);
		m_btnQuit->setOpacityModifyRGB(true);
		addChild(m_btnQuit, 1);

		m_btnQuit->setVisible(false);
	}

	m_fish = Fish::createFish();
	if (m_fish)
		addChild(m_fish, 1);


	setOnExitCallback(CC_CALLBACK_0(GameScene::mainSceneOnExit, this));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	scheduleUpdate();

	m_timeBadFish = 0.0f;
	m_timeBubbles = 0.0f;
	m_badsCount = 0;
	m_bubblesCount = 0;
	m_gameOver = false;

	Director::getInstance()->setAnimationInterval(1.0f / m_gameFPS);

	return true;
}

void GameScene::btnTouchEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type) const
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default: return;
	}
}

void GameScene::mainSceneOnExit()
{
	m_bubbles.clear();
	m_bubblesCount = 0;

	m_badFishes.clear();
	m_badsCount = 0;
}

void GameScene::update(float dt)
{
	if (m_gameOver)
		return;

	m_timeBubbles += dt;
	m_timeBadFish += dt;

	spawnBadFish();
	checkCollissions();
}

void GameScene::badFishOnExit(cocos2d::Ref* pSender)
{
	auto bf = dynamic_cast<BadFish*>(pSender);
	auto bftouched = dynamic_cast<BadFish*>(getUserObject());

	if (!bf)
		return;

	if (m_badFishes.find(bf->getTag()) != m_badFishes.end())
		m_badFishes.erase(bf->getTag());

	if (bftouched)
		if (bf->getTag() == bftouched->getTag())
			setUserObject(nullptr);
}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	if (m_gameOver)
		return false;

	m_fish->rotate(touch->getLocation());

	for (auto& bf : m_badFishes)
	{
		if (bf.second->getBoundingBox().containsPoint(touch->getLocation()))
		{
			setUserObject(bf.second);
			return true;
		}
	}

	return true; //return true here to rotate the fish anyway.
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	m_fish->rotate(touch->getLocation());

	if (m_timeBubbles > m_bubblesSpawnInterval)
	{
		auto bftouched = dynamic_cast<BadFish*>(getUserObject());

		if (bftouched && bftouched->getBoundingBox().containsPoint(touch->getLocation()))
			spawnBubble();	
			//i wasnt sure about this, but it prevents spawn bubbles with just one touch and then 
			//moving around and keep spawning bubbles. I think is better this way.
	}

}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	onTouchMoved(touch, evnt);
	setUserObject(nullptr);
}

void GameScene::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
}

void GameScene::spawnBubble()
{
	auto bubble = Bubble::createBubble();
	if (!bubble)
		return;

	m_timeBubbles = 0.0f;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_bubbles.emplace(m_bubblesCount, bubble);
	addChild(bubble, 3);
	bubble->setTag(m_bubblesCount++);
	
	//all this math is to obtain the position of the mouth relative to the current fish rotation
	Vec2 unitVector = Vec2::ZERO;
	auto fishSize = m_fish->getContentSize() * m_fish->getScale() / 2.0f;
	Vec2 mouthPos = m_fish->getPosition();

	unitVector.x = cos(CC_DEGREES_TO_RADIANS(m_fish->getRotation()));
	unitVector.y = sin(CC_DEGREES_TO_RADIANS(m_fish->getRotation()));
	mouthPos.x += unitVector.x * fishSize.width;
	mouthPos.y += unitVector.y * - fishSize.height;
	bubble->setPosition(mouthPos);

	///////////////////////////////
	/*
	unitVector.x *=   visibleSize.width  / m_bubbleUnitVector;	//This can make the bubble go to the edge of
	unitVector.y *= - visibleSize.height / m_bubbleUnitVector;	//badfish and not collide.
	auto axn = MoveBy::create(m_bubbleAxnTime, unitVector); 
	*/
	auto bftouched = dynamic_cast<BadFish*>(getUserObject());	//this one fixes it, but it always goes to
	auto axn = MoveTo::create(m_bubbleAxnTime, bftouched->getPosition());	//the anchorpoint of bad fish. (center)
	///////////////////////////////

	bubble->runAction(axn);

	bubble->setOnExitCallback([this, bubble]()
	{
		m_bubbles.erase(bubble->getTag());
	});

	m_fish->runAction(TP::TP_graphics::createFISHAnimateAction(m_fishAnimationTime));
}

void GameScene::spawnBadFish()
{
	if (m_timeBadFish > m_badFishSpawnInterval)
	{
		m_timeBadFish = 0.0f;
		auto bf = BadFish::createBadFish();
		if (bf)
		{
			addChild(bf, 2);
			bf->setOnExitCallback(CC_CALLBACK_0(GameScene::badFishOnExit, this, bf));
			m_badFishes.emplace(m_badsCount, bf);
			bf->setTag(m_badsCount++);
		}
	}
}

void GameScene::checkCollissions()
{
	for (auto& bf : m_badFishes)
	{
		if (m_fish->getBoundingBox().intersectsRect(bf.second->getBoundingBox()))
		{
			GameOver();
			return;
		}
		for (auto& bubble : m_bubbles)
		{
			if (bf.second->getBoundingBox().intersectsRect(bubble.second->getBoundingBox()))
			{
				removeChild(bubble.second);
				removeChild(bf.second);
				return;
			}
		}
	}
}

void GameScene::GameOver()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::create("Game Over", "", 72, visibleSize, TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setIgnoreAnchorPointForPosition(false);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y));
	addChild(label, 5);
	m_gameOver = true;
	Director::getInstance()->setAnimationInterval(1.0f / m_gameOverFPS);

	m_btnQuit->setVisible(true);
}
