#pragma
#include <filesystem>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string_view>

#include "Texture.h"

class Game {
public:
  Game();
  ~Game();

  bool LoadMedia();

  bool Init();
  void Run();
  void Shutdown();

private:
  static constexpr Uint32 WINDOW_FLAGS =
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
  static constexpr int WINDOW_WIDTH = 640;
  static constexpr int WINDOW_HEIGHT = 480;
  static constexpr std::string_view WINDOW_TITLE = "cpp-game-template";

  bool m_windowShouldClose;

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

  Texture m_upTexture;
  Texture m_downTexture;
  Texture m_leftTexture;
  Texture m_rightTexture;
  Texture m_defaultTexture;

  std::filesystem::path m_basePath;
  std::string_view m_texturePath = "Resources/Textures/";
};
