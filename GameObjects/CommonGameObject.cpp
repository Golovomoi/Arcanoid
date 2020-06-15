#include "CommonGameObject.h"
USING_NS_CC;
//TODO: сделать чтобы размер нод не зависил от спрайта!
CommonGameObject* CommonGameObject::create(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    CommonGameObject* ret = new (std::nothrow) CommonGameObject();
    if (ret && ret->init(pos, sprite, physicsBody))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool CommonGameObject::init(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    if (!Node::init())
    {
        return false;
    }

    objectPhysicsBody = physicsBody;
    objectSprite = sprite;
    addComponent(physicsBody);
    setContentSize(sprite->getContentSize());
    setPosition(pos.x, pos.y + getContentSize().height / 2 * sprite->getScale());
    addChild(sprite);
    return true;
}

void CommonGameObject::update(float delta)
{
}
