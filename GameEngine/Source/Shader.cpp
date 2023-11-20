#include "Shader.h"

#include "AssertionMacro.h"
#include "FileManager.h"
#include "GLAssertionMacro.h"

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
	ASSERT(programID_ != 0, "failed to create shader program...");

	GL_ASSERT(glAttachShader(programID_, vsID), "failed to attach vertex shader in shader program...");
	GL_ASSERT(glAttachShader(programID_, fsID), "failed to attach fragment shader in shader program...");
	GL_ASSERT(glLinkProgram(programID_), "failed to link shader program...");

	int32_t success;
	GL_ASSERT(glGetProgramiv(programID_, GL_LINK_STATUS, &success), "failed to get program link info...");
	if (!success)
	{
		glGetProgramInfoLog(programID_, MAX_BUFFER_SIZE, nullptr, buffer_);
		ASSERT(false, "failed to link shader program : %s", buffer_);
	}

	GL_ASSERT(glDeleteShader(vsID), "invalid delete shader id : %d", vsID);
	GL_ASSERT(glDeleteShader(fsID), "invalid delete shader id : %d", fsID);

	bIsInitialized_ = true;
}

void Shader::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	if (programID_ != 0)
	{
		GL_ASSERT(glDeleteProgram(programID_), "failed to delete shader program : %d", programID_);
	}

	bIsInitialized_ = false;
}

void Shader::Bind()
{
	GL_ASSERT(glUseProgram(programID_), "failed to bind shader program...");
}

void Shader::Unbind()
{
	GL_ASSERT(glUseProgram(0), "failed to unbind shader program...");
}

void Shader::SetBoolParameter(const std::string& name, bool value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "failed to set bool type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetBoolParameter(const int32_t& location, bool value)
{
	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "failed to set bool type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetIntParameter(const std::string& name, int32_t value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "faild to set int type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetIntParameter(const int32_t& location, int32_t value)
{
	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "faild to set int type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetFloatParameter(const std::string& name, float value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform1f(location, value), "failed to set float type uniform value : %f", value);
}

void Shader::SetFloatParameter(const int32_t& location, float value)
{
	GL_ASSERT(glUniform1f(location, value), "failed to set float type uniform value : %f", value);
}

void Shader::SetVector2fParameter(const std::string& name, const Vector2f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2fv(location, 1, valuePtr), "failed to set Vector2f type uniform value : (%f, %f)", value.x, value.y);
}

void Shader::SetVector2fParameter(const int32_t& location, const Vector2f& value)
{
	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2fv(location, 1, valuePtr), "failed to set Vector2f type uniform value : (%f, %f)", value.x, value.y);
}

void Shader::SetVector2fParameter(const std::string& name, float x, float y)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform2f(location, x, y), "failed to set Vector2f type uniform value : (%f, %f)", x, y);
}

void Shader::SetVector2fParameter(const int32_t& location, float x, float y)
{
	GL_ASSERT(glUniform2f(location, x, y), "failed to set Vector2f type uniform value : (%f, %f)", x, y);
}

void Shader::SetVector2iParameter(const std::string& name, const Vector2i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2iv(location, 1, valuePtr), "failed to set Vector2i type uniform value : (%d, %d)", value.x, value.y);
}

void Shader::SetVector2iParameter(const int32_t& location, const Vector2i& value)
{
	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2iv(location, 1, valuePtr), "failed to set Vector2i type uniform value : (%d, %d)", value.x, value.y);
}

void Shader::SetVector2iParameter(const std::string& name, int32_t x, int32_t y)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform2i(location, x, y), "failed to set Vector2i type uniform value : (%d, %d)", x, y);
}

void Shader::SetVector2iParameter(const int32_t& location, int32_t x, int32_t y)
{
	GL_ASSERT(glUniform2i(location, x, y), "failed to set Vector2i type uniform value : (%d, %d)", x, y);
}

void Shader::SetVector3fParameter(const std::string& name, const Vector3f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3fv(location, 1, valuePtr), "failed to set Vector3f type uniform value : (%f, %f, %f)", value.x, value.y, value.z);
}

void Shader::SetVector3fParameter(const int32_t& location, const Vector3f& value)
{
	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3fv(location, 1, valuePtr), "failed to set Vector3f type uniform value : (%f, %f, %f)", value.x, value.y, value.z);
}

void Shader::SetVector3fParameter(const std::string& name, float x, float y, float z)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform3f(location, x, y, z), "failed to set Vector3f type uniform value : (%f, %f, %f)", x, y, z);
}

void Shader::SetVector3fParameter(const int32_t& location, float x, float y, float z)
{
	GL_ASSERT(glUniform3f(location, x, y, z), "failed to set Vector3f type uniform value : (%f, %f, %f)", x, y, z);
}

void Shader::SetVector3iParameter(const std::string& name, const Vector3i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3iv(location, 1, valuePtr), "failed to set Vector3i type uniform value : (%d, %d, %d)", value.x, value.y, value.z);
}

