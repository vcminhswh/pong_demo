#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "vec2.hh"

class PlayerScore {
public:
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect rect;

	PlayerScore(Vec2 position, SDL_Renderer *renderer, TTF_Font *font);
	~PlayerScore();
	void draw();
	void set_score(int score);

};
