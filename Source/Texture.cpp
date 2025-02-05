#include "Texture.h"
#include <SDL3_image/SDL_image.h>
#include <cstdio>

Texture::Texture()
    : m_renderer(nullptr), m_texture(nullptr), m_width(0), m_height(0) {}

Texture::~Texture() { Destroy(); }

bool Texture::LoadFromFile(const std::string_view &path) {
  Destroy();
  auto srf = IMG_Load(path.data());
  if (srf == nullptr) {
    printf("Unable to load image %s\n", path.data());
    return false;
  }

  m_texture = SDL_CreateTextureFromSurface(m_renderer, srf);
  if (m_texture == nullptr) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.data(),
           SDL_GetError());
    SDL_DestroySurface(srf);
    return false;
  }

  m_width = srf->w;
  m_height = srf->h;
  SDL_DestroySurface(srf);

  return m_texture != nullptr;
}

void Texture::SetRenderer(SDL_Renderer *renderer) { m_renderer = renderer; }

void Texture::Draw(float x, float y) const {
  SDL_FRect dstRect = {x, y, static_cast<float>(m_width),
                       static_cast<float>(m_height)};
  SDL_RenderTexture(m_renderer, m_texture, nullptr, &dstRect);
}

void Texture::Destroy() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }
}

int Texture::GetWidth() const { return m_width; }

int Texture::GetHeight() const { return m_height; }
