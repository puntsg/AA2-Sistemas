#pragma once
#include "Character.h"
#include "../dist/json/json.h"
#include "../Utils/Timer.h"
enum class LeftCenterRight
{
    LEFT = 0,
    CENTER = 1,
    RIGHT = 2    
};
enum class UpCenterDown {
    UP = 0,
    CENTER = 1,
    DOWN = 2
};
class Enemy :
    public Character
{
private:
    Timer* timer;

public:
    Enemy(Vector2 pos, LeftCenterRight _xArea, UpCenterDown _yArea);
    void Draw(Vector2 offset)override;
    void Kill();
    void Decode(Json::Value json);
    Json::Value Encode();
    static Enemy* FromJson(Json::Value json);
    void WaitForNextActionLoop();
    void DoneActing();
    
    LeftCenterRight xArea;
    UpCenterDown yArea;
    int timeForNextMove;
    bool iCanMove;
};

