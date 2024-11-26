#include "Enemy.h"
#include <iostream>
#include "../Utils/Timer.h"
Enemy::Enemy(Vector2 pos)
{
	srand(time(NULL));
	this->position = pos;
	iCanMove = false;
	timeForNextMove = (2 + rand() % 6) * 1000;

	WaitForNextActionLoop();
}

void Enemy::Draw(Vector2 offset)
{
	std::cout << 'E';
}

void Enemy::Kill()
{
}

void Enemy::WaitForNextActionLoop() {
	
	timer->StartLoopTimer(timeForNextMove, [this]() {
		iCanMove = true;
		return true;
	});

}

void Enemy::DoneActing() {
	iCanMove = false;
}