#pragma once
#include "Character.h"
#include "../dist/json/json.h"
class Enemy :
    public Character
{
public:
    Enemy(Vector2 pos);
    void Draw(Vector2 offset)override;
    void Kill();
    void Decode(Json::Value json);
    Json::Value Encode();
    static Enemy* FromJson(Json::Value json);
   
};

