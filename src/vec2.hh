#pragma once

class Vec2 {
public:
	float x, y;

	Vec2(): x(0), y(0) {}
	Vec2(float x, float y): x(x), y(y) {}

	Vec2 operator+(Vec2 const &rhs);
	Vec2 &operator+=(Vec2 const &rhs);
	Vec2 operator*(float rhs);
};
