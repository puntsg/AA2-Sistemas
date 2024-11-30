#pragma once
#include "../3Nodes/Vector2.h"
#include "../3Nodes/INodeContent.h"
#include "Player.h"
class Collectable : public INodeContent {
public:
	Collectable() { icon = 'O'; }
	void Draw(Vector2 offset) override;
	void Collect(Player* player);
};