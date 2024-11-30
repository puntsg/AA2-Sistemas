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
	srand(time(NULL));
	int random = rand() % 100;
	if (random > 50)
		player->potions++;
	else
		player->coins++;
}
