#ifndef GANE_SCENE
#define GANE_SCENE

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void btnTouchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	virtual void update(float dt) override;

private:
	cocos2d::ui::Button* m_btnQuit = nullptr;
};

#endif // !GANE_SCENE
