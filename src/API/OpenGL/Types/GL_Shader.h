#pragma once
#include "IMCommon/RendererCommon.h"
#include <string>


struct Shader {
public:
	void Load(std::string vertexPath, std::string fragmentPath);

	
	void Bind() const;

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;
private:
	int m_ID;

};