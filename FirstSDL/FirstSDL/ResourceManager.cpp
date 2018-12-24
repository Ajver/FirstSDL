#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
	return ResourceManager::textureCache.getTexture(texturePath);
}