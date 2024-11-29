#pragma once
#include "../3Nodes/Nodes.h" 
class Character :
    public INodeContent
{
public:
    virtual void Draw(Vector2 offset) = 0;
    Vector2 position;
    void Move(Vector2 dir);
};

