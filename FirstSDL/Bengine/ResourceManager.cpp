#include "ResourceManager.h"

namespace Bengine
{

	TextureCache ResourceManager::textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return ResourceManager::textureCache.getTexture(texturePath);
	}

}