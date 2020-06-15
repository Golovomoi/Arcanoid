#include "HighScoreScene.h"
#include "MainMenuScene.h"

USING_NS_CC;
cocos2d::Scene* HighScoreScene::createScene()
{
    return HighScoreScene::create();
}

bool HighScoreScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF("Highscore: ", "fonts/Marker Felt.ttf", 24);
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        addChild(label, 1);
    auto backItem = MenuItemImage::create(
        "back.png",
        "back.png",
        CC_CALLBACK_1(HighScoreScene::mainMenuCallback, this));
    backItem->setScale(0.025);
    auto menu = Menu::create();
    menu->setPosition(Vec2(visibleSize.width/2, backItem->getContentSize().height * 0.025));
    menu->addChild(backItem);
    addChild(menu, 1);
    auto fileUtill = FileUtils::getInstance();
    std::string path = fileUtill->getWritablePath() + "highscore.txt";
    fileUtill->writeStringToFile("somestring", path);
    auto uDef = UserDefault::getInstance();
    for (int i = 1; i <= 10; i++)
    {
        auto pos = "0" + std::to_string(i);
        auto scorVal = uDef->getIntegerForKey(pos.c_str());
        std::string resultScoreField = std::to_string(i) + ". " + std::to_string(scorVal);
        auto label = Label::createWithTTF(resultScoreField, "fonts/Marker Felt.ttf", 24);
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - (label->getContentSize().height + 5) * (i+1)));
        addChild(label, 1);
    }
    return true;
}

void HighScoreScene::mainMenuCallback(cocos2d::Ref* pSender)
{
    auto mainMenuScene = MainMenu::createScene();
    Director::getInstance()->replaceScene(mainMenuScene);
}
