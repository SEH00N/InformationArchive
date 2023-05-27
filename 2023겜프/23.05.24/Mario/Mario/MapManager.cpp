#include "MapManager.h"
#include "Stage.h"

MapManager::MapManager()
{
    for (int i = 0; i < 3; ++i)
        stages[i] = nullptr;
}

MapManager::~MapManager()
{
    for (int i = 0; i < 3; ++i)
        SAFE_DELETE(stages[i]);
}

bool MapManager::Init()
{
    char* stageName[3] = {(char*)"Stage1.txt", (char*)"Stage2.txt", (char*)"Stage3.txt"};

    for (int i = 0; i < 3; ++i)
    {
        stages[i] = new Stage;
        stages[i]->Init(stageName[i]);
    }

    return true;
}

void MapManager::Run(int currentStage)
{
    this->currentStage = currentStage;
    stages[this->currentStage]->Render();
}
