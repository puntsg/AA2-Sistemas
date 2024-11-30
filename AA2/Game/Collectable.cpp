#include "Collectable.h"
#include <iostream>

Collectable::Collectable(Vector2 _pos) {
	position = _pos;	
}

void Collectable::Draw(Vector2 offset)
{
	std::cout << 'O';
}

void Collectable::Collect(Player* player)
{
	int random = rand() % 100;
	if (random % 2)
		player->potions++;
	else
		player->coins++;
}
