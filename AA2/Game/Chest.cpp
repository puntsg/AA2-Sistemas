#include "Chest.h"
Chest::Chest(Vector2 vec) {
	position = vec;
	icon = 'C';
}

void Chest::Draw(Vector2 offset)
{
	std::cout << icon;
}
