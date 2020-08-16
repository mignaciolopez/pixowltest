#ifndef GANE_SCENE
#define GANE_SCENE

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "graphics/TP_graphics.hpp"

#include "BadFish.h"
#include "Fish.h"
#include "Bubble.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void btnTouchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) const;

	void mainSceneOnExit();

	virtual void update(float dt) override;

	void badFishOnExit(cocos2d::Ref* pSender);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* evnt);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* evnt);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* evnt);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* evnt);

private:
	void spawnBubble();
	void spawnBadFish();
	void checkCollissions();
	void GameOver();

	cocos2d::ui::Button* m_btnQuit = nullptr;

	std::map<unsigned short, BadFish*> m_badFishes;
	std::map<unsigned short, Bubble*> m_bubbles;

	float m_timeBadFish = 0.0f;
	float m_timeBubbles = 0.0f;

	unsigned short m_badsCount = 0;
	unsigned short m_bubblesCount = 0;

	Fish* m_fish = nullptr;

	bool m_gameOver = false;

	float m_gameFPS,
		m_gameOverFPS,
		m_fishAnimationTime,
		m_badFishSpawnInterval,
		m_bubbleAxnTime,
		m_bubbleUnitVector,
		m_bubblesSpawnInterval;
};

#endif // !GANE_SCENE
