#include "Collectable.h"
#include <iostream>
#include "../Utils/ConsoleControl.h"
Collectable::Collectable(Vector2 _pos) {
	position = _pos;	
	icon = 'O';
}

void Collectable::Draw(Vector2 offset)
{
	std::cout << icon;
}

void Collectable::Collect(Player* player)
{
	srand(time(NULL));
	int random = rand() % 100;
	if (random > 50) {
		player->potions++;
		CC::SetPosition(9, 13);
		std::cout << player->potions;
	}
	else {
		player->coins++;
		CC::SetPosition(8, 11);
	}
	
}
