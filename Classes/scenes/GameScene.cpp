#include "scenes/GameScene.h"

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

	auto sprBackground = Sprite::create("background.png");
	if (!sprBackground)
		cocos2d::log("[MainMenuScene]::init() | Problem loading background.png");
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
		m_btnQuit->setTitleText("Quit");
		m_btnQuit->setName("btnQuit");
		m_btnQuit->setOpacity(100.0f);
		m_btnQuit->setOpacityModifyRGB(true);
		addChild(m_btnQuit, 1);
	}


	scheduleUpdate();

	return true;
}

void GameScene::btnTouchEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:
		break;
	case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
		break;
	case ui::Widget::TouchEventType::CANCELED:
		break;
	default: return;
	}
}

void GameScene::update(float dt)
{

}
