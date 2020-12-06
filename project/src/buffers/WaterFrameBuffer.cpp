#include "WaterFrameBuffer.h"

const int WaterFrameBuffer::reflectionWidth = 1024;
const int WaterFrameBuffer::reflectionHeight = 768;
const int WaterFrameBuffer::refractionWidth = 1280;
const int WaterFrameBuffer::refractionHeight = 720;

WaterFrameBuffer::WaterFrameBuffer() {
	reflectionFrameBuffer = createFrameBuffer();
	reflectionTexture = createTextureAttachment(reflectionWidth, reflectionHeight);
	reflectionDepthBuffer = createDepthBufferAttachment(reflectionWidth, reflectionHeight);
	unbindBuffer();

	refractionFrameBuffer = createFrameBuffer();
	refractionTexture = createTextureAttachment(refractionWidth, refractionHeight);
	refractionDepthTexture = createDepthTextureAttachment(refractionWidth, refractionHeight);
	unbindBuffer();
}

GLuint WaterFrameBuffer::createFrameBuffer() {
	GLuint frameBufferId;
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBufferId;
}

GLuint WaterFrameBuffer::createTextureAttachment(int width, int height) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId, 0);
	return textureId;
}

GLuint WaterFrameBuffer::createDepthTextureAttachment(int width, int height) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
	return textureId;
}

GLuint WaterFrameBuffer::createDepthBufferAttachment(int width, int height) {
	GLuint depthBufferId;
	glGenRenderbuffers(1, &depthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
	return depthBufferId;
}

void WaterFrameBuffer::bindFrameBuffer(GLuint bufferId, int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferId);
	glViewport(0, 0, width, height);
}

void WaterFrameBuffer::bindReflectionBuffer() {
	bindFrameBuffer(reflectionFrameBuffer, reflectionWidth, reflectionHeight);
}

void WaterFrameBuffer::bindRefractionBuffer() {
	bindFrameBuffer(refractionFrameBuffer, refractionWidth, refractionHeight);
}

void WaterFrameBuffer::unbindBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 800, 800); // TODO change to dynamic width and height
}

WaterFrameBuffer::~WaterFrameBuffer() {
	glDeleteFramebuffers(1, &reflectionFrameBuffer);
	glDeleteFramebuffers(1, &refractionFrameBuffer);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteTextures(1, &refractionDepthTexture);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteTextures(1, &refractionTexture);
}

GLuint WaterFrameBuffer::getReflectionTexture() {
	return reflectionTexture;
}

GLuint WaterFrameBuffer::getRefractionTexture() {
	return refractionTexture;
}

GLuint WaterFrameBuffer::getRefractionDepthTexture() {
	return refractionDepthTexture;
}
