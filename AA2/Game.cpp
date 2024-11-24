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
    
    //In case of pressing D
    InputSystem::KeyBinding* kb1 = is->KeyAddListener(K_D, [this]() {
        if ((player->position + Vector2(1,0)).x < Vector2(10, 6).x)
        
            player->Move(Vector2(1,0));
        });
    
    // pressing S
    InputSystem::KeyBinding* kb2 = is->KeyAddListener(K_S, [this]() {
        if ((player->position + Vector2(0, 1)).y < Vector2(10, 6).y)
            player->Move(Vector2(0, 1));
        });

    //In case of pressing A
    InputSystem::KeyBinding* kb3 = is->KeyAddListener(K_A, [this]() {
        if ((player->position + Vector2(-1, 0)).x >= 0)

        player->Move(Vector2(-1, 0));
        });

    // pressing W
    InputSystem::KeyBinding* kb4 = is->KeyAddListener(K_W, [this]() {
        if ((player->position + Vector2(0, -1)).y >= 0)
        player->Move(Vector2(0, -1));
        });

    //In case of pressing 
    /*InputSystem::KeyBinding* kb = is->KeyAddListener(K_1, [this]() {
        if ((player->position + Vector2(1, 1)).x < Vector2(10, 6).x &&
        (player->position + Vector2(1, 1)).y < Vector2(10, 6).y)
            player->Move(Vector2(1, 1));
        });*/

    //Timer for saving files
    timer->StartLoopTimer(5000, [this]() {
        //DataSaver::Instance().SaveData();
        return true;
    });

    //Paint map then player
    timer->StartLoopTimer(100, [this, &map]() {
        map.UnsaveDraw();
        player->DrawContent(player->position);
        return true;
        });
    is->StartListen();
    while (true)
    {

    }
}
