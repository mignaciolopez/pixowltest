#ifndef BUBLLE_H
#define BUBLLE_H

#include "cocos2d.h"
#include "graphics/TP_graphics.hpp"

class Bubble : public cocos2d::Sprite
{
public:
	static Bubble* createBubble();

	virtual bool init() override;

	CREATE_FUNC(Bubble);

	void update(float dt);

private:
	float m_bubbleScale,
		m_bubbleLifeTime;

	int m_bubbleOpacity;

};

#endif // !BUBLLE_H