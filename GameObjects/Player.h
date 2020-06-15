#ifndef __PLAYEROBJECT_H__
#define __PLAYEROBJECT_H__

#include "cocos2d.h"
#include "GameBall.h"
#include "CommonGameObject.h"
class Player : public CommonGameObject
{   
public:
    static Player* create(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    virtual bool init(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    void moveRight();
    void moveLeft();
    virtual void update(float delta) override;
private:
    bool isLeftArrowPressed, isRightArrowPressed, isBallInGame = false;
    const float speed = 35.0f;
    ~Player();
};

#endif //__PLAYEROBJECT_H__ 