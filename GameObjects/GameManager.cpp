#include "GameManager.h"
#include <vector>
#include <algorithm>

USING_NS_CC;
static GameManager* instance = nullptr;

GameManager* GameManager::getInstance()
{
    if (!instance)
    {
        instance = new GameManager();
        instance->SetDefaultValues();
    }

    return instance;
}

void GameManager::SetCurrentLvl(int x)
{
    currentLvl = x;
}

int GameManager::GetCurrentLvl()
{
    return currentLvl;
}

void GameManager::SetCurrentScore(int x)
{
    currentScore = x;
}

int GameManager::GetCurrentScore()
{
    return currentScore;
}

void GameManager::IncreseCurrentScore(int x)
{
    currentScore += x;
}

int GameManager::GetBricksCount()
{
    return bricksLeft;
}

void GameManager::SetBricksCount(int x)
{
    bricksLeft = x;
}

int GameManager::RemoveBricks(int x)
{
    bricksLeft = std::max(bricksLeft - x, 0);
    return 0;
}

void GameManager::StartGame()
{
    SetDefaultValues();
}

void GameManager::StartNextLvl()
{
    currentLvl++;
}

bool GameManager::CheckGameOver()
{
    return isGameOver;
}

void GameManager::SetGameOver()
{
    isGameOver = true;
}

void GameManager::SaveScore()
{
    auto uDef = UserDefault::getInstance();
    std::vector<int> scores;
    for (int i = 1; i <= 10; i++)
    {
        auto pos = "0" + std::to_string(i);
        auto scorVal = uDef->getIntegerForKey(pos.c_str());
        scores.push_back(scorVal);
    }
    scores.push_back(currentScore);
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    scores.pop_back();
    for (int i = 0; i < 10; i++)
    {
        auto pos = "0" + std::to_string(i+1);
        uDef->setIntegerForKey(pos.c_str(), scores[i]);
    }
    uDef->flush();
}

void GameManager::SetDefaultValues()
{
    isGameOver = false;
    currentLvl = 1;
    currentScore = 0;
    bricksLeft = 0;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}
