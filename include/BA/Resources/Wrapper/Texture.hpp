#pragma once

#include <iostream>
#include <string>

#include <BA/Globals.hpp>
#include <BA/Utilities/Vector2.hpp>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

namespace ba {
namespace Resources {

    /**
     * @brief A wrappers for SDL_Texture*
     * 
     * This class acts as a wrapper for SDL_Texture and provides 
     * an OOP means of managing the stored object, and also acts
     * as its own smart pointer that keep tracks of how many objects
     * share ownership to the same pointer and 
     * automatically calls SDL_DestroyTexture() once one of the 
     * following happens:
     *  - The last remaining Texture owning the pointer is destroyed.
     *  - The last remaining Texture owning the pointer is reassigned via means of operator= or reset().
     * 
     */
    class Texture {
    public:
        ///@{
        /**
         * Constructs the texture.
         * 
         * Initializes this object and for constructors with
         * parameters, calls the relevant create() method.
         * 
         * @param file the path to the texture file, can be absolute path or relative to the current working directory.
         * @param width The desired width for the texture.
         * @param height The desired height for the texture.
         * @param dimension The desired dimension of the texture in the format: {width, height}.
         * @param other The texture to be constructed.
         * @param rvalue The texture to be moved.
         */
        Texture();
        Texture(const std::string& file);
        Texture(int width, int height);
        Texture(const Vector2i& dimesnsion);
        Texture(const Texture& other);
        Texture(Texture&& rvalue) noexcept;
        ///@}

        ~Texture();

        Texture& operator=(const Texture& rhs);
        Texture& operator=(Texture&& rvalue) noexcept;

        ///@{
        /**
         * Creates the texture
         * 
         * Attempts to create a texture with the given parameters and returns
         * it. If a texture is already created however, then this functions
         * simply returns that texture, ignoring the given parameters.
         * 
         * @param renderer The renderer used to create the texture.
         * @param file the path to the texture file, can be absolute path or relative to the current working directory.
         * @param width The desired width for the texture.
         * @param height The desired height for the texture.
         * @param dimension The desired dimension of the texture in the format: {width, height}.
         * 
         * @returns A pointer to
         * 
         * @note Textures created without the file parameter will be
         * created with SDL_TEXTUREACCESS_TARGET and 
         * SDL_PIXELFORMAT_RGBA32 arguments.
         * 
         * @warning Do not use SDL_DestroyTexture() on the given pointer.
         * Use the clear() method instead.
         */
        SDL_Texture* create(const std::string& file);
        SDL_Texture* create(int width, int height);
        SDL_Texture* create(const Vector2i& dimension);
        ///@}

        /**
         * @brief gets the stored raw pointer to the texture.
         * 
         * @return constexpr SDL_Texture* 
         */
        constexpr SDL_Texture* get() const;

        /**
         * @brief Destroy the texture and reset the pointer.
         */
        void reset();

    private:
        SDL_Texture* m_texture = nullptr;
        int* m_refCount = nullptr;
    }; // class Texture

    constexpr SDL_Texture* Texture::get() const {
        return m_texture;
    }
} // namespace Resource
} // namespace ba