#include "AssetManager.h"

std::string AssetManager::GetAssetPath(const char* dir = nullptr)
{
    return std::string("../Assets/") + dir;
}
