#include "Character.h"

void Character::Move(Vector2 dir)
{
	this->position = this->position + dir;
}
