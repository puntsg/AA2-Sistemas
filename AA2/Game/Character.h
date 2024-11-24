#pragma once
#include "../3Nodes/Nodes.h" 
class Character :
    public INodeContent
{
    virtual void Draw(Vector2 offset) = 0;
public:
    Vector2 position;
    inline char GetIcon() const;
    void Move(Vector2 dir);
};

