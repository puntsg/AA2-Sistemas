#pragma once
#include "Character.h"
#include <iostream>
enum class LeftCenterRightC
{
	LEFT = 0,
	CENTER = 1,
	RIGHT = 2
};
enum class UpCenterDownC {
	UP = 0,
	CENTER = 1,
	DOWN = 2
};
class Chest
	: public Character
{
private:
	bool isDestroyed;
	LeftCenterRightC xArea;
	UpCenterDownC yArea;
public:
	Chest(Vector2 vec, LeftCenterRightC _xArea, UpCenterDownC _yArea);
	void Draw(Vector2 offset)override;
	void Destroy();
	bool IsDestroyed();
};

