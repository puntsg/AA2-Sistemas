#include "Chest.h"
Chest::Chest(Vector2 vec, LeftCenterRightC _xArea, UpCenterDownC _yArea) {
	position = vec;
	icon = 'C';
	isDestroyed = false;
	xArea = _xArea;
	yArea = _yArea;
}

void Chest::Draw(Vector2 offset)
{
	std::cout << icon;
}

void Chest::Destroy()
{
	isDestroyed = true;
}

bool Chest::IsDestroyed()
{
	return isDestroyed;
}
