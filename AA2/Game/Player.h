#pragma once
#include"Character.h"
#include "Weapon.h"
#include "../dist/json/json.h"
class Player :
    public Character
{
public:
    Player(Vector2 pos);
    Weapon* weapon;
    void Draw(Vector2 offset)override;
    int coins;
    int lifes;
    int potions;
    void Decode(Json::Value json);
    void CollectMysteriousCollectable();
    Json::Value Encode();
    static Player* FromJson(Json::Value json);
    void Heal();
    void Hurt();
};

