#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create(cocos2d::Scene*);

    virtual bool init(cocos2d::Scene*);
    void CloseCallback(cocos2d::Ref* pSender);
    void mainMenuCallback(cocos2d::Ref* pSender);
private:
    // не использовать, пока не работает.
    cocos2d::Scene* mainMenuScene;
};
#endif // __GAMEOVER_SCENE_H__
