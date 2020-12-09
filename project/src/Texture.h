#pragma once

#include <string>
#include <glad/glad.h>
#include <iostream>
#include "FreeImage.h"
#include "SDL_ttf.h"

class Texture {
private:
	std::string filename;
	GLuint textureID;
	GLsizei width, height;
	bool transparency;

public:
	Texture();
	Texture(int width, int height);
	Texture(const std::string& filename);
	~Texture();

	bool hasTransparency();

	void bind(int index = 0);
	void unbind();

	void setText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize);
};