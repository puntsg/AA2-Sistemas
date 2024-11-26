#pragma once
#include "Utils/Timer.h"
#include "3Nodes/NodeMap.h"
#include "Game/Player.h"
#include "Game/Wall.h"
#include "InputSystem/InputSystem.h"
#include "Game/Enemy.h"
#include "Game/Chest.h"
#define VERTICAL_MAP_ZONES 3
#define HORIZONTAL_MAP_ZONES 3
#define ZONE_WIDTH 16
#define ZONE_HEIGHT 9
enum EDirection{
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
};
class Game
{
	
public:
	Game();
	void GameUpdate();
	void PrintMapAndHud();
	std::vector<Enemy*> allEnemies;
	std::vector<Character*> allchests;
private :
	void ChangeMapZone(EDirection dir);
	void MovePlayer(EDirection dir);
	void MoveEnemies();
	void MoveEnemy(EDirection dir, Enemy* enemy);
	bool canAttackMove = true;
	int currentVerticalZone, currentHorizontalZone;
	Timer* timer;
	NodeMap* maps[VERTICAL_MAP_ZONES][HORIZONTAL_MAP_ZONES] ;
	NodeMap* currentMap;
	Player* player;
	InputSystem* is;
	std::mutex _enemyMutex;
};

