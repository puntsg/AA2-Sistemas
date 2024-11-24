#include "Character.h"

void Character::Move(Vector2 dir)
{
	this->position += dir;
}
