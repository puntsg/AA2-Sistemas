#include "Player.h"
#include <iostream>
Player::Player(Vector2 pos) {
	position = pos;
	coins = 0;
	lifes = 0;
	potions = 0;
	icon = 'J';
}

void Player::Draw(Vector2 offset)
{
	std::cout << this->icon;
}

void Player::Decode(Json::Value json)
{
	
}

Json::Value Player::Encode()
{
	return Json::Value();
}

Player* Player::FromJson(Json::Value json)
{
	return nullptr;
}

void Player::Heal()
{
	if (potions > 0 && lifes <= 2) {
		this->lifes++;
		this->potions--;
	}
}

void Player::Hurt()
{
	lifes--;
	if (lifes == 0)
		abort();
}
