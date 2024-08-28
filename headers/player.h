#pragma once
#include "entity.h"

class Player: public Entity
{
public:
    Player(Vector2 _position, SDL_Texture* _texture, int _width = 16, int _height = 16);

public:
    void applyGravity(float delta);
    void update(float delta);
    void jump(float jump_velocity);

private:
    float y_velocity;
    const float y_accel = 250;
};