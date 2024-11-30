#pragma once
#include "Character.h"
#include <iostream>
class Chest
	: public Character
{
	bool isDestroyed;
public:
	Chest(Vector2 vec);
	void Draw(Vector2 offset)override;
	void Destroy();
	bool IsDestroyed();
};

