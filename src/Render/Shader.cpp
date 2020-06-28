#include "Shader.h"

Shader::~Shader() {
	Log::debug("Deleting shader %d", mProgram);
	glDeleteProgram(mProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
}


void Shader::run() const { 
	glUseProgram(mProgram); 
}


void Shader::stop() const { 
	glUseProgram(0); 
}


void Shader::link() const {
	glLinkProgram(mProgram);
	GLint isLinked = 0;
	glGetProgramiv(mProgram, GL_LINK_STATUS, (int*) &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);

		//The maxLength includes the NULL character
		std::string log(length, ' ');
		glGetProgramInfoLog(mProgram, length, &length, &log[0]);
		Log::error("Shader link error: %s", log.c_str());

		this->~Shader();
		emscripten_force_exit(EXIT_FAILURE);
	}
}


void Shader::bindAttribute(GLuint index, const char *name) const {
	glBindAttribLocation(mProgram, index, name);
}


GLint Shader::getUniformLocation(const std::string& param) {
	// if location is unknown, add it to the cache
	if (mUniformLocations.find(param) == mUniformLocations.end()) {
		const GLint location = glGetUniformLocation(mProgram, param.c_str());
		mUniformLocations[param] = location;
		if (location == -1)
			Log::info("Uniform location not found for %s", param.c_str());
	}
	return mUniformLocations[param];
}


GLint Shader::getAttributeLocation(const std::string& param) {
	// if location is unknown, add it to the cache
	if (mAttributeLocations.find(param) == mAttributeLocations.end()) {
		const GLint location = glGetAttribLocation(mProgram, param.c_str());
		mAttributeLocations[param] = location;
		if (location == -1)
			Log::info("Attribute location not found for %s", param.c_str());
	}
	return mAttributeLocations[param];
}


void Shader::setUniform1i(int location, int number) const {
	glUniform1i(location, number);
}

/*
void Shader::set(const std::string& param, const ITexture* texture) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		texture->bind();
		setUniform1i(location, texture->getSlot());
	}
}
*/

void Shader::set(const std::string& param, const Vector3& vector) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniform3f(location, vector.x(), vector.y(), vector.z());
	}
}


void Shader::set(const std::string& param, float value) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniform1f(location, value);
	}
}


void Shader::set(const std::string& param, int value) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniform1i(location, value);
	}
}


void Shader::set(const std::string& param, float v1, float v2) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniform2f(location, v1, v2);
	}
}


void Shader::set(const std::string &param, const Matrix4x4 &matrix) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniformMatrix4fv(location, 1 /*only setting 1 matrix*/, false /*transpose?*/, matrix.raw());
	}
}


void Shader::set4f(const std::string& param, float* value) {
	const GLint location = getUniformLocation(param);
	if (location >= 0) {
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}
}
