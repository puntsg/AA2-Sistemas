#pragma once
#include "Utils/Timer.h"
#include "3Nodes/NodeMap.h"
#include "Game/Player.h"
#include "Game/Wall.h"
#include "InputSystem/InputSystem.h"
#define VERTICAL_MAP_ZONES 3
#define HORIZONTAL_MAP_ZONES 3
#define ZONE_WIDTH 10
#define ZONE_HEIGHT 10
class Game
{
	enum EDirection{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
public:
	Game();
	void GameUpdate();
	void PrintMapAndHud();
private :
	void MovePlayer(EDirection dir);
	bool canAttackMove = true;
	Timer* timer;
	NodeMap* map;
	Player* player;
	InputSystem* is;
};

