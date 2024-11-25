#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Vector2 pos)
{
	this->position = pos;
}

void Enemy::Draw(Vector2 offset)
{
	std::cout << 'E';
}

void Enemy::Kill()
{
}
