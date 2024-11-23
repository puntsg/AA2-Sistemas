#include "Game.h"
#include "Game/DataSaver.h"
#include "Game/Player.h"
#include "Utils/ConsoleControl.h"

Game::Game()
{


    NodeMap map(Vector2(10, 6), Vector2(0, 0));
    Player* player = new Player(Vector2(1,5));
    /*map = new NodeMap * *[VERTICAL_MAP_ZONES];
    for (int i = 0; i < VERTICAL_MAP_ZONES; i++) {
        map[i] = new NodeMap * [HORIZONTAL_MAP_ZONES];
        for (int j = 0; j < HORIZONTAL_MAP_ZONES; j++) {
            map[i][j] = new NodeMap(Vector2(ZONE_WIDTH, ZONE_HEIGHT), Vector2(0, 0));
        }
    }
*/
    map.UnsaveDraw();
    CC::Lock();
    CC::SetPosition(player->position.x,player->position.y);
    std::cout << player->GetIcon();
    //CC::FillWithCharacter(player->GetIcon(),CC::BLACK,CC::WHITE);
    CC::Unlock();
    
    timer->StartLoopTimer(5000, [this]() {
        //DataSaver::Instance().SaveData();
        return true;
    });
}
