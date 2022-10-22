#include "ball.hh"
#include "collision.hh"

Ball::Ball(Vec2 position, Vec2 velocity): position(position), velocity(velocity) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);
	rect.w = BALL_WIDTH;
	rect.h = BALL_HEIGHT;
}

void Ball::draw(SDL_Renderer *renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_RenderFillRect(renderer, &rect);
}

void Ball::update(float dt) {
	position += velocity * dt;
}


void Ball::collide_with_paddle(const Contact &contact) {
	position.x += contact.penetration;
	velocity.x = -velocity.x;

	if(contact.type == CollisionType::Top) velocity.y = -0.75f * BALL_SPEED;
	else if(contact.type == CollisionType::Bottom) velocity.y = 0.75f * BALL_SPEED; 
}

void Ball::collide_with_wall(const Contact &contact) {
	if(contact.type == CollisionType::Top || contact.type == CollisionType::Bottom) velocity.y = -velocity.y;
	else if(contact.type == CollisionType::Left) {
		position.x = WINDOW_WIDTH / 2.0f;
		position.y = WINDOW_HEIGHT / 2.0f;
		velocity.x = BALL_SPEED;
		velocity.y = 0;
	}
	else if(contact.type == CollisionType::Right) {
		position.x = WINDOW_WIDTH / 2.0f;
		position.y = WINDOW_HEIGHT / 2.0f;
		velocity.x = -BALL_SPEED;
		velocity.y = 0;
	}
}

Contact Ball::check_paddle_collision(const Paddle &paddle) {
	float ball_left = position.x;
	float ball_right = position.x + BALL_WIDTH;
	float ball_top = position.y;
	float ball_bottom = position.y + BALL_HEIGHT;

	float paddle_left = paddle.position.x;
	float paddle_right = paddle.position.x + PADDLE_WIDTH;
	float paddle_top = paddle.position.y;
	float paddle_bottom = paddle.position.y + PADDLE_HEIGHT;

	Contact contact{};

	if (ball_left >= paddle_right)
	{
		return contact;
	}

	if (ball_right <= paddle_left)
	{
		return contact;
	}

	if (ball_top >= paddle_bottom)
	{
		return contact;
	}

	if (ball_bottom <= paddle_top)
	{
		return contact;
	}

	float paddle_range_upper = paddle_bottom - (2.0f * PADDLE_HEIGHT / 3.0f);
	float paddle_range_middle = paddle_bottom - (PADDLE_HEIGHT / 3.0f);

	if (velocity.x < 0)
	{
		// _left paddle
		contact.penetration = paddle_right - ball_left;
	}
	else if (velocity.x > 0)
	{
		// _right paddle
		contact.penetration = paddle_left - ball_right;
	}

	if ((ball_bottom > paddle_top)
	    && (ball_bottom < paddle_range_upper))
	{
		contact.type = CollisionType::Top;
	}
	else if ((ball_bottom > paddle_range_upper)
	     && (ball_bottom < paddle_range_middle))
	{
		contact.type = CollisionType::Middle;
	}
	else
	{
		contact.type = CollisionType::Bottom;
	}

	return contact;

}

Contact Ball::check_wall_collision() {
	float ball_left = position.x;
	float ball_right = position.x + BALL_WIDTH;
	float ball_top = position.y;
	float ball_bottom = position.y + BALL_HEIGHT;

	Contact contact;

	if(ball_left < 0.0f) contact.type = CollisionType::Left;
	else if(ball_top < 0.0f) contact.type = CollisionType::Top;
	else if(ball_right > WINDOW_WIDTH) contact.type = CollisionType::Right;
	else if(ball_bottom > WINDOW_HEIGHT) contact.type = CollisionType::Bottom;

	return contact;
}
