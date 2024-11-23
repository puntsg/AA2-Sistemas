#include "Player.h"
Player::Player(Vector2 pos) {
	icon = 'P';
	coins = 0;
	lifes = 0;
	potions = 0;
}

void Player::Draw(Vector2 offset)
{
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
