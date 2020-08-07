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

	// add a label shows "Hello World"
	// create and initialize a label

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
		m_btnQuit->setPosition(Vec2(visibleSize.width + origin.x - m_btnQuit->getContentSize().width / 2.0f, origin.y + m_btnQuit->getContentSize().height / 2.0f));
		m_btnQuit->addTouchEventListener(CC_CALLBACK_2(GameScene::btnTouchEvent, this));
		m_btnQuit->setZoomScale(0.4f);
		m_btnQuit->setPressedActionEnabled(true);
		m_btnQuit->setTitleText("Menu");
		m_btnQuit->setName("btnQuit");
		m_btnQuit->setOpacity(100.0f);
		m_btnQuit->setOpacityModifyRGB(true);
		addChild(m_btnQuit, 1);
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
	
}

void GameScene::update(float dt)
{
	if (m_gameOver)
		return;

	m_timeBubbles += dt;
	m_timeBadFish += dt;

	if (m_timeBadFish > 1.0f)
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

	checkCollissions();
}

void GameScene::badFishOnExit(cocos2d::Ref* pSender)
{
	auto bf = dynamic_cast<BadFish*>(pSender);

	if (!bf)
		return;

	if (m_badFishes.find(bf->getTag()) != m_badFishes.end())
		m_badFishes.erase(bf->getTag());
}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	if (m_gameOver)
		return;

	m_fish->rotate(touch->getLocation());
	if (m_timeBubbles > 0.2f)
	{
		m_timeBubbles = 0.0f;
		spawnBubble();
	}
}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	if (m_gameOver)
		return;

	m_fish->rotate(touch->getLocation());
	spawnBubble();
}

void GameScene::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
}

void GameScene::spawnBubble()
{
	auto bubble = Bubble::createBubble();
	if (!bubble)
		return;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_bubbles.emplace(m_bubblesCount, bubble);
	addChild(bubble, 3);
	bubble->setTag(m_bubblesCount++);

	Vec2 unitVector = Vec2::ZERO;
	auto fishSize = m_fish->getContentSize() * m_fish->getScale() / 2.0f;
	Vec2 mouthPos = m_fish->getPosition();

	unitVector.x = cos(CC_DEGREES_TO_RADIANS(m_fish->getRotation()));
	unitVector.y = sin(CC_DEGREES_TO_RADIANS(m_fish->getRotation()));
	mouthPos.x += unitVector.x * fishSize.width;
	mouthPos.y += unitVector.y * - fishSize.height;
	bubble->setPosition(mouthPos);

	unitVector.x *=   visibleSize.width  / 2.5f;
	unitVector.y *= - visibleSize.height / 2.5f;
	auto axn = MoveBy::create(3.0f, unitVector);
	bubble->runAction(axn);

	bubble->setOnExitCallback([this, bubble]()
	{
		m_bubbles.erase(bubble->getTag());
	});

	m_fish->runAction(TP::TP_graphics::createFISHAnimateAction(0.2f));
}

void GameScene::checkCollissions()
{
	for (auto& bf : m_badFishes)
	{
		if (bf.second->didReachCenter())
		{
			GameOver();
			return;
		}
		for (auto& bubble : m_bubbles)
		{
			if (bf.second->getBoundingBox().containsPoint(bubble.second->getPosition()))
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
	Director::getInstance()->setAnimationInterval(1.0f / 30);
}
