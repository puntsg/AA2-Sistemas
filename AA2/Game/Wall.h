#pragma once
#include "../3Nodes/Nodes.h" 
class Wall:
	public INodeContent
{
public:
	Wall() { icon = '#'; }
	void Draw(Vector2 offset)override{}
};