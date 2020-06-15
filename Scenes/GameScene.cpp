#include "GameScene.h"
#include "GameOverScene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Brick.h"
#include "GameObjects//GameManager.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;

cocos2d::Scene* Game::create(cocos2d::Scene* scene)
{
    Game* ret = new (std::nothrow) Game();
    if (ret && ret->init(scene))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

Scene* Game::createScene(cocos2d::Scene* scene)
{
    auto newScene = Game::createWithPhysics();
    // set gravity
    newScene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    //newScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Game::create(scene);
    newScene->addChild(layer);
    return newScene;
}


bool Game::init(cocos2d::Scene* scene)
{
    if (!Scene::init())
    {
        return false;
    }
    mainMenuScene = scene;
    auto gameManager = GameManager::getInstance();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Vec2* edges = new Vec2[4];
    edges[0] = Vec2(0, 0);
    edges[1] = Vec2(0, visibleSize.height);
    edges[2] = Vec2(visibleSize.width, visibleSize.height);
    edges[3] = Vec2(visibleSize.width, 0);
    auto edgeBody = PhysicsBody::createEdgeChain(edges, 4, PhysicsMaterial(0, 1, 0), 10);
    auto edgeNode = Node::create();
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);
    
    auto playerSprite = Sprite::createWithSpriteFrameName("50-Breakout-Tiles.png");
    playerSprite->setScale(0.5);
    auto playerBody = PhysicsBody::createBox(playerSprite->getContentSize() * playerSprite->getScale(), PhysicsMaterial(1, 1, 1));
    auto playerObj = Player::create(Vec2(visibleSize.width / 2 + origin.x, origin.y), playerSprite, playerBody);
    addChild(playerObj);

    int currentScore = gameManager->GetCurrentLvl();
    scoreLable = Label::createWithTTF("score: " + std::to_string(currentScore), "fonts/Marker Felt.ttf", 24);
    scoreLable->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - scoreLable->getContentSize().height));
    addChild(scoreLable, 1);

    auto hintLabel = Label::createWithTTF("Press space to launch ball!!! ", "fonts/Marker Felt.ttf", 24);
    hintLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + hintLabel->getContentSize().height * 5));
    addChild(hintLabel, 1);

    int rowCount = 6;
    int columnCount = 6;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++) 
        {
            std::string spriteName = "01-Breakout-Tiles.png";
            auto brickSprite = Sprite::createWithSpriteFrameName(spriteName);
            float scale = 0.5f;
            brickSprite->setScale(scale);
            auto brickGameWidth = brickSprite->getContentSize().width * scale;
            auto brickGameHeight = brickSprite->getContentSize().height * scale;
            auto brickBody = PhysicsBody::createBox(brickSprite->getContentSize() * scale, PhysicsMaterial(0, 1.05, 0));
            brickBody->setCollisionBitmask(0xFFFFFFFF);
            brickBody->setContactTestBitmask(0xFFFFFFFF);
            auto brickObject = Brick::create(Vec2(visibleSize.width / 2 - brickGameWidth * rowCount / 2 + i * brickGameWidth + brickGameWidth / 2,
                visibleSize.height - (j + 4) * brickGameHeight - brickGameHeight / 2), brickSprite, brickBody);
            brickObject->setHealth(gameManager->GetCurrentLvl());
            brickObject->setScoreValue(gameManager->GetCurrentLvl());
            brickObject->setTag(10);
            addChild(brickObject);
        }
    }
    gameManager->SetBricksCount(rowCount*columnCount);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    scheduleUpdate();
    return true;
}

bool Game::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == 10 && nodeB->getTag() != 10)
        {
            handleHit(nodeA);
        }
        if (nodeB->getTag() == 10 && nodeA->getTag() != 10)
        {
            handleHit(nodeB);
        }
        
    }

    return true;
}

void Game::update(float delta)
{
    if (GameManager::getInstance()->CheckGameOver())
    {
        auto gameOverScene = GameOverScene::create(mainMenuScene);
        GameManager::getInstance()->SaveScore();
        //GameManager::getInstance()->StartGame();
        Director::getInstance()->replaceScene(gameOverScene);
    }
}

void Game::handleHit(cocos2d::Node* node)
{
    auto gameManager = GameManager::getInstance();
    auto brick = dynamic_cast<Brick*>(node);
    auto hitScoreValue = brick->getHit();
    if (hitScoreValue > 0)
    {
        gameManager->RemoveBricks(1);
        gameManager->IncreseCurrentScore(hitScoreValue);
        scoreLable->setString("score: " + std::to_string(gameManager->GetCurrentScore()));
        node->removeFromParentAndCleanup(true);
        if (gameManager->GetBricksCount() == 0)
            gameManager->StartNextLvl();
    }
    
}


