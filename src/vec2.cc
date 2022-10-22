#include "vec2.hh"

Vec2 Vec2::operator+(const Vec2 &rhs) {
	return Vec2(x+rhs.x,y+rhs.y);
}

Vec2 &Vec2::operator+=(const Vec2 &rhs) {
	x+=rhs.x;
	y+=rhs.y;

	return *this;
}

Vec2 Vec2::operator*(float rhs) {
	return Vec2(x*rhs,y*rhs);
}
