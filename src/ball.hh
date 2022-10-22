#pragma once

#include "vec2.hh"
#include "collision.hh"
#include "paddle.hh"
#include "options.hh"
#include <SDL2/SDL.h>


class Ball {
public:
	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};	

	Ball(Vec2 position, Vec2 velocity);

	void update(float dt);
	void draw(SDL_Renderer *renderer);

	void collide_with_paddle(const Contact &contact);
	void collide_with_wall(const Contact &contact);
	Contact check_paddle_collision(const Paddle &paddle);
	Contact check_wall_collision();
};
