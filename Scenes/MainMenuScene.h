#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartGameCallback(cocos2d::Ref* pSender);
    void highScoreCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__

