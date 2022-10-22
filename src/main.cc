#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <chrono>

#include "ball.hh"
#include "paddle.hh"
#include "player_score.hh"
#include "options.hh"
#include "collision.hh"

enum Buttons {
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};


int main() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window *window = SDL_CreateWindow(
			"Pong",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH,WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font *score_font = TTF_OpenFont("DejaVuSansMono.ttf", 40);
	

	
	Ball ball(
	Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f),
	(WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)), Vec2(BALL_SPEED, 0.0f));

	Paddle paddle1(Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)), Vec2(0.0f,0.0f));
	Paddle paddle2(Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)), Vec2(0.0f,0.0f));

	PlayerScore score1(Vec2(WINDOW_WIDTH/4.0f,20),renderer,score_font);
	PlayerScore score2(Vec2(3.0f*WINDOW_WIDTH/4.0f,20),renderer,score_font);
	

	// Insert Game Logic
	{

		int player1_score = 0;
		int player2_score = 0;
		bool running = true;
		bool buttons[4] = {};
		float dt = 0.0f;

		while(running) {
			SDL_Event event;
			auto start_time = std::chrono::high_resolution_clock::now();
			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_QUIT:
						running = false;
						break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym) {
							case SDLK_ESCAPE:
								running = false;
								break;
							case SDLK_w:
								buttons[Buttons::PaddleOneUp] = true;
								break;
							case SDLK_s:
								buttons[Buttons::PaddleOneDown] = true;
								break;
							case SDLK_UP:
								buttons[Buttons::PaddleTwoUp] = true;
								break;
							case SDLK_DOWN:
								buttons[Buttons::PaddleTwoDown] = true;
								break;
						}
						break;
					case SDL_KEYUP:
						switch(event.key.keysym.sym) {
							case SDLK_w:
								buttons[Buttons::PaddleOneUp] = false;
								break;
							case SDLK_s:
								buttons[Buttons::PaddleOneDown] = false;
								break;
							case SDLK_UP:
								buttons[Buttons::PaddleTwoUp] = false;
								break;
							case SDLK_DOWN:
								buttons[Buttons::PaddleTwoDown] = false;
								break;
					}
				}
			}


			if(buttons[Buttons::PaddleOneUp]) paddle1.velocity.y = -PADDLE_SPEED;
			else if(buttons[Buttons::PaddleOneDown]) paddle1.velocity.y = PADDLE_SPEED;
			else paddle1.velocity.y = 0.0f;

			if(buttons[Buttons::PaddleTwoUp]) paddle2.velocity.y = -PADDLE_SPEED;
			else if(buttons[Buttons::PaddleTwoDown]) paddle2.velocity.y = PADDLE_SPEED;
			else paddle2.velocity.y = 0.0f;

			paddle1.update(dt);
			paddle2.update(dt);

			ball.update(dt);

			Contact paddle1_contact = ball.check_paddle_collision(paddle1);
			Contact paddle2_contact = ball.check_paddle_collision(paddle2);
			Contact wall_contact = ball.check_wall_collision();
				
			if(paddle1_contact.type != CollisionType::None) {
				ball.collide_with_paddle(paddle1_contact);
			}
			else if (paddle2_contact.type != CollisionType::None) {
				ball.collide_with_paddle(paddle2_contact);
			}
			else if(wall_contact.type != CollisionType::None) {
				ball.collide_with_wall(wall_contact);

				if(wall_contact.type == CollisionType::Left) {
					++player2_score;
					score2.set_score(player2_score);
				}
				else if(wall_contact.type == CollisionType::Right) {
					++player1_score;
					score1.set_score(player1_score);
				}
			}


			SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,0xff);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
			SDL_RenderDrawLine(renderer, WINDOW_WIDTH/2,0,WINDOW_WIDTH/2,WINDOW_HEIGHT);
			ball.draw(renderer);
			paddle1.draw(renderer);
			paddle2.draw(renderer);
			score1.draw();
			score2.draw();

			SDL_RenderPresent(renderer);

			auto stop_time = std::chrono::high_resolution_clock::now();
			dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stop_time - start_time).count();
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(score_font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
