#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "globals.h"

class Entity
{
public:
    Entity(Vector2 _position, SDL_Texture* _texture, int _width = 16, int _height = 16);

public:
    Vector2 getPosition();
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTexture();
    void freeTexture();
    void move(Vector2 movement, float delta);

protected:
    Vector2 m_position;
    SDL_Texture* m_texture;
    SDL_Rect m_current_frame;
};