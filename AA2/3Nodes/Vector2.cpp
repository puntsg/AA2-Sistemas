#include "Vector2.h"

Vector2::Vector2() {}

Vector2::Vector2(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(Vector2* other)
{
	*this = other;
}

Vector2 Vector2::operator+(Vector2 other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(Vector2 other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator+=(Vector2 other)
{
	return *this + other;
}

Vector2 Vector2::operator-=(Vector2 other)
{
	return *this - other;
}
