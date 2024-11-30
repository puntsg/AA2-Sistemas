#pragma once
#include "../3Nodes/Vector2.h"
#include "../3Nodes/INodeContent.h"
#include "Player.h"
class Collectable : public INodeContent {
public:
	Vector2 position;
	Collectable(Vector2 _pos);
	void Draw(Vector2 offset) override;
	void Collect(Player* player);
};