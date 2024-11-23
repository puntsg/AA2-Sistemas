#pragma once
#include "../3Nodes/Nodes.h" 
class Character :
    public Node, public INodeContent
{
    virtual void Draw(Vector2 offset) = 0;
};

