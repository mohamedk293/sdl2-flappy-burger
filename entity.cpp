#include <SDL.h>
#include <SDL_image.h>
#include "headers/entity.h"
#include <iostream>

Entity::Entity(Vector2 _position, SDL_Texture* _texture, int _width, int _height)
{
    m_position = _position;
    m_texture = _texture;
    m_current_frame.x = 0;
    m_current_frame.y = 0;
    m_current_frame.w = _width;
    m_current_frame.h = _height;
}

Vector2 Entity::getPosition()
{
    return m_position;
}

SDL_Rect Entity::getCurrentFrame()
{
    return m_current_frame;
}

SDL_Texture* Entity::getTexture(){
    return m_texture;
}

void Entity::freeTexture(){
    SDL_DestroyTexture(m_texture);
}

void Entity::move(Vector2 movement, float delta)
{
    m_position.x += movement.x * delta;
    m_position.y += movement.y * delta;
}