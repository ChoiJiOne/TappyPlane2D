#include "Texture2D.h"
#include "FileManager.h"
#include "GLAssertionMacro.h"
#include "StringUtils.h"

#include <array>

#include <glad/glad.h>
#include <stb_image.h>

/**
 * @brief ASTC 파일의 헤더입니다.
 * 
 * @note astcenc.exe를 이용해서 생성한 파일 기준입니다.
 */
struct ASTCFileHeader
{
	uint8_t magic[4];
	uint8_t blockdimX;
	uint8_t blockdimY;
	uint8_t blockdimZ;
	uint8_t xsize[3];
	uint8_t ysize[3];
	uint8_t zsize[3];
};

const int32_t COUNT_SUPPORT_EXTENSIONS = 6;
std::array<std::string, COUNT_SUPPORT_EXTENSIONS> SUPPORT_EXTENSIONS = {
	"jpeg",
	"jpg",
	"png",
	"tga",
	"bmp",
	"astc", // 압축 포멧
};

Texture2D::~Texture2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Texture2D::Initialize(const std::string& path, bool bCheckValid)
{
	ASSERT(!bIsInitialized_, "already initialize 2d texture resource...");

	FileManager& fileManager = FileManager::Get();
	if (bCheckValid)
	{
		ASSERT(fileManager.IsValidPath(path) && fileManager.IsFilePath(path), "invalid image resource path : %s", path.c_str());
	}
	
	std::string extension = StringUtils::ToLower(fileManager.GetFileExtension(path));
	bool bFoundExtension = false;

	for (const auto& supportExtension : SUPPORT_EXTENSIONS)
	{
		if (extension == supportExtension)
		{
			bFoundExtension = true;
			break;
		}
	}
	ASSERT(bFoundExtension, "not support image resource format : %s", extension.c_str());

	if (extension == "astc")
	{
		textureID_ = CreateCompressionTexture(path);
	}
	else
	{
		textureID_ = CreateNonCompressionTexture(path);
	}

	bIsInitialized_ = true;
}

void Texture2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteTextures(1, &textureID_), "failed to delete texture object...");

	bIsInitialized_ = false;
}

void Texture2D::Active(uint32_t unit)
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + unit), "failed to active texture unit : %d", (GL_TEXTURE0 + unit));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID_), "failed to bind texture...");
}

uint32_t Texture2D::CreateNonCompressionTexture(const std::string& path)
{
	int32_t width;
	int32_t height;
	int32_t channels;
	
	uint8_t* buffer = stbi_load(path.c_str(), &width, &height, &channels, 0);
	ASSERT(buffer != nullptr, "failed to load image resource : %s", path.c_str());

	GLenum format = 0;
	switch (channels)
	{
	case 1:
		format = static_cast<GLenum>(GL_RED);
		break;

	case 3:
		format = static_cast<GLenum>(GL_RGB);
		break;

	case 4:
		format = static_cast<GLenum>(GL_RGBA);
		break;

	default:
		ASSERT(false, "not support image channel : %d", channels);
	}

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer), "failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");

	stbi_image_free(buffer);
	buffer = nullptr;

	return textureID;
}

uint32_t Texture2D::CreateCompressionTexture(const std::string& path)
{
	return uint32_t(0);
}