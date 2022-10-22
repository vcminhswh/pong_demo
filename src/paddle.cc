#include "paddle.hh"

Paddle::Paddle(Vec2 position, Vec2 velocity): position(position), velocity(velocity) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = PADDLE_WIDTH;
	rect.h = PADDLE_HEIGHT;
}

void Paddle::draw(SDL_Renderer *renderer) {
	rect.y = static_cast<int>(position.y);
	SDL_RenderFillRect(renderer, &rect);
}

void Paddle::update(float dt) {
	position += velocity * dt;

	if(position.y < 0) position.y = 0;
	else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT)) {
		position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
	}
}
