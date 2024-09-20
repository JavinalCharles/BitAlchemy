#include <BA/Resources/Wrapper/Texture.hpp>

namespace ba{
namespace Resource {

Texture::Texture() = default;

Texture::Texture(SDL_Renderer* renderer, const std::string& file) {
    this->createFromFile(renderer, file);
    if (m_texture != nullptr) {
        m_refCount = new int(1);
    }
}

Texture::Texture(SDL_Renderer* renderer, int width, int height) {
    this->createBlank(renderer, width, height);
    if (m_texture != nullptr) {
        m_refCount = new int(1);
    }
}

Texture::Texture(SDL_Renderer* renderer, const Vector2i& dimension) {
    this->createBlank(renderer, dimension);
    if (m_texture != nullptr) {
        m_refCount = new int(1);
    }
}

Texture::Texture(const Texture& other) :
    m_texture(other.m_texture),
    m_refCount(other.m_refCount)
{
    if (m_refCount != nullptr) {
        (*m_refCount)++;
    }
}

Texture::Texture(Texture&& other) :
    m_texture(other.m_texture),
    m_refCount(other.m_refCount)
{
    other.m_texture = nullptr;
    other.m_refCount = nullptr;
}

Texture::~Texture() {
    reset();
}

Texture& Texture::operator=(const Texture& other) {
    if (this != &other) {
        reset(); // resets current object.
        m_texture = other.m_texture;
        m_refCount = other.m_refCount;
        (*m_refCount)++;
    }
    return *this;
}

Texture& Texture::operator=(Texture&& rvalue) {
    if (this != &rvalue) {
        reset();
        m_texture = rvalue.m_texture;
        m_refCount = rvalue.m_refCount;
        rvalue.m_texture = nullptr;
        rvalue.m_refCount = nullptr;
    }
    return *this;
}

SDL_Texture* Texture::createFromFile(SDL_Renderer* renderer, const std::string& file) {
    if (m_texture != nullptr || renderer == nullptr) {
        return m_texture;
    }

    m_texture = IMG_LoadTexture(renderer, file.c_str());
    if (m_texture == nullptr) {
        std::cerr << "In ba::Resource::Texture::createFromFile(). Texture cannot be created from file: " << file << std::endl;
        std::cerr << "\tIMG_GetError() returns: " << IMG_GetError() << std::endl;
    }

    return m_texture;
}

SDL_Texture* Texture::createBlank(SDL_Renderer* renderer, int width, int height) {
    if (m_texture != nullptr || renderer == nullptr) {
        return m_texture;
    }

    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
    if (m_texture == nullptr) {
        std::cerr << "In ba::Resource::Texture::createBlank(). unable to create Texture.\n"
        << "\tSDL_GetError() returns: " << SDL_GetError() << std::endl;
    }

    return m_texture;
}

SDL_Texture* Texture::createBlank(SDL_Renderer* renderer, const Vector2i& dimension) {
    return createBlank(renderer, dimension.x, dimension.y);
}

void Texture::reset() {
    if (m_refCount != nullptr && --(*m_refCount) < 1) {
        SDL_DestroyTexture(m_texture);
        delete m_refCount;
    }
    m_texture = nullptr;
    m_refCount = nullptr;
} 


}// Resources
}// namespace ba