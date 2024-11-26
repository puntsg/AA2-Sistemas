#pragma once
#include "Character.h"
#include "../dist/json/json.h"
#include "../Utils/Timer.h"
class Enemy :
    public Character
{
private:
    Timer* timer;

public:
    Enemy(Vector2 pos);
    void Draw(Vector2 offset)override;
    void Kill();
    void Decode(Json::Value json);
    Json::Value Encode();
    static Enemy* FromJson(Json::Value json);
    void WaitForNextActionLoop();
    void DoneActing();
    
    int timeForNextMove;
    bool iCanMove;
};

