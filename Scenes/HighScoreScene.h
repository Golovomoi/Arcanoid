#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__
#include "cocos2d.h"
class HighScoreScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void mainMenuCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HighScoreScene);
};

#endif // __HIGHSCORE_SCENE_H__

