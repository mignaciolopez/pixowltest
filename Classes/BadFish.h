#ifndef BAD_FISH_H
#define BAD_FISH_H

#include "cocos2d.h"

class BadFish
{
public:
	BadFish(cocos2d::Node* parent);
	~BadFish();

	void onExitCallBack();

private:
	cocos2d::Sprite* m_sprite;
};

#endif // !BAD_FISH_H