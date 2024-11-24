#pragma once
#include "Utils/Timer.h"
#include "3Nodes/NodeMap.h"
#include "Game/Player.h"
#include "InputSystem/InputSystem.h"
#define VERTICAL_MAP_ZONES 3
#define HORIZONTAL_MAP_ZONES 3
#define ZONE_WIDTH 16
#define ZONE_HEIGHT 9
class Game
{
public:
	Game();
private :
	Timer* timer;
	NodeMap*** map;
	Player* player;
	InputSystem* is;
};

