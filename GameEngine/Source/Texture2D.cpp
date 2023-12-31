#include "Texture2D.h"
#include "FileManager.h"
#include "GLAssertionMacro.h"
#include "StringUtils.h"

#include <array>
#include <unordered_map>

#include <glad/glad.h>
#include <stb_image.h>

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

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

/**
 * @brief DDS 파일의 헤더입니다.
 * 
 * @see https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
 */
struct DDSFileHeader
{
	uint8_t  magic[4];
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	uint32_t dwPixelSize;
	uint32_t dwPixelFlags;
	uint32_t dwFourCC;
	uint32_t dwRGBBitCount;
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwABitMask;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
};

/**
 * @brief ASTC 블록 크기를 나타내는 열거형입니다.
 * 
 * @note OpenGL의 GL_COMPRESSED_RGBA_ASTC_<SIZE>x<SIZE>_KHR 상수와 일대일 대응합니다.
 */
enum class EASTCBlockSize
{
	ASTC_4x4 = 0x93B0,
	ASTC_5x4 = 0x93B1,
	ASTC_5x5 = 0x93B2,
	ASTC_6x5 = 0x93B3,
	ASTC_6x6 = 0x93B4,
	ASTC_8x5 = 0x93B5,
	ASTC_8x6 = 0x93B6,
	ASTC_8x8 = 0x93B7,
	ASTC_10x5 = 0x93B8,
	ASTC_10x6 = 0x93B9,
	ASTC_10x8 = 0x93BA,
	ASTC_10x10 = 0x93BB,
	ASTC_12x10 = 0x93BC,
	ASTC_12x12 = 0x93BD,
	None = 0xFFFF,
};

const std::unordered_map<EASTCBlockSize, std::string> blockSizeMaps = {
	{ EASTCBlockSize::ASTC_4x4,   "4x4"   },
	{ EASTCBlockSize::ASTC_5x4,   "5x4"   },
	{ EASTCBlockSize::ASTC_5x5,   "5x5"   },
	{ EASTCBlockSize::ASTC_6x5,   "6x5"   },
	{ EASTCBlockSize::ASTC_6x6,   "6x6"   },
	{ EASTCBlockSize::ASTC_8x5,   "8x5"   },
	{ EASTCBlockSize::ASTC_8x6,   "8x6"   },
	{ EASTCBlockSize::ASTC_8x8,   "8x8"   },
	{ EASTCBlockSize::ASTC_10x5,  "10x5"  },
	{ EASTCBlockSize::ASTC_10x6,  "10x6"  },
	{ EASTCBlockSize::ASTC_10x8,  "10x8"  },
	{ EASTCBlockSize::ASTC_10x10, "10x10" },
	{ EASTCBlockSize::ASTC_12x10, "12x10" },
	{ EASTCBlockSize::ASTC_12x12, "12x12" },
};

const int32_t COUNT_SUPPORT_EXTENSIONS = 7;
const std::array<std::string, COUNT_SUPPORT_EXTENSIONS> supportExtensions = {
	"jpeg",
	"jpg",
	"png",
	"tga",
	"bmp",
	"astc", // 압축 포멧
	"dds",  // 압축 포멧
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

	for (const auto& supportExtension : supportExtensions)
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
		textureID_ = CreateASTCCompressionTexture(path);
	}
	else if (extension == "dds")
	{
		textureID_ = CreateDXTCompressionTexture(path);
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

void Texture2D::Active(uint32_t unit) const
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
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer), "failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	stbi_image_free(buffer);
	buffer = nullptr;

	return textureID;
}

uint32_t Texture2D::CreateASTCCompressionTexture(const std::string& path)
{
	FileManager& fileManager = FileManager::Get();
	std::string filename = fileManager.RemoveBasePath(path);

	bool bFoundBlockSize = false;
	GLenum compressionFormat;

	for (const auto& blockSizeMap : blockSizeMaps)
	{
		if (filename.find(blockSizeMap.second) != std::string::npos)
		{
			bFoundBlockSize = true;
			compressionFormat = static_cast<GLenum>(blockSizeMap.first);
			break;
		}
	}
	ASSERT(bFoundBlockSize, "%s astc is not support astc format...", path.c_str());
	
	std::vector<uint8_t> astcData = FileManager::Get().ReadFileToBuffer(path);
	ASTCFileHeader* astcDataPtr = reinterpret_cast<ASTCFileHeader*>(astcData.data());

	int32_t xsize = astcDataPtr->xsize[0] + (astcDataPtr->xsize[1] << 8) + (astcDataPtr->xsize[2] << 16);
	int32_t ysize = astcDataPtr->ysize[0] + (astcDataPtr->ysize[1] << 8) + (astcDataPtr->ysize[2] << 16);
	int32_t zsize = astcDataPtr->zsize[0] + (astcDataPtr->zsize[1] << 8) + (astcDataPtr->zsize[2] << 16);
	int32_t xblocks = (xsize + astcDataPtr->blockdimX - 1) / astcDataPtr->blockdimX;
	int32_t yblocks = (ysize + astcDataPtr->blockdimY - 1) / astcDataPtr->blockdimY;
	int32_t zblocks = (zsize + astcDataPtr->blockdimZ - 1) / astcDataPtr->blockdimZ;

	uint32_t byteToRead = (xblocks * yblocks * zblocks) << 4;

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glCompressedTexImage2D(GL_TEXTURE_2D, 0, compressionFormat, xsize, ysize, 0, byteToRead, reinterpret_cast<const void*>(&astcDataPtr[1])), "failed to compress texture...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	return textureID;
}

uint32_t Texture2D::CreateDXTCompressionTexture(const std::string& path)
{
	std::vector<uint8_t> dxtData = FileManager::Get().ReadFileToBuffer(path);
	DDSFileHeader* dxtDataPtr = reinterpret_cast<DDSFileHeader*>(dxtData.data());
	
	std::string ddsFileCode;
	for (std::size_t index = 0; index < 4; ++index)
	{
		ddsFileCode += dxtDataPtr->magic[index];
	}
	ASSERT(ddsFileCode == "DDS ", "invalid dds file code : %s", path.c_str());
	
	uint32_t width = dxtDataPtr->dwWidth;
	uint32_t height = dxtDataPtr->dwHeight;
	uint32_t linearSize = dxtDataPtr->dwPitchOrLinearSize;
	uint32_t mipMapCount = dxtDataPtr->dwMipMapCount;
	uint32_t fourCC = dxtDataPtr->dwFourCC;
	uint32_t bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	uint8_t* bufferPtr = reinterpret_cast<uint8_t*>(&dxtDataPtr[1]);

	GLenum format;
	uint32_t blockSize;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		blockSize = 8;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		blockSize = 16;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		blockSize = 16;
		break;
	default:
		ASSERT(false, "not support DXT format or invalid DDS file format : %d", fourCC);
		return 0;
	}

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), "failed to set pixel storage modes...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");

	for (uint32_t level = 0, offset = 0; level < mipMapCount; ++level)
	{
		if (width == 0 || height == 0)
		{
			mipMapCount--;
			continue;
		}

		uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		GL_ASSERT(glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, bufferPtr + offset), "failed to compression texture...");

		offset += size;
		width /= 2;
		height /= 2;
	}
	
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	return textureID;
}