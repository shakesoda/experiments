#ifndef _NEPGEAR_TEXTURE_H_
#define _NEPGEAR_TEXTURE_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <map>

namespace Nepgear
{

enum TextureFormat
{
	// 1-4 channels + palleted
	TextureFormat_Luminance = 0,
	TextureFormat_Luminance_Alpha,
	TextureFormat_RGB,
	TextureFormat_RGBA,
	TextureFormat_Pallete,
	// 32-bit float variants for 1-4 channels:
	TextureFormat_Luminance_F32,
	TextureFormat_Luminance_Alpha_F32,
	TextureFormat_RGB_F32,
	TextureFormat_RGBA_F32
};

struct Texture
{
	TextureFormat format;
	// frames, pixels.
	std::vector< std::vector<char> > pixels;
	int width, height;
	unsigned id;
};

class ImageLoader
{
public:
	Texture *load(std::string path);

	static void reload();

	// texture + path list, for when reloading is necessary.
	static std::map<std::string, Texture*> textures;
};

}
#endif

