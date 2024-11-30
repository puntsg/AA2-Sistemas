#include "Collectable.h"
#include <iostream>
#include "../Utils/ConsoleControl.h"
#include "Sword.h"
#include "Polearm.h"
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
	int random = rand() % 150;
	if (random < 50) {
		player->potions++;
		CC::SetPosition(9, 13);
		std::cout << player->potions;
	}
	else if (random < 100){
		player->coins++;
		CC::SetPosition(8, 11);
		std::cout << player->coins;
	}
	else if (random < 125) {
		player->weapon = new Sword();
		CC::SetPosition(7, 14);
		std::cout << player->weapon->name << "    ";
	}
	else {
		player->weapon = new Polearm();
		CC::SetPosition(7, 14);
		std::cout << player->weapon->name << "    ";
	}
	
}
