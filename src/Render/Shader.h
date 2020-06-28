#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <unordered_map>
#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include "../LinearMath/Vector3.h"
#include "../LinearMath/Matrix4x4.h"
#include "../Utils/Log.h"

class Shader
{
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mProgram;

	std::unordered_map<std::string, GLint> mUniformLocations;
	std::unordered_map<std::string, GLint> mAttributeLocations;

	template <int N> GLuint compile(GLuint type, const char* const(&source)[N]) const;
public:
	template <int N, int M> Shader(const char* const(&vs)[N], const char* const(&fs)[M]);
	virtual ~Shader();

	void run() const;
	void link() const;
	void stop() const;

	GLint getUniformLocation(const std::string& param);
	GLint getAttributeLocation(const std::string& param);

	void bindAttribute(GLuint index, const char *name) const;
	void setUniform1i(int location, int number) const;
	// void set(const std::string& param, const ITexture* texture);
	void set(const std::string& param, const Vector3& vector);
	void set(const std::string& param, float value);
	void set(const std::string& param, int value);
	void set(const std::string& param, float v1, float v2);
	void set(const std::string& param, const Matrix4x4& matrix);
	void set4f(const std::string& param, float* value);
};

//-----------------------------------------------------------------------------

template <int N> GLuint Shader::compile(GLuint type, const char* const(&source)[N]) const {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, N, source, nullptr);
	glCompileShader(shader);
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string log(length, ' ');
		glGetShaderInfoLog(shader, length, &length, &log[0]);
		glDeleteShader(shader); // Don't leak the shader.
		std::string msg { "Shader not compiled: " + log };
		Log::error(msg.c_str());

		for (int i = 0; i < N; i++) {
			Log::debug(source[i]);
		}
		emscripten_force_exit(EXIT_FAILURE);
	}
	return shader;
}


template <int N, int M> Shader::Shader(const char* const(&vs)[N], const char* const(&fs)[M]) {
	mVertexShader = compile(GL_VERTEX_SHADER, vs);
	mFragmentShader = compile(GL_FRAGMENT_SHADER, fs);
	mProgram = glCreateProgram();
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);
	link();
}

#endif