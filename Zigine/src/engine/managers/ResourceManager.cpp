#include "ResourceManager.h"

DEFINE_INSTANCE_FUNCTION(ResourceManager, Resources)

bool ResourceManager::LoadModel(const std::string& key, const std::string& path)
{
    // (TODO): Implement
    return true;
}

sf::Sound* ResourceManager::LoadSound(const std::string& key, const std::string& path)
{
    // (TODO): Implement
    return nullptr;
}

sf::Texture* ResourceManager::LoadTexture(const std::string& key, const std::string& path)
{
    // (TODO): Implement
    return nullptr;
}

bool ResourceManager::GetModel(const std::string& key)
{
    // (TODO): Implement
    return false;
}

sf::Sound* ResourceManager::GetSound(const std::string& key)
{
    // (TODO): Implement
    return nullptr;
}

sf::Texture* ResourceManager::GetTexture(const std::string& key)
{
    // (TODO): Implement
    return nullptr;
}
