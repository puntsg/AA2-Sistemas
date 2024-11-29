#pragma once
#include "Character.h"


class Portal
	: public Character
{
public:
	Portal() { icon = 'P'; };

	void Draw(Vector2 offset) override;

};


