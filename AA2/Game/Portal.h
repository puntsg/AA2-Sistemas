#pragma once
#include "Character.h"


class Portal
	: public Character
{
public:
	Portal();

	void Draw(Vector2 offset) override;

};


