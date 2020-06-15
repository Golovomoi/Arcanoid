#include "Brick.h"
//TODO: добавить кирпичикам возможность менять текстуру.
Brick* Brick::create(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    Brick* ret = new (std::nothrow) Brick();
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

bool Brick::init(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    if (!CommonGameObject::init(pos, sprite, physicsBody))
        return false;
    physicsBody->setVelocityLimit(0);
    physicsBody->setDynamic(false);
    setDefaultValues();
    return true;
}

void Brick::setDefaultValues()
{
    baseScoreValue = 100;
    maxHealth = 2;
    currentHealth = maxHealth;
    scoreValue = baseScoreValue;
}

int Brick::getBaseScoreValue()
{
    return baseScoreValue;
}

void Brick::setBaseScoreValue(int x)
{
    baseScoreValue = x;
}

int Brick::getMaxHealth()
{
    return maxHealth;
}

void Brick::setMaxHealth(int x)
{
    maxHealth = x;
}

void Brick::setHealth(int x)
{
    setMaxHealth(x);
    setCurrentHealth(x);
}

int Brick::getCurrentHealth()
{
    return 0;
}

void Brick::setCurrentHealth(int x)
{
    currentHealth = x;
}

int Brick::getScoreValue()
{
    return scoreValue;
}

void Brick::setScoreValue(int x)
{
    scoreValue = x * baseScoreValue;
}

int Brick::getHit()
{
    currentHealth--;
    return currentHealth > 0 ? 0 : scoreValue;
}

