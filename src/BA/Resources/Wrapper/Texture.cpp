#include <BA/Resources/Wrapper/Texture.hpp>

namespace ba{
namespace Resources {

Texture::Texture() = default;

Texture::Texture(const std::string& file) {
	this->create(file);
}

Texture::Texture(int width, int height) {
	this->create(width, height);
}

Texture::Texture(const Vector2i& dimension) {
	this->create(dimension);
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
		if (m_refCount != nullptr)
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

SDL_Texture* Texture::create(const std::string& file) {
	if (m_texture != nullptr || globalRenderer == nullptr) {
		return m_texture;
	}

	m_texture = IMG_LoadTexture(globalRenderer, file.c_str());

	if (m_texture != nullptr) {
		m_refCount = new int(1);
		std::cout << "Texture created from file: " << file.c_str() << std::endl;
		std::cout << "\tTexture memory: " << m_texture << std::endl;
	}
	else {
		std::cerr << "In ba::Resource::Texture::createFromFile(). Texture cannot be created from file: " << file << std::endl;
		std::cerr << "\tIMG_GetError() returns: " << IMG_GetError() << std::endl;
	}

	return m_texture;
}

SDL_Texture* Texture::create(int width, int height) {
	if (m_texture != nullptr || globalRenderer == nullptr) {
		return m_texture;
	}

	m_texture = SDL_CreateTexture(globalRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
	if (m_texture != nullptr) {
		m_refCount = new int(1);
	}
	else {
		std::cerr << "In ba::Resource::Texture::create(). unable to create Texture.\n";
		std::cerr << "\tSDL_GetError() returns: " << SDL_GetError() << std::endl;
	}

	return m_texture;
}

SDL_Texture* Texture::create(const Vector2i& dimension) {
	return create(dimension.x, dimension.y);
}

void Texture::reset() {
	// std::cout << "Texture reset for " << m_texture << "; Count " << ((m_refCount != nullptr) ? *m_refCount : 0) << " Remaining." << std::endl;
	if (m_refCount != nullptr && --(*m_refCount) < 1) {
		SDL_DestroyTexture(m_texture);
		delete m_refCount;
	}
	m_texture = nullptr;
	m_refCount = nullptr;
} 

}// Resources
}// namespace ba