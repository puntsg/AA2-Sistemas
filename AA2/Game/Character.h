#pragma once
#include "../3Nodes/Nodes.h" 
class Character :
    public Node, public INodeContent
{
    virtual void Draw(Vector2 offset) = 0;
public:
    Vector2 position;
    inline char GetIcon() const { return this->icon; }
};

