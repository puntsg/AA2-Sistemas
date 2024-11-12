#include "Vector2.h"

Vector2::Vector2() {}

Vector2::Vector2(int x, int y) {
	this->X = x;
	this->Y = y;
}

Vector2::Vector2(Vector2* other) {
	*this = *other;
}

Vector2 Vector2::operator+=(Vector2 other)
{
	return *this + this;
}

Vector2 Vector2::operator+(Vector2 other) { //per sumar la posició al mapa
	
	Vector2 result = *this;
	result.X += other.X;
	result.Y += other.Y;

	return result;
}

Vector2 Vector2::operator-=(Vector2 other)
{
	return *this - this;
}

Vector2 Vector2::operator-(Vector2 other) {//per restar la posició al mapa

	Vector2 result = *this;
	result.X -= other.X;
	result.Y -= other.Y;

	return Vector2();
	return Vector2();
}