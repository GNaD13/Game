#include "Texture.hpp"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

Texture::Texture()
    : mWidth(0)
    , mHeight(0)
    , mTextureID(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
    int channels = 0;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channels, 0);

    if(data == nullptr)
    {
        SDL_Log("Failed to load image %s: ", fileName.c_str());
        return false;
    }

    int format = GL_RGB;
    int internalFormat = GL_RGB8;
    if(channels == 4)
    {
        format = GL_RGBA;
        internalFormat = GL_RGBA8;
    }

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}
