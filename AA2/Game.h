#pragma once
#include "Utils/Timer.h"
#include "3Nodes/NodeMap.h"
#include "Game/Player.h"
#include "Game/Wall.h"
#include "InputSystem/InputSystem.h"
#define VERTICAL_MAP_ZONES 3
#define HORIZONTAL_MAP_ZONES 3
#define ZONE_WIDTH 16
#define ZONE_HEIGHT 9
enum EDirection{
		UP,
		DOWN,
		LEFT,
		RIGHT
};
class Game
{
	
public:
	Game();
	void GameUpdate();
	void PrintMapAndHud();
private :
	void ChangeMapZone(EDirection dir);
	void MovePlayer(EDirection dir);
	bool canAttackMove = true;
	int currentVerticalZone, currentHorizontalZone;
	Timer* timer;
	NodeMap* maps[VERTICAL_MAP_ZONES][HORIZONTAL_MAP_ZONES] ;
	NodeMap* currentMap;
	Player* player;
	InputSystem* is;
};

