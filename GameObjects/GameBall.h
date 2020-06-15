#ifndef __GAMEBALL_H__
#define __GAMEBALL_H__

#include "cocos2d.h"
#include "CommonGameObject.h"
class GameBall : public CommonGameObject
{
public:
    static GameBall* create(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody);
    virtual bool init(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody);
    virtual void update(float delta) override;
    void launch();
};
#endif // __GAMEBALL_H__
