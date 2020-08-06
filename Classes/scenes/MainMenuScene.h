#ifndef MAIN_MENU_SCENE
#define MAIN_MENU_SCENE

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

	void btnTouchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type) const;

private:
	cocos2d::ui::Button* m_btnPlay = nullptr;

	cocos2d::ui::Button* m_btnQuit = nullptr;

};

#endif // !MAIN_MENU_SCENE
