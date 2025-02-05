#pragma
#include <string_view>

#include <SDL3/SDL.h>

class Texture {
public:
  Texture();
  ~Texture();

  bool LoadFromFile(const std::string_view &path);
  void SetRenderer(SDL_Renderer *renderer);

  void Draw(float x, float y) const;
  void Destroy();

  [[nodiscard]] int GetWidth() const;
  [[nodiscard]] int GetHeight() const;

private:
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  int m_width;
  int m_height;
};
