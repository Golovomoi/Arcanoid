#ifndef __COMMONGAMEOBJECT_H__
#define __COMMONGAMEOBJECT_H__
#include "cocos2d.h"
class CommonGameObject : public cocos2d::Node
{
public:
    static CommonGameObject* create(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    virtual bool init(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    virtual void update(float delta) override;
protected:
    cocos2d::PhysicsBody* objectPhysicsBody;
    cocos2d::Sprite* objectSprite;
};
#endif // __COMMONGAMEOBJECT_H__

