#include "Game.h"
#include "Game/DataSaver.h"
#include "Utils/ConsoleControl.h"

Game::Game()
{


    NodeMap map(Vector2(10, 6), Vector2(0, 0));
    player = new Player(Vector2(0,0));
    /*map = new NodeMap * *[VERTICAL_MAP_ZONES];
    for (int i = 0; i < VERTICAL_MAP_ZONES; i++) {
        map[i] = new NodeMap * [HORIZONTAL_MAP_ZONES];
        for (int j = 0; j < HORIZONTAL_MAP_ZONES; j++) {
            map[i][j] = new NodeMap(Vector2(ZONE_WIDTH, ZONE_HEIGHT), Vector2(0, 0));
        }
    }
*/
    map.UnsaveDraw();
    player->DrawContent(player->position);
    is = new InputSystem();
    InputSystem::KeyBinding* kb = is->KeyAddListener(K_1, [this]() {
        player->Move(Vector2(-1,-1));
        player->DrawContent(player->position);
    });
    timer->StartLoopTimer(5000, [this]() {
        //DataSaver::Instance().SaveData();
        return true;
    });
    is->StartListen();
    while (true)
    {

    }
}
