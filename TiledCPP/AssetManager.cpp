#include "AssetManager.h"

template<typename T>
void AssetManager::Store(const std::string& Name, const T& Asset)
{
    Assets[Name] = FAsset(Asset);
}

template<typename T>
T* AssetManager::Get(const std::string& Name)
{
    auto it = Assets.find(Name);
    if (it != Assets.end())
    {
        return it->second.Get<T>();
    }
    return nullptr;
}

Texture2D* AssetManager::LoadTexture(const std::string& Name, const std::string& Filename)
{
    if (Exists(Name))
    {
        return Get<Texture2D>(Name);
    }

    Texture2D Texture = ::LoadTexture(Filename.c_str());
    if (Texture.id == 0)
    {
        std::cout << "Failed to load texture: " << Filename << std::endl;
        return nullptr;
    }
    Store(Name, Texture);
    return Get<Texture2D>(Name);
}

Sound* AssetManager::LoadSound(const std::string& Name, const std::string& Filename)
{
    if (Exists(Name))
    {
        return Get<Sound>(Name);
    }

    Sound SoundAsset = ::LoadSound(Filename.c_str());
    if (SoundAsset.stream.buffer == nullptr)
    {
        std::cout << "Failed to load sound: " << Filename << std::endl;
        return nullptr;
    }
    Store(Name, SoundAsset);
    return Get<Sound>(Name);
}

Music* AssetManager::LoadMusic(const std::string& Name, const std::string& Filename)
{
    if (Exists(Name))
    {
        return Get<Music>(Name);
    }

    Music MusicAsset = ::LoadMusicStream(Filename.c_str());
    if (MusicAsset.stream.buffer == nullptr)
    {
        std::cout << "Failed to load music: " << Filename << std::endl;
        return nullptr;
    }
    Store(Name, MusicAsset);
    return Get<Music>(Name);
}

Font* AssetManager::LoadFont(const std::string& Name, const std::string& Filename, int FontSize)
{
    if (Exists(Name))
    {
        return Get<Font>(Name);
    }

    Font FontAsset = ::LoadFontEx(Filename.c_str(), FontSize, 0, 0);
    if (FontAsset.texture.id == 0)
    {
        std::cout << "Failed to load font: " << Filename << std::endl;
        return nullptr;
    }
    Store(Name, FontAsset);
    return Get<Font>(Name);
}

Model* AssetManager::LoadModel(const std::string& Name, const std::string& Filename)
{
    if (Exists(Name))
    {
        return Get<Model>(Name);
    }

    Model ModelAsset = ::LoadModel(Filename.c_str());
    if (ModelAsset.meshCount == 0)
    {
        std::cout << "Failed to load model: " << Filename << std::endl;
        return nullptr;
    }
    Store(Name, ModelAsset);
    return Get<Model>(Name);
}

bool AssetManager::Exists(const std::string& Name) const
{
    if (Assets.size() < 1)
    {
        return false;
    }

    return Assets.find(Name) != Assets.end();
}

void AssetManager::Remove(const std::string& Name)
{
    Assets.erase(Name);
}

void AssetManager::Clear()
{
    Assets.clear();
}

void AssetManager::UnloadAll()
{
    if (Assets.empty())
    {
        return;
    }

    for (auto& Pair : Assets)
    {
        const FAsset& Asset = Pair.second;

        if (Asset.Type == &typeid(Texture2D))
        {
            UnloadTexture(*Asset.Get<Texture2D>());
        }
        else if (Asset.Type == &typeid(Sound))
        {
            UnloadSound(*Asset.Get<Sound>());
        }
        else if (Asset.Type == &typeid(Music))
        {
            UnloadMusicStream(*Asset.Get<Music>());
        }
        else if (Asset.Type == &typeid(Font))
        {
            UnloadFont(*Asset.Get<Font>());
        }
        else if (Asset.Type == &typeid(Model))
        {
            UnloadModel(*Asset.Get<Model>());
        }
    }
    Clear();
}

std::string AssetManager::GetAssetPath(const char* dir = nullptr)
{
    return std::string("../Assets/") + dir;
}