#pragma once
class Vector2
{
public:
	int x = 0;
	int y = 0;
	Vector2();
	Vector2(int _x, int _y);
	Vector2(Vector2* other);
	Vector2 operator+(Vector2 other);
	Vector2 operator-(Vector2 other);
	Vector2 operator+=(Vector2 other);
	Vector2 operator-=(Vector2 other);
	static Vector2 up() {return Vector2(0,1);}
	static Vector2 down(){return Vector2(0,-1);}
	static Vector2 left(){return Vector2(-1,0);}
	static Vector2 right(){return Vector2(1,0);}
	static Vector2 one(){return Vector2(1,1);}
	static Vector2 reverse(){return Vector2(-1,-1);}
	static Vector2 zero(){return Vector2(0,0);}
};

