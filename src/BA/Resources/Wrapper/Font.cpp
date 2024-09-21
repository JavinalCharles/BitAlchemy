#include <BA/Resources/Wrapper/Font.hpp>

namespace ba {
namespace Resources {

Font::Font() = default;

Font::Font(const std::string& file, int ptsize) {
	openFont(file, ptsize);
}

Font::Font(const std::string& file, int ptsize, long index) {
	openFont(file, ptsize, index);
}

Font::Font(const std::string& file, int ptsize, const Vector2u& dpi) {
	openFont(file, ptsize, dpi);
}

Font::Font(const std::string& file, int ptsize, long index, const Vector2u& dpi) {
	openFont(file, ptsize, index, dpi);
}

Font::Font(const Font& other) :
	m_font(other.m_font),
	m_refCount(other.m_refCount)
{
	if (m_refCount != nullptr) {
		(*m_refCount)++;
	}
}

Font::Font(Font&& other) :
	m_font(other.m_font),
	m_refCount(other.m_refCount)
{
	other.m_font = nullptr;
	other.m_refCount = nullptr;
}

Font::~Font() {
	reset();
}

Font& Font::operator=(const Font& rhs) {
	if (this != &rhs) {
		reset();
		m_font = rhs.m_font;
		m_refCount = rhs.m_refCount;
		if (m_refCount != nullptr)
			(*m_refCount)++;
	}
	return *this;
}

Font& Font::operator=(Font&& rhs) {
	if (this != &rhs) {
		reset();
		m_font = rhs.m_font;
		m_refCount = rhs.m_refCount;
		rhs.m_font = nullptr;
		rhs.m_refCount = nullptr;
	}
	return *this;
}

TTF_Font* Font::openFont(const std::string& file, int ptsize) {
	if (m_font != nullptr) {
		return m_font;
	}
	m_font = TTF_OpenFont(file.c_str(), ptsize);

	initializeRefCount();
}

TTF_Font* Font::openFont(const std::string& file, int ptsize, long index) {
	if (m_font != nullptr) {
		return m_font;
	}
	m_font = TTF_OpenFontIndex(file.c_str(), ptsize, index);

	initializeRefCount();
}

TTF_Font* Font::openFont(const std::string& file, int ptsize, const Vector2u& dpi) {
	if (m_font != nullptr) {
		return m_font;
	}
	m_font = TTF_OpenFontDPI(file.c_str(), ptsize, dpi.x, dpi.y);

	initializeRefCount();
}

TTF_Font* Font::openFont(const std::string& file, int ptsize, long index, const Vector2u& dpi) {
	if (m_font != nullptr) {
		return m_font;
	}
	m_font = TTF_OpenFontIndexDPI(file.c_str(), ptsize, index, dpi.x, dpi.y);

	initializeRefCount();

}

void Font::initializeRefCount() {
	if (m_font == nullptr) {
		std::cerr << "In ba::Resource::Font::openFont(). Unable to open font.\n";
		std::cerr << "TTF_GetError() returns: " << TTF_GetError() << std::endl;
		return;
	}
	m_refCount = new int(1);
}

void Font::reset() {
	if (m_refCount != nullptr && --(*m_refCount) < 1) {
		TTF_CloseFont(m_font);
		delete m_refCount;
	}
	m_font = nullptr;
	m_refCount = nullptr;
}


} // namespace Resource
} // namespace ba