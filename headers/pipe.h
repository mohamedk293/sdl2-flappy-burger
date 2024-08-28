#pragma once
#include "entity.h"
#include "player.h"

class Pipe: public Entity
{
public:
    Pipe(Vector2 _position, SDL_Texture* _texture, int _width = 16, int _height = 16);

public:
    void update(float delta);
    void resetPosition();
    void setHeight(int height);
    bool passedScreen();
    bool collidingWithPlayer(Player* player);

private:
    float SPEED = 20;
    float X_SPAWN_POSITION = 320;
    float PIPE_WIDTH_LEEWAY = 5;
};