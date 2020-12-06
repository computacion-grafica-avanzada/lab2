#pragma once

#include <string>
#include <glad/glad.h>
#include "FreeImage.h"

class Texture {
private:
	std::string filename;
	GLuint textureID;
	GLsizei width, height;
	bool transparency;

public:
	Texture(int width, int height);
	Texture(const std::string& filename);
	~Texture();

	bool hasTransparency();

	void bind(int index = 0);
	void unbind();
};