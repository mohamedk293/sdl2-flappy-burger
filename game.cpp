#include "headers/game.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

Game::Game()
{
    m_window = nullptr;
    m_renderer = nullptr;
    m_currentState = GameState::PLAYING;
    m_scale = 1;
    m_current_time = 0;
    m_accumulated_dt = 0;
    m_player = nullptr;
    m_space_pressed = false;
    m_score = 0;
};

void Game::initWindow(const char* windowTitle, int xPos, int yPos, int windowWidth, int windowHeight, Uint32 flags)
{
    // if (SDL_Init(SDL_INIT_EVERYTHING) > 0){
    //     std::cout << "SDL exited out with an error: " << SDL_GetError() << std::endl;
    // } else {
    m_window = SDL_CreateWindow("SDL2 Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    
    // need integer scaling
    SDL_RenderSetIntegerScale(m_renderer, SDL_TRUE);
    //}

    initPlayer();
    initPipes();
}

void Game::startGame()
{
    update(); // starts the game loop
}

void Game::update()
{
    float upper_run_limit = 0.025;
    while (m_currentState != GameState::QUIT)
    {
        float dt = getDeltaTime();
        m_accumulated_dt += dt;

        if (m_accumulated_dt >= TARGET_DELTA_TIME)
        {
            //std::cout << "Delta time: " << m_accumulated_dt << "s\n";
            if (m_accumulated_dt <= upper_run_limit)
            {
                pollEvents();
                // display loop below
                clearRenderer();

                renderEntities();
                updatePipes(m_accumulated_dt);
                updatePlayer(m_accumulated_dt);

                render();
            }
            m_accumulated_dt -= TARGET_DELTA_TIME;
            m_space_pressed = false;
        }
        else 
        {
            // std::cout << "Current accumulated dt: " << m_accumulated_dt << "s" << std::endl;
            // stop running at 100% cpu you bozo
            SDL_Delay((TARGET_DELTA_TIME - m_accumulated_dt) * 1000);
        }
    }
}

void Game::pollEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_currentState = GameState::QUIT;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                m_space_pressed = true;
            }
            break;
    }
}

void Game::setViewportDimensions(int _width, int _height)
{
    SDL_RenderSetLogicalSize(m_renderer, _width, _height);
}

SDL_Texture* Game::loadTexture(const char* filePath)
{
    SDL_Texture* new_texture = nullptr;
    new_texture = IMG_LoadTexture(m_renderer, filePath);

    if (new_texture == nullptr)
        std::cout << "SDL could not load image from file path " << filePath << std::endl;
    
    return new_texture;
}

void Game::renderEntity(Entity& entity)
{
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = entity.getPosition().x;
    dest.y = entity.getPosition().y;
    dest.w = src.w * m_scale;
    dest.h = src.h * m_scale;

    SDL_RenderCopy(m_renderer, entity.getTexture(), &src, &dest);
}

void Game::renderPlayer(Player* player_ptr)
{
    SDL_Rect src;
    src.x = player_ptr->getCurrentFrame().x;
    src.y = player_ptr->getCurrentFrame().y;
    src.w = player_ptr->getCurrentFrame().w;
    src.h = player_ptr->getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = player_ptr->getPosition().x;
    dest.y = player_ptr->getPosition().y;
    dest.w = src.w * m_scale;
    dest.h = src.h * m_scale;

    SDL_RenderCopy(m_renderer, player_ptr->getTexture(), &src, &dest);
}

void Game::renderEntities()
{
    for (auto &entity: m_entities)
    {
        renderEntity(entity);
    }
}

void Game::setScale(float _scale)
{
    if (_scale > 0)
        m_scale = _scale;
    else
        std::cout << "Invalid scale float given." << std::endl;
}

void Game::render()
{
    SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(m_window);
    delete m_player;
}

void Game::clearRenderer()
{
    SDL_RenderClear(m_renderer);
}

void Game::addEntity(Entity _entity)
{
    m_entities.push_back(_entity);
}

float Game::getDeltaTime()
{
    float new_time = SDL_GetTicks() * 0.001f;
    float old_time = m_current_time;
    m_current_time = new_time;

    return new_time - old_time;
}

void Game::initPlayer()
{
    SDL_Texture* player_texture = loadTexture("assets/burger.png");
    //m_player.reset(new Player({0, 0}, player_texture));
    m_player = new Player({0, 0}, player_texture);

    if (m_player == nullptr)
    {
        std::cout << "Something went wrong when initializing the player!" << std::endl;
    }
}

void Game::updatePlayer(float delta)
{
    if (m_player != nullptr)
    {
        if (m_space_pressed)
        {
            m_player->jump(JUMP_FORCE);
        }
        m_player->update(delta);
        renderPlayer(m_player);
    }
    else
    {
        std::cout << "whoopsies game's player is a nullptr reference :P" << std::endl;
    }
}

void Game::initPipes()
{
    int amount_of_pipes = 5; // change this to make game harder
    float pipe_gap = 64;
    // loading textures :P
    SDL_Texture* top_pipe_texture = loadTexture("assets/top_pipe.png");
    SDL_Texture* bottom_pipe_texture = loadTexture("assets/bottom_pipe.png");

    for (int i = 0; i < amount_of_pipes; i++)
    {
        // we need to create a bottom pipe and top pipe;
        float x_gap = 96;
        float x_position = 320 + i * x_gap;
        float y_offset = generatePipeLocation(); // 128/2 = 64, offseting the pipes to the "center"
        float y_position = -y_offset; // TODO: make this random
        float gap_offset = 128; // height of the pipe texture added to make gap actually work :P

        Pipe top_pipe({x_position, y_position}, top_pipe_texture, 32, 128);
        Pipe bottom_pipe({x_position, y_position + pipe_gap + gap_offset}, bottom_pipe_texture, 32, 128);

        m_pipes.push_back(top_pipe);
        m_pipes.push_back(bottom_pipe);
    }

    // std::cout << "Amount of pipes: " << m_pipes.size() << std::endl;
}

void Game::updatePipes(float delta)
{

    for (auto &pipe: m_pipes)
    {
        pipe.update(delta);
        
        if (pipe.collidingWithPlayer(m_player))
        {
            std::cout << "Pipe collided with the player. Game over!\n";
            std::cout << "Final score (how many pipes reached the end of the screen): " << m_score << std::endl;
            m_currentState = GameState::QUIT;
        }

        if (pipe.passedScreen())
        {
            pipe.resetPosition();

            int new_pipe_height = generatePipeLocation();
            pipe.setHeight(new_pipe_height);

            m_score ++;
        }

        renderEntity(pipe);
    }
}

int Game::generatePipeLocation()
{
    std::random_device dev;
    std::mt19937 random_gen(dev());
    std::uniform_int_distribution<std::mt19937::result_type> height_generator(10, 118);

    return height_generator(random_gen);
}