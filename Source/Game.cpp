#include "Game.h"
#include <cstdio>

Game::Game()
    : m_window(nullptr, SDL_DestroyWindow),
      m_renderer(nullptr, SDL_DestroyRenderer), m_basePath(SDL_GetBasePath()),
      m_upTexture(), m_downTexture(), m_leftTexture(), m_rightTexture() {}

Game::~Game() { Shutdown(); }

bool Game::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return false;
  };

  m_window.reset(SDL_CreateWindow(WINDOW_TITLE.data(), WINDOW_WIDTH,
                                  WINDOW_HEIGHT, WINDOW_FLAGS));
  if (m_window == nullptr) {
    printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
    return false;
  };

  m_renderer.reset(SDL_CreateRenderer(m_window.get(), 0));
  if (m_renderer == nullptr) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    return false;
  };

  SDL_SetRenderVSync(m_renderer.get(), 1);

  m_upTexture.SetRenderer(m_renderer.get());
  m_downTexture.SetRenderer(m_renderer.get());
  m_leftTexture.SetRenderer(m_renderer.get());
  m_rightTexture.SetRenderer(m_renderer.get());
  m_defaultTexture.SetRenderer(m_renderer.get());

  return true;
}

void Game::Shutdown() { SDL_Quit(); }

bool Game::LoadMedia() {
  bool success = true;

  auto path = m_basePath / m_texturePath;
  if (success &= m_upTexture.LoadFromFile(std::string(path) + "up.png")) {
    SDL_Log("Failed to load up texture");
  }

  if (success &= m_downTexture.LoadFromFile(std::string(path) + "down.png")) {
    SDL_Log("Failed to load down texture");
  }

  if (success &= m_leftTexture.LoadFromFile(std::string(path) + "left.png")) {
    SDL_Log("Failed to load left texture");
  }

  if (success &= m_rightTexture.LoadFromFile(std::string(path) + "right.png")) {
    SDL_Log("Failed to load right texture");
  }

  if (success &=
      m_defaultTexture.LoadFromFile(std::string(path) + "hello_world.bmp")) {
    SDL_Log("Failed to load default texture");
  }

  return success;
}

void Game::Run() {
  SDL_Event event{};
  Texture *currentTexture = &m_defaultTexture;

  SDL_Color bgColor = {0xFF, 0xFF, 0xFF, 0xFF};
  SDL_ShowWindow(m_window.get());

  while (!m_windowShouldClose) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        m_windowShouldClose = true;
        break;
      case SDL_EVENT_KEY_DOWN:
        switch (event.key.key) {
        case SDLK_UP:
          currentTexture = &m_upTexture;
          break;
        case SDLK_DOWN:
          currentTexture = &m_downTexture;
          break;
        case SDLK_LEFT:
          currentTexture = &m_leftTexture;
          break;
        case SDLK_RIGHT:
          currentTexture = &m_rightTexture;
          break;
        default:
          currentTexture = &m_defaultTexture;
          break;
        }
        break;
      }
    }

    SDL_SetRenderDrawColor(m_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer.get());
    currentTexture->Draw(
        WINDOW_WIDTH * 0.5f - currentTexture->GetWidth() * 0.5f,
        WINDOW_HEIGHT * 0.5f - currentTexture->GetHeight() * 0.5f);

    SDL_RenderPresent(m_renderer.get());
  }
}
