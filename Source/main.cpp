#include <cstdlib>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <string_view>

constexpr Uint32 WINDOW_FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 320;
constexpr std::string_view WINDOW_TITLE = "cpp-game-template";

int main(int argc, char *argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  };

  SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE.data(), WINDOW_WIDTH,
                                        WINDOW_HEIGHT, WINDOW_FLAGS);
  if (window == nullptr) {
    printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  SDL_SetRenderVSync(renderer, 1);
  if (renderer == nullptr) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  SDL_Event event;

  bool shouldClose = false;
  SDL_ShowWindow(window);
  while (!shouldClose) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      switch (event.type) {
      case SDL_EVENT_QUIT:
        shouldClose = true;
        break;
      default:
        break;
      }
    }

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Test");
    ImGui::Text("Hello from another window!");
    ImGui::End();

    ImGui::Render();
    SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y,
                                clear_color.z, clear_color.w);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }

  // Cleanup
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
