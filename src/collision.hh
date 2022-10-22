#pragma once


enum class CollisionType {
	None,
	Top,
	Middle, 
	Bottom,
	Left,
	Right
};

struct Contact {
	CollisionType type;
	float penetration;
};



