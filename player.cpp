#include "headers/player.h"
#include <iostream>

Player::Player(Vector2 _position, SDL_Texture* _texture, int _width, int _height) : Entity(_position, _texture, _width, _height)
{
    y_velocity = 0;
}

void Player::applyGravity(float delta)
{
    y_velocity += y_accel * delta;
}

void Player::update(float delta)
{
    applyGravity(delta);
    m_position.y += y_velocity * delta;
    // std::cout << "Position: " << m_position.y << ", Delta: " << delta << std::endl;
    // std::cout << "Velocity: " << y_velocity << std::endl;
}

void Player::jump(float jump_velocity)
{
    y_velocity = -jump_velocity;
}