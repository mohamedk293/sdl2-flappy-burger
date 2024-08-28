#pragma once

#include <SDL.h>
#include "entity.h"
#include "player.h"
#include "pipe.h"
#include <vector>
#include <random>

enum class GameState {PLAYING, QUIT};

class Game
{
    public:
        Game();
    
    public:
        void initWindow(const char* windowTitle, int xPos, int yPos, int windowWidth, int windowHeight, Uint32 flags);
        void startGame();
        void clean();
        void renderEntity(Entity& entity);
        void renderPlayer(Player* player_ptr);
        void addEntity(Entity _entity);
        void setScale(float _scale);
        void setViewportDimensions(int _width, int _height);
        void initPlayer();
        void initPipes();
        void updatePipes(float delta);
        SDL_Texture* loadTexture(const char* filePath);
        float getDeltaTime();
    
    private:
        const float JUMP_FORCE = 110;
        const float TARGET_DELTA_TIME = 1.0/60;
        float m_scale;
        float m_current_time;
        float m_accumulated_dt;
        bool m_space_pressed;
        int m_score;
    
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        GameState m_currentState;
        std::vector<Entity> m_entities;
        std::vector<Pipe> m_pipes;
        // std::random_device device;
        // std::mt19937 random_num_gen(device());
        // std::uniform_int_distribution<std::mt19937::result_type> generate_random_height(10, 118); // we basically can call this for a random number in the range [10, 118]
        Player* m_player;

    private:
        void pollEvents();
        void update();
        void render();
        void clearRenderer();
        void renderEntities();
        void updatePlayer(float delta);
        int generatePipeLocation();
};