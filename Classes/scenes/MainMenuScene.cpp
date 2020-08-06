#include "scenes/MainMenuScene.h"

#include "scenes/GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
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

	auto sprBackground = Sprite::create("menuBackground.png");
	if (!sprBackground)
		cocos2d::log("[MainMenuScene]::init() | Problem loading menuBackground.png");
	else
	{
		sprBackground->setContentSize(visibleSize);
		sprBackground->setAnchorPoint(Vec2(0.0f, 0.0f));
		sprBackground->setPosition(origin);
		addChild(sprBackground, 0);
	}

	m_btnPlay = ui::Button::create("buttonRed.png", "buttonRedPressed.png", "buttonRed.png");
	if (!m_btnPlay)
		cocos2d::log("[MainMenuScene]::init() | Problem creating ui::Button 'Play'");
	else
	{
		m_btnPlay->setScale9Enabled(true);
		m_btnPlay->setContentSize(Size(m_btnPlay->getContentSize().width * 5.0f, m_btnPlay->getContentSize().height * 2.5f));
		m_btnPlay->setTitleFontSize(48.0f);
		m_btnPlay->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_btnPlay->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y));
		m_btnPlay->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::btnTouchEvent, this));
		m_btnPlay->setZoomScale(0.4f);
		m_btnPlay->setPressedActionEnabled(true);
		m_btnPlay->setTitleText("Play");
		m_btnPlay->setName("btnPlay");
		addChild(m_btnPlay, 1);
	}

	m_btnQuit = ui::Button::create("buttonRed.png", "buttonRedPressed.png", "buttonRed.png");
	if (!m_btnQuit)
		cocos2d::log("[MainMenuScene]::init() | Problem creating ui::Button 'Quit'");
	else
	{
		m_btnQuit->setScale9Enabled(true);
		m_btnQuit->setContentSize(Size(m_btnQuit->getContentSize().width * 5.0f, m_btnQuit->getContentSize().height * 2.5f));
		m_btnQuit->setTitleFontSize(48.0f);
		m_btnQuit->setAnchorPoint(Vec2(0.5f, 0.5f));
		m_btnQuit->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y - m_btnQuit->getContentSize().height * 2.0f));
		m_btnQuit->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::btnTouchEvent, this));
		m_btnQuit->setZoomScale(0.4f);
		m_btnQuit->setPressedActionEnabled(true);
		m_btnQuit->setTitleText("Quit");
		m_btnQuit->setName("btnQuit");
		addChild(m_btnQuit, 1);
	}

    return true;
}

void MainMenuScene::btnTouchEvent(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type) const
{
	auto btn = dynamic_cast<ui::Button*>(pSender);
	if (!btn || btn->getContentSize().width == 0)
		return;

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::MOVED:	
		break;
	case ui::Widget::TouchEventType::ENDED:
		if (btn->getName() == "btnPlay")
		{
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		else if (btn->getName() == "btnQuit")
			Director::getInstance()->end();
		break;
	case ui::Widget::TouchEventType::CANCELED: 
		break;
	default: return;
	}
}
