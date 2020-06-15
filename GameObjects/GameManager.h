#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager
{
public:
    static GameManager* getInstance();
    void SetCurrentLvl(int);
    int GetCurrentLvl();
    void SetCurrentScore(int);
    int GetCurrentScore();
    void IncreseCurrentScore(int);
    int GetBricksCount();
    void SetBricksCount(int);
    int RemoveBricks(int);
    void StartGame();
    void StartNextLvl();
    bool CheckGameOver();
    void SetGameOver();
    void SaveScore();
private:
    int bricksLeft;
    int currentLvl;
    int currentScore;
    void SetDefaultValues();
    bool isGameOver;
    GameManager();
    ~GameManager();
    GameManager(GameManager const*) = delete;
    GameManager operator= (GameManager* const*) = delete;

};
#endif // __GAME_MANAGER_H__
