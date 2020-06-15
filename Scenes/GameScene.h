#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create(cocos2d::Scene*);
    static cocos2d::Scene* createScene(cocos2d::Scene*);
    virtual bool init(cocos2d::Scene*);
    bool onContactBegin(cocos2d::PhysicsContact&);
    virtual void update(float delta) override;

private:
    cocos2d::Label* scoreLable;
    void handleHit(cocos2d::Node*);
    // не использовать, пока не работает.
    cocos2d::Scene* mainMenuScene;
};

#endif // __GAME_SCENE_H__
