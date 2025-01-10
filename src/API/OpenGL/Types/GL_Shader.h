#pragma once
#include "IMCommon/RendererCommon.h"
#include <string>


struct Shader {
public:
	void Load(std::string vertexPath, std::string fragmentPath);

	
	void Bind() const;
private:
	int m_ID;

};