#include "Collectable.h"
#include <iostream>

void Collectable::Draw(Vector2 offset)
{
	std::cout << icon;
}

void Collectable::Collect(Player* player)
{
	int random = rand() % 100;
	if (random % 2)
		player->potions++;
	else
		player->coins++;
}
