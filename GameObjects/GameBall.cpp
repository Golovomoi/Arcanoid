#include "GameBall.h"
#include "GameObjects/GameManager.h"
USING_NS_CC;

GameBall* GameBall::create(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    GameBall* ret = new (std::nothrow) GameBall();
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

bool GameBall::init(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    if (!CommonGameObject::init(pos, sprite, physicsBody))
        return false;
    physicsBody->setCollisionBitmask(0xFFFFFFFF);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    return true;
}

void GameBall::update(float delta)
{
    float x = std::min(getPosition().x, Director::getInstance()->getVisibleSize().width - getContentSize().width * objectSprite->getScale() / 2);
    x = std::max(x, getContentSize().width / 2 * objectSprite->getScale());
    setPosition(x, std::min(getPosition().y, Director::getInstance()->getVisibleSize().height - getContentSize().height / 2 * objectSprite->getScale()));
    if (getPosition().y < 0)
        GameManager::getInstance()->SetGameOver();
}

void GameBall::launch()
{
    objectPhysicsBody->applyImpulse(Vec2(1000,25000));
}
