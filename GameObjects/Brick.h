#ifndef __BRICK_H__
#define __BRICK_H__
#include "cocos2d.h"
#include "CommonGameObject.h"
class Brick : public CommonGameObject
{
public:
    static Brick* create(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    virtual bool init(cocos2d::Vec2, cocos2d::Sprite*, cocos2d::PhysicsBody*);
    int getBaseScoreValue();
    void setBaseScoreValue(int);
    int getMaxHealth();
    void setMaxHealth(int);
    void setHealth(int);
    int getCurrentHealth();
    void setCurrentHealth(int);
    int getScoreValue();
    // parametr is multiplier for baseScore
    void setScoreValue(int);
    int getHit();

private:
    void setDefaultValues();
    int baseScoreValue;
    int maxHealth;
    int currentHealth;
    int scoreValue;
};
#endif // __BRICK_H__
