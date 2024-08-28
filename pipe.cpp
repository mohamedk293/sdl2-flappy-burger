#include "headers/pipe.h"

Pipe::Pipe(Vector2 _position, SDL_Texture* _texture, int _width, int _height) : Entity(_position, _texture, _width, _height)
{
    // m_position.x = X_SPAWN_POSITION;
}

void Pipe::update(float delta)
{
    m_position.x -= SPEED * delta;
}

bool Pipe::passedScreen()
{
    return m_position.x < -32; // hardcoded width :D
}

bool Pipe::collidingWithPlayer(Player* player) // fix this lolol
{
    Vector2 player_position = player->getPosition();
    SDL_Rect player_frame = player->getCurrentFrame();

    return (player_position.x > m_position.x - player_frame.w + PIPE_WIDTH_LEEWAY && player_position.x < m_position.x + m_current_frame.w - PIPE_WIDTH_LEEWAY && player_position.y > m_position.y - player_frame.h && player_position.y < m_position.y + m_current_frame.h);
}

void Pipe::resetPosition()
{
    m_position.x = X_SPAWN_POSITION;
}

void Pipe::setHeight(int height)
{
    m_position.y = height;
}