#include "player_score.hh"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

PlayerScore::PlayerScore(Vec2 position, SDL_Renderer *renderer, TTF_Font *font): renderer(renderer), font(font) {
	surface = TTF_RenderText_Solid(font, "0", {0xFF,0xFF,0xFF,0xFF});
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = width;
	rect.h = height;
}

PlayerScore::~PlayerScore() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void PlayerScore::draw() {
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void PlayerScore::set_score(int score) {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), {0xff, 0xff, 0xff, 0xff});
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}


