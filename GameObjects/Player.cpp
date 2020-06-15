#include "Player.h"
USING_NS_CC;

Player* Player::create(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    Player* ret = new (std::nothrow) Player();
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
bool Player::init(cocos2d::Vec2 pos, cocos2d::Sprite* sprite, cocos2d::PhysicsBody* physicsBody)
{
    
    if (!CommonGameObject::init(pos, sprite, physicsBody))
        return false;
    physicsBody->setAngularVelocityLimit(0);

    auto eventListener = EventListenerKeyboard::create();
    log("testing log");
    eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            log("log key_arrow");
            isRightArrowPressed = true;
            moveRight();
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            log("log key_arrow");
            isLeftArrowPressed = true;
            moveLeft();
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            if (!isBallInGame)
            {
                log("starting");
                auto ballSprite = Sprite::createWithSpriteFrameName("58-Breakout-Tiles.png");
                ballSprite->setScale(0.25);
                auto ballphysicsBody = PhysicsBody::createCircle(ballSprite->getContentSize().width * ballSprite->getScale() / 2, PhysicsMaterial(0.1, 1, 1));
                auto gameBall = GameBall::create(getPosition(), ballSprite, ballphysicsBody);
                getParent()->addChild(gameBall);
                gameBall->launch();
                isBallInGame = true;
            }
        }
    }; 
    eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            objectPhysicsBody->setVelocityLimit(0);
            isRightArrowPressed = false;
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            objectPhysicsBody->setVelocityLimit(0);
            isLeftArrowPressed = false;
            break;   
        }

    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();
    return true;
}
void Player::moveRight()
{
    objectPhysicsBody->setVelocityLimit(FLT_MAX);
    objectPhysicsBody->setVelocity(Vec2(1000,0));
}
void Player::moveLeft()
{
    objectPhysicsBody->setVelocityLimit(FLT_MAX);
    objectPhysicsBody->setVelocity(Vec2(-1000, 0));
}
void Player::update(float delta)
{
    float x = std::min(getPosition().x, Director::getInstance()->getVisibleSize().width - getContentSize().width * objectSprite->getScale() / 2);
    x = std::max(x, getContentSize().width / 2 * objectSprite->getScale());
    setPosition(x, getContentSize().height/2 * objectSprite->getScale());
    Node::update(delta);
    if (isRightArrowPressed)
        moveRight();
    if (isLeftArrowPressed)
        moveLeft();
}
Player::~Player()
{
}
