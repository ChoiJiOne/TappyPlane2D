#pragma once

#include <vector>
#include <string>
#include <memory>

#include "IResource.h"
#include "Vector2.h"


/**
 * @brief �ؽ�ó ��Ʋ�󽺿� ǥ�õ� �۸����Դϴ�.
 */
struct Glyph
{
	int32_t codePoint;
	Vector2i position0;
	Vector2i position1;
	float xoffset;
	float yoffset;
	float xoffset2;
	float yoffset2;
	float xadvance;
};


/**
 * @brief Ʈ�� Ÿ�� ��Ʈ ������ �ε��ϰ� �ؽ�Ʈ �ؽ�ó ��Ʋ�󽺸� ���� �� �����մϴ�.
 * 
 * @note Ʈ�� Ÿ�� ��Ʈ ������ Ȯ���ڴ� .ttf �� �����մϴ�.
 */
class TTFont : public IResource
{
public:
	/**
	 * @brief Ʈ�� Ÿ�� ��Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note �ʱ�ȭ�� �����ϱ� ���ؼ��� �ݵ�� ������ �ʱ�ȭ �޼��带 ȣ���ؾ� �մϴ�.
	 */
	TTFont() = default;


	/**
	 * @brief Ʈ�� Ÿ�� ��Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������ �����ϱ� ���ؼ��� �ݵ�� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~TTFont();


	/**
	 * @brief Ʈ�� Ÿ�� ��Ʈ Ŭ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TTFont);


	/**
	 * @brief Ʈ�� Ÿ�� ��Ʈ ������ �ε��ϰ� �۸��� ��Ʋ�󽺸� �����մϴ�.
	 *
	 * @param path Ʈ�� Ÿ�� ��Ʈ ������ ����Դϴ�.
	 * @param beginCodePoint �۸��� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �������Դϴ�.
	 * @param endCodePoint �۸��� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �����Դϴ�.
	 * @param fontSize ��Ʈ�� ũ���Դϴ�.
	 * 
	 * @note 
	 * - �۸��� �ؽ�ó ��Ʋ�� ������ ���۰� ���� �ڵ� ����Ʈ�� �����մϴ�.
	 * - Ʈ�� Ÿ�� ��Ʈ ������ Ȯ���ڴ� .ttf �� �����մϴ�.
	 */
	void Initialize(const std::string& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize);


	/**
	 * @brief Ʈ�� Ÿ�� ��Ʈ Ŭ���� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �۸��� �ؽ�ó ��Ʋ���� ID�� ����ϴ�.
	 *
	 * @return �۸��� �ؽ�ó ��Ʋ���� ID ���� ��ȯ�մϴ�.
	 */
	uint32_t GetGlyphAtlasID() const { return glyphAtlasID_; }


	/**
	 * @brief �ڵ� ����Ʈ�� �����ϴ� ���� ��ġ �� ũ�� ������ ����ϴ�.
	 *
	 * @param codePoint ��ġ �� ������ �˰� ���� �ڵ� ����Ʈ ���Դϴ�.
	 *
	 * @return �ڵ� ����Ʈ�� �����ϴ� ������ ��ġ �� ũ�� ������ ��ȯ�մϴ�.
	 */
	const Glyph& GetGlyph(int32_t codePoint) const;


	/**
	 * @brief �ؽ�ó ��Ʋ���� ũ�⸦ ����ϴ�.
	 *
	 * @return �ؽ�ó ��Ʋ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	int32_t GetGlyphAtlasSize() const { return glyphAtlasSize_; }


	/**
	 * @brief �ڵ� ����Ʈ�� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param codePoint ��ȿ�� �˻縦 ������ �ڵ� ����Ʈ ���Դϴ�.
	 *
	 * @return �ڵ� ����Ʈ�� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidCodePoint(int32_t codePoint) const;


	/**
	 * @brief �ؽ�Ʈ�� ũ�⸦ �����մϴ�.
	 *
	 * @note ���� ������ �ȼ� �����Դϴ�.
	 *
	 * @param text ������ �ؽ�Ʈ�Դϴ�.
	 * @param outWidth ������ �ؽ�Ʈ�� ���� ũ���Դϴ�.
	 * @param outHeight ������ �ؽ�Ʈ�� ���� ũ���Դϴ�.
	 */
	void MeasureText(const std::wstring& text, float& outWidth, float& outHeight) const;


private:
	/**
	 * @brief �۸��� �ؽ�ó ��Ʋ�� ��Ʈ���� �����մϴ�.
	 *
	 * @note �۸��� �ؽ�ó ��Ʋ���� ���� ���� ũ��� �����ϴ�.
	 *
	 * @param buffer Ʈ�� Ÿ�� ��Ʈ ���ҽ� �����Դϴ�.
	 * @param beginCodePoint ���� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �������Դϴ�.
	 * @param endCodePoint ���� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �����Դϴ�.
	 * @param fontSize ��Ʈ�� ũ���Դϴ�.
	 * @param outGlyphs �ؽ�ó ��Ʋ�� ���� �ڵ� ����Ʈ�� �����ϴ� ���� ��ġ �� ũ�� �����Դϴ�.
	 * @param outGlyphAtlasSize �۸��� �ؽ�ó ��Ʋ�� ũ���Դϴ�.
	 *
	 * @return ������ �۸��� �ؽ�ó ��Ʋ�� ��Ʈ���� ��ȯ�մϴ�.
	 */
	std::shared_ptr<uint8_t[]> GenerateGlyphAtlasBitmap(
		const std::vector<uint8_t>& buffer,
		int32_t beginCodePoint,
		int32_t endCodePoint,
		float fontSize,
		std::vector<Glyph>& outGlyphs,
		int32_t& outGlyphAtlasSize
	);


	/**
	 * @brief �ؽ�ó ��Ʋ�� ��Ʈ������ ���� �ؽ�ó ���ҽ��� �����մϴ�.
	 *
	 * @param bitmap �ؽ�ó ��Ʋ�� ��Ʈ���Դϴ�.
	 * @param atlasSize �ؽ�ó ��Ʋ�� ��Ʈ���� ���� ���� ũ���Դϴ�
	 * 
	 * @return �ؽ�ó ���ҽ��� ID ���� ��ȭ�մϴ�.
	 */
	uint32_t CreateGlyphAtlasFromBitmap(
		const std::shared_ptr<uint8_t[]>& bitmap,
		const int32_t& glyphAtlasSize
	);


private:
	/**
	 * @brief ���� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �������Դϴ�.
	 *
	 * @note �ؽ�ó ��Ʋ�󽺴� �������� �����մϴ�.
	 */
	int32_t beginCodePoint_ = 0;


	/**
	 * @brief ���� �ؽ�ó ��Ʋ���� �ڵ� ����Ʈ �����Դϴ�.
	 *
	 * @note �ؽ�ó ��Ʋ�󽺴� ������ �����մϴ�.
	 */
	int32_t endCodePoint_ = 0;


	/**
	 * @brief �۸��� �ؽ�ó ��Ʋ���� ũ���Դϴ�.
	 */
	int32_t glyphAtlasSize_ = 0;


	/**
	 * @brief �۸��� �ؽ�ó ��Ʋ�� ���� �ڵ� ����Ʈ�� �����ϴ� ���� ��ġ �� ũ�� �����Դϴ�.
	 */
	std::vector<Glyph> glyphs_;


	/**
	 * @brief �۸��� �ؽ�ó ��Ʋ���� ID�Դϴ�.
	 */
	uint32_t glyphAtlasID_ = 0;
};