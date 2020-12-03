#pragma once

#include <glad/glad.h>
#include "../Texture.h"

class WaterFrameBuffer {
	static const int reflectionWidth, reflectionHeight;
	static const int refractionWidth, refractionHeight;

	GLuint reflectionFrameBuffer;
	GLuint reflectionDepthBuffer;
	
	GLuint refractionFrameBuffer;
	GLuint refractionDepthTexture;

	GLuint reflectionTexture;
	GLuint refractionTexture;

	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);
	void bindFrameBuffer(GLuint buffer, int width, int height);

public:
	WaterFrameBuffer();
	~WaterFrameBuffer();

	void clear();
	void bindReflectionBuffer();
	void bindRefractionBuffer();
	void unbindBuffer();
	GLuint getReflectionTexture();
	GLuint getRefractionTexture();
	GLuint getRefractionDepthTexture();
};