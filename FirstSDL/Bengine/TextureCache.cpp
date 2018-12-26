#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
	// Lookup the texture and see if its in the map
	auto mit = textureMap.find(texturePath);

	// If it's not in the map
	if (mit == textureMap.end()) {
		// Load the texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
	
		textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded new texture: " << texturePath << std::endl;

		return newTexture;
	}

	std::cout << "Used cached texture: " << texturePath << std::endl;

	// If texture was found - return it!
	return mit->second;
}