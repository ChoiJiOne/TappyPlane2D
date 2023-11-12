#include "Shader.h"

#include "AssertionMacro.h"
#include "FileManager.h"

#include <glad/glad.h>

char Shader::buffer_[MAX_BUFFER_SIZE];

Shader::~Shader()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Shader::Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid)
{
	ASSERT(!bIsInitialized_, "already initialize shader resource...");

	if (bCheckValid)
	{
		ASSERT(CheckValidShaderFile(vsPath, fsPath), "invalid shader file : \'%s\' and \'%s\'", vsPath.c_str(), fsPath.c_str());
	}

	std::string vsSource = FileManager::Get().ReadTextFileToString(vsPath);
	std::string fsSource = FileManager::Get().ReadTextFileToString(fsPath);

	uint32_t vsID = CreateAndCompileShader(EType::Vertex, vsSource);
	ASSERT(vsID != 0, "failed to create and compile vertex shader : %s", vsPath.c_str());

	uint32_t fsID = CreateAndCompileShader(EType::Fragment, fsSource);
	ASSERT(fsID != 0, "failed to create and compile fragment shader : %s", fsPath.c_str());

	programID_ = glCreateProgram();
	glAttachShader(programID_, vsID);
	glAttachShader(programID_, fsID);
	glLinkProgram(programID_);

	int32_t success;
	glGetProgramiv(programID_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID_, MAX_BUFFER_SIZE, nullptr, buffer_);
		ASSERT(false, "failed to link shader program : %s", buffer_);
	}

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	bIsInitialized_ = true;
}

void Shader::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	if (programID_ != 0)
	{
		glDeleteProgram(programID_);
	}

	bIsInitialized_ = false;
}

void Shader::Bind()
{
	glUseProgram(programID_);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetBoolParameter(const std::string& name, bool value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform1i(location, static_cast<int32_t>(value));
}

void Shader::SetIntParameter(const std::string& name, int32_t value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform1i(location, static_cast<int32_t>(value));
}

void Shader::SetFloatParameter(const std::string& name, float value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform1f(location, value);
}

void Shader::SetVector2fParameter(const std::string& name, const Vector2f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	glUniform2fv(location, 1, valuePtr);
}

void Shader::SetVector2fParameter(const std::string& name, float x, float y)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform2f(location, x, y);
}

void Shader::SetVector2iParameter(const std::string& name, const Vector2i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	glUniform2iv(location, 1, valuePtr);
}

void Shader::SetVector2iParameter(const std::string& name, int32_t x, int32_t y)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform2i(location, x, y);
}

void Shader::SetVector3fParameter(const std::string& name, const Vector3f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	glUniform3fv(location, 1, valuePtr);
}

void Shader::SetVector3fParameter(const std::string& name, float x, float y, float z)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform3f(location, x, y, z);
}

void Shader::SetVector3iParameter(const std::string& name, const Vector3i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	glUniform3iv(location, 1, valuePtr);
}

void Shader::SetVector3iParameter(const std::string& name, int32_t x, int32_t y, int32_t z)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform3i(location, x, y, z);
}

void Shader::SetVector4fParameter(const std::string& name, const Vector4f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	glUniform4fv(location, 1, valuePtr);
}

void Shader::SetVector4fParameter(const std::string& name, float x, float y, float z, float w)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform4f(location, x, y, z, w);
}

void Shader::SetVector4iParameter(const std::string& name, const Vector4i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	glUniform4iv(location, 1, valuePtr);
}

void Shader::SetVector4iParameter(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	glUniform4i(location, x, y, z, w);
}

bool Shader::CheckValidShaderFile(const std::string& vsPath, const std::string& fsPath)
{
	FileManager& fileManager = FileManager::Get();

	// 파일 여부 및 유효성 검사
	if (!fileManager.IsValidPath(vsPath) || !fileManager.IsFilePath(vsPath))
	{
		return false;
	}

	if (!fileManager.IsValidPath(fsPath) || !fileManager.IsFilePath(fsPath))
	{
		return false;
	}

	// 파일 확장자 검사
	std::string vsExtension = fileManager.GetFileExtension(vsPath);
	if (vsExtension != "vert" && vsExtension != "vs" && vsExtension != "glsl")
	{
		return false;
	}

	std::string fsExtension = fileManager.GetFileExtension(fsPath);
	if (fsExtension != "frag" && fsExtension != "fs" && fsExtension != "glsl")
	{
		return false;
	}

	return true;
}

uint32_t Shader::CreateAndCompileShader(const EType& type, const std::string& source)
{
	uint32_t shaderType = 0;
	switch (type)
	{
	case EType::Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;

	case EType::Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;

	default:
		ASSERT(false, "undefined shader type...");
		break;
	}

	const char* sourcePtr = source.c_str();
	uint32_t shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &sourcePtr, nullptr);
	glCompileShader(shaderID);

	int32_t success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, MAX_BUFFER_SIZE, nullptr, buffer_);
		ASSERT(false, "failed to compile shader : %s", buffer_);
	}

	return shaderID;
}

int32_t Shader::GetUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(programID_, uniformName.c_str());
}