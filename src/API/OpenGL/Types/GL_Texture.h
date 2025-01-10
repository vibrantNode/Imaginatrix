#pragma once
#include <string>
#include <glad/glad.h>



struct OGLTexture {
	OGLTexture() = default;
	explicit OGLTexture(const std::string& filepath) : m_fullPath(filepath) {}

	GLuint GetID();

	void Bind(unsigned int slot);
	bool Load(const std::string filepath);

	const std::string& GetFilePath() const { return m_fullPath; }

private:
	GLuint m_ID;

	std::string m_filename;
	std::string m_fullPath;
};