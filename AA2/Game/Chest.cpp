#include "Chest.h"
Chest::Chest(Vector2 vec) {
	position = vec;
	isDestroyed = false;
}

void Chest::Draw(Vector2 offset)
{
	std::cout << 'C';
}

void Chest::Destroy()
{
	isDestroyed = true;
}

bool Chest::IsDestroyed()
{
	return isDestroyed;
}