void Shader::SetVector3iParameter(const int32_t& location, const Vector3i& value)
{
	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3iv(location, 1, valuePtr), "failed to set Vector3i type uniform value : (%d, %d, %d)", value.x, value.y, value.z);
}

void Shader::SetVector3iParameter(const std::string& name, int32_t x, int32_t y, int32_t z)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform3i(location, x, y, z), "failed to set Vector3i type uniform value : (%d, %d, %d)", x, y, z);
}

void Shader::SetVector3iParameter(const int32_t& location, int32_t x, int32_t y, int32_t z)
{
	GL_ASSERT(glUniform3i(location, x, y, z), "failed to set Vector3i type uniform value : (%d, %d, %d)", x, y, z);
}

void Shader::SetVector4fParameter(const std::string& name, const Vector4f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4fv(location, 1, valuePtr), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", value.x, value.y, value.z, value.w);
}

void Shader::SetVector4fParameter(const int32_t& location, const Vector4f& value)
{
	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4fv(location, 1, valuePtr), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", value.x, value.y, value.z, value.w);
}

void Shader::SetVector4fParameter(const std::string& name, float x, float y, float z, float w)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform4f(location, x, y, z, w), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", x, y, z, w);
}

void Shader::SetVector4fParameter(const int32_t& location, float x, float y, float z, float w)
{
	GL_ASSERT(glUniform4f(location, x, y, z, w), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", x, y, z, w);
}

void Shader::SetVector4iParameter(const std::string& name, const Vector4i& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4iv(location, 1, valuePtr), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", value.x, value.y, value.z, value.w);
}

void Shader::SetVector4iParameter(const int32_t& location, const Vector4i& value)
{
	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4iv(location, 1, valuePtr), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", value.x, value.y, value.z, value.w);
}

void Shader::SetVector4iParameter(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniform4i(location, x, y, z, w), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", x, y, z, w);
}

void Shader::SetVector4iParameter(const int32_t& location, int32_t x, int32_t y, int32_t z, int32_t w)
{
	GL_ASSERT(glUniform4i(location, x, y, z, w), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", x, y, z, w);
}

void Shader::SetMatrix2x2fParameter(const std::string& name, const Matrix2x2f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniformMatrix2fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix2x2f type uniform value...");
}

void Shader::SetMatrix2x2fParameter(const int32_t& location, const Matrix2x2f& value)
{
	GL_ASSERT(glUniformMatrix2fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix2x2f type uniform value...");
}

void Shader::SetMatrix3x3fParameter(const std::string& name, const Matrix3x3f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniformMatrix3fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix3x3f type uniform value...");
}

void Shader::SetMatrix3x3fParameter(const int32_t& location, const Matrix3x3f& value)
{
	GL_ASSERT(glUniformMatrix3fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix3x3f type uniform value...");
}

void Shader::SetMatrix4x4fParameter(const std::string& name, const Matrix4x4f& value)
{
	int32_t location = GetUniformLocation(name);
	ASSERT(location != -1, "failed to find %s uniform location in shader...", name.c_str());

	GL_ASSERT(glUniformMatrix4fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix4x4f type uniform value...");
}

void Shader::SetMatrix4x4fParameter(const int32_t& location, const Matrix4x4f& value)
{
	GL_ASSERT(glUniformMatrix4fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix4x4f type uniform value...");
}

int32_t Shader::GetUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(programID_, uniformName.c_str());
}

void Shader::UpdateDynamicVertexBuffer(uint32_t vertexBufferID, const void* vertexPtr, uint32_t bufferByteSize)
{
	ASSERT(vertexPtr != nullptr, "invalid vertex buffer pointer...");

	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID), "failed to dynamic vertex buffer...");
	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	ASSERT(bufferPtr != nullptr, "failed to map the entire data store of a specified buffer object into the client's address space...");
	
	std::memcpy(bufferPtr, vertexPtr, bufferByteSize);
	GLboolean bSuccssed = glUnmapBuffer(GL_ARRAY_BUFFER);
	ASSERT(bSuccssed, "failed to unmap the entire data store of a specified buffer object into the client's address space...");

	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0), "failed to unbind dynamic vertex buffer...");
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
	ASSERT(shaderID != 0, "failed to create %s shader", type == EType::Vertex ? "Vertex" : "Fragment");

	GL_ASSERT(glShaderSource(shaderID, 1, &sourcePtr, nullptr), "failed to set source code in shader...");
	GL_ASSERT(glCompileShader(shaderID), "failed to compile %s shader...", type == EType::Vertex ? "Vertex" : "Fragment");

	int32_t success;
	GL_ASSERT(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success), "failed to get shader compile status...");
	if (!success)
	{
		glGetShaderInfoLog(shaderID, MAX_BUFFER_SIZE, nullptr, buffer_);
		ASSERT(false, "failed to compile shader : %s", buffer_);
	}

	return shaderID;
}