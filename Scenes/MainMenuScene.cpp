#include "MainMenuScene.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "GameObjects/GameManager.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}


bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto startLabel = Label::createWithTTF("start", "fonts/Marker Felt.ttf", 24);

    auto someMenuItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    auto startItem = MenuItemImage::create(
        "StartButton.png",
        "StartButton.png",
        CC_CALLBACK_1(MainMenu::menuStartGameCallback, this));

    auto highScoreItem = MenuItemImage::create(
        "highscore.png",
        "highscore.png",
        CC_CALLBACK_1(MainMenu::highScoreCallback, this));

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    startItem->setScale(0.5);
    auto menu = Menu::create();
    menu->addChild(startItem);
    menu->addChild(highScoreItem);
    menu->addChild(closeItem);
    menu->alignItemsVerticallyWithPadding(10.0);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(menu, 1);


    auto label = Label::createWithTTF("Arcanoid", "fonts/Marker Felt.ttf", 24);

        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        addChild(label, 1);
    return true;
}

void MainMenu::menuStartGameCallback(Ref* pSender)
{
    auto gameManager = GameManager::getInstance();
    gameManager->StartGame();
    auto newMenu = MainMenu::createScene();
    auto gameScene = Game::createScene(newMenu);
    Director::getInstance()->replaceScene(gameScene);
}

void MainMenu::highScoreCallback(cocos2d::Ref* pSender)
{
    auto fileUtill = FileUtils::getInstance();
    std::string path = fileUtill->getWritablePath() + "highscore.txt";
    fileUtill->writeStringToFile("somestring", path);
    auto uDef = UserDefault::getInstance();
    uDef->setIntegerForKey("1", 0);
    auto highScoreScene = HighScoreScene::createScene();
    Director::getInstance()->replaceScene(highScoreScene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}