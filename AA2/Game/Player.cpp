#include "Player.h"
#include <iostream>
#include "../Utils/ConsoleControl.h"
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
	lifes = json["lifes"].asInt();
	potions = json["potions"].asInt();
	coins = json["coins"].asInt();
}

void Player::CollectMysteriousCollectable()
{
	int obj = rand() % 2;

	switch (obj)
	{
	case 0:
		coins++;
		break;
	case 1:
		potions++;
		break;
	
	default:
		break;
	}
}

Json::Value Player::Encode()
{
	Json::Value playerJson;
	playerJson["coins"] = coins;
	playerJson["lifes"] = lifes;
	playerJson["potions"] = potions;
	return playerJson;
}

Player* Player::FromJson(Json::Value& json,Vector2 playerPos)
{
	Player* player = new Player(playerPos);
	player->Decode(json);
	return player;
}

void Player::Heal()
{
	if (potions > 0 && lifes <= 2) {
		this->lifes++;
		this->potions--;
		CC::SetPosition(6, 12);
		std::cout << lifes;
		CC::SetPosition(9, 13);
		std::cout << potions;
	}
}

void Player::Hurt()
{
	lifes--;
	if (lifes == 0)
		abort();
}
