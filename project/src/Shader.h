#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

class Shader {
private:
	GLuint vertexShader, fragmentShader, shaderProgram;
	GLuint Compile(GLuint type, const char* source);
	void CompileShaders(const char* vertexSource, const char* fragmentSource);

	void printShaderError(GLint shader);

public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void bind();
	void unbind();
	void setUniformMatrix4fv(const char* name, const glm::mat4& matrix);
	void setUniform1f(const char* name, const float& value);
	void setUniform2f(const char* name, const glm::vec2& vector);
	void setUniform3f(const char* name, const glm::vec3& vector);
	void setUniform4f(const char* name, const glm::vec4& vector);
	void setUniform1i(const char* name, const int& value);
};