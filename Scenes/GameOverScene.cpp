#include "GameOverScene.h"
//TODO: подумать... gameover знает о mainmenu, mainmenu знает о gameScene, gamescene знает о gameover = циклическая зависимость... прогнать параметром сцену?
#include "MainMenuScene.h"
USING_NS_CC;

cocos2d::Scene* GameOverScene::create(cocos2d::Scene* scene)
{
    GameOverScene* ret = new (std::nothrow) GameOverScene();
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


bool GameOverScene::init(cocos2d::Scene* scene)
{
    if (!cocos2d::Scene::init())
    {
        return false;
    }
    mainMenuScene = scene;
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto gameOverLabel = cocos2d::Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
        gameOverLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - gameOverLabel->getContentSize().height));

        this->addChild(gameOverLabel, 1);

        auto startItem = MenuItemImage::create(
            "mainMenu.png",
            "mainMenu.png",
            CC_CALLBACK_1(GameOverScene::mainMenuCallback, this));

        auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(GameOverScene::CloseCallback, this));

        startItem->setScale(0.5);
        auto menu = Menu::create();
        menu->addChild(startItem);
        menu->addChild(closeItem);
        menu->alignItemsVerticallyWithPadding(10.0);
        menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        this->addChild(menu, 1);
    return true;
}

void GameOverScene::CloseCallback(cocos2d::Ref* pSender)
{
    cocos2d::Director::getInstance()->end();
}

void GameOverScene::mainMenuCallback(cocos2d::Ref* pSender)
{
    auto mainMenu = MainMenu::createScene();
    cocos2d::Director::getInstance()->replaceScene(mainMenu);
}