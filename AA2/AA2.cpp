#include "json/json.h"
#include "3Nodes/NodeMap.h"
#include <iostream>
#include "Game.h"

int main()
{
    Game* game = new Game();
    game->GameUpdate();
    return 0;
}
