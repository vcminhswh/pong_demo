#pragma once

#include "vec2.hh"
#include "options.hh"

#include <SDL2/SDL.h>


class Paddle {
public:
	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};

	Paddle(Vec2 position, Vec2 velocity);
	void draw(SDL_Renderer *renderer);
	void update(float dt);
};
