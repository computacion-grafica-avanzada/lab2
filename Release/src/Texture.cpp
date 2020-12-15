#include "Texture.h"

BYTE* loadImage(const char* filename, GLsizei &width, GLsizei &height) {
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);
    FIBITMAP* bitmap = FreeImage_Load(fif, filename);

    if (!bitmap) {
        fprintf(stderr, "Could not get image bitmap.\n");
        return NULL;
    }
    
    int bitsPerPixel = FreeImage_GetBPP(bitmap);
    if (bitsPerPixel != 32) {
        FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(bitmap);
        bitmap = bitmap32;
    }


    width = FreeImage_GetWidth(bitmap);
    height = FreeImage_GetHeight(bitmap);
    BYTE* pixels = FreeImage_GetBits(bitmap);

    if ((pixels == 0) || (width == 0) || (height == 0)) {
        return NULL;
    }
    return pixels;
}

Texture::Texture(const std::string& filename, bool hasTransparency) : filename(filename) {
    BYTE* pixels = loadImage(filename.c_str(), width, height);
    this->transparency = hasTransparency;

    glGenTextures(1, &textureID);
    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unbind();
}

Texture::Texture(int width, int height) {
    this->width = width;
    this->height = height;
    this->transparency = false;

    glGenTextures(1, &(this->textureID));
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->textureID, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

bool Texture::hasTransparency() {
    return transparency;
}

void Texture::bind(int index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}