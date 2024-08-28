#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "headers/game.h"
#include "headers/entity.h"

int main(void)
{
    // checking if everything is okay
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
        std::cout << "SDL exited out with an error: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG Init has failed with an error: " << SDL_GetError() << std::endl; 

    // initializing the game
    Game game;
    game.initWindow("My SDL2 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);
    game.setViewportDimensions(320, 180);
    
    // testing adding background
    SDL_Texture* test_texture = game.loadTexture("assets/background.png");
    Entity bgEntity({0, 0}, test_texture, 320, 180);
    game.addEntity(bgEntity);

    // start game loop
    game.startGame();

    // destroy window and other stuff and what not
    game.clean();

    SDL_Quit();
}