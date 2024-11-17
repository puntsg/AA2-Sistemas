#include "Game.h"
#include "Game/DataSaver.h"

Game::Game()
{
    map = new NodeMap * *[VERTICAL_MAP_ZONES];
    for (int i = 0; i < VERTICAL_MAP_ZONES; i++) {
        map[i] = new NodeMap * [HORIZONTAL_MAP_ZONES];
        for (int j = 0; j < HORIZONTAL_MAP_ZONES; j++) {
            map[i][j] = new NodeMap(Vector2(ZONE_WIDTH, ZONE_HEIGHT), Vector2(0, 0));
        }
    }

    timer->StartLoopTimer(1000, [this]() {
        //DataSaver::Instance().SaveData();
        return true;
    });
}
