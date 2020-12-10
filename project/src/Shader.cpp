#include "Shader.h"

// loadFile - loads text file into char* fname
// allocates memory - so need to delete after use
const char* loadFile(const char* fname)
{
	int size;
	char* memblock = NULL;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		memblock = new char[size + 1]; // create buffer with space for null char
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		memblock[size] = 0;
		std::cout << "file " << fname << " loaded" << std::endl;
	}
	else
	{
		std::cout << "Unable to open file " << fname << std::endl;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
	}
	return memblock;
}

// printShaderError
// Display (hopefully) useful error messages if shader fails to compile or link
void Shader::printShaderError(GLint shader)
{
	int maxLength = 0;
	int logLength = 0;
	GLchar* logMessage;

	// Find out how long the error message is
	if (glIsShader(shader))
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	else
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	if (maxLength > 0) // If message has length > 0
	{
		logMessage = new GLchar[maxLength];
		if (glIsShader(shader))
			glGetProgramInfoLog(shader, maxLength, &logLength, logMessage);
		else
			glGetShaderInfoLog(shader, maxLength, &logLength, logMessage);
		std::cout << "Shader Info Log:" << std::endl << logMessage << std::endl;
		delete[] logMessage;
	}
}

GLuint Shader::Compile(GLuint type, const char* source) {
	GLuint shader = glCreateShader(type);			// create shader handle
	glShaderSource(shader, 1, &source, NULL);		// send shader source to GPU
	glCompileShader(shader);						// compile shader

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		std::cout << type << " shader not compiled." << std::endl;
		printShaderError(shader);
	}

	return shader;
}

void Shader::CompileShaders(const char* vertexSource, const char* fragmentSource) {
	vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
	fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

	shaderProgram = glCreateProgram();				// create the handle for the shader program
	glAttachShader(shaderProgram, vertexShader);	// attach vertex shader to program
	glAttachShader(shaderProgram, fragmentShader);	// attach fragment shader to program
	glLinkProgram(shaderProgram);					// link the shader program and test for errors

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "Program not linked." << std::endl;
		printShaderError(shaderProgram);
	}
	else {
		std::cout << "Program linked." << std::endl;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	const char* vertexSource = loadFile(vertexFile);
	const char* fragmentSource = loadFile(fragmentFile);
	CompileShaders(vertexSource, fragmentSource);
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

void Shader::bind() {
	glUseProgram(shaderProgram);
}
void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setUniformMatrix4fv(const char* name, const glm::mat4& matrix) {
	GLint matrixID = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform1f(const char* name, const float& value) {
	GLint floatID = glGetUniformLocation(shaderProgram, name);
	glUniform1f(floatID, value);
}
void Shader::setUniform2f(const char* name, const glm::vec2& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform2f(vectorID, vector.x, vector.y);
}
void Shader::setUniform3f(const char* name, const glm::vec3& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform3f(vectorID, vector.x, vector.y, vector.z);
}
void Shader::setUniform4f(const char* name, const glm::vec4& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform4f(vectorID, vector.x, vector.y, vector.z, vector.w);
}
void Shader::setUniform1i(const char* name, const int& value) {
	GLint intID = glGetUniformLocation(shaderProgram, name);
	glUniform1i(intID, value);
}