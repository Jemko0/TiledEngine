#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include <iostream>
#include "raylib.h"

class AssetManager
{

protected:
    struct FAsset 
    {
        std::shared_ptr<void> Data;
        const std::type_info* Type;

        template<typename T>
        FAsset(const T& Value) : Data(std::make_shared<T>(Value)), Type(&typeid(T)) {}

        //default
        FAsset() : Data(nullptr), Type(nullptr) {}

        template<typename T>
        T* Get() const 
        {
            if (Type != &typeid(T)) 
            {
                return nullptr;
            }
            return std::static_pointer_cast<T>(Data).get();
        }
    };

    std::unordered_map<std::string, FAsset> Assets;

public:

    template<typename T>
    void Store(const std::string& Name, const T& Asset);

    template<typename T>
    T* Get(const std::string& Name);

    bool Exists(const std::string& Name) const;
    void Remove(const std::string& Name);
    void Clear();
    void UnloadAll();

    std::string GetAssetPath(const char* dir);

    /// <summary>
    /// Load functions will automatically get the asset, if its already loaded
    /// </summary>
    Texture2D* LoadTexture(const std::string& Name, const std::string& Filename);

    /// <summary>
    /// Load functions will automatically get the asset, if its already loaded
    /// </summary>
    Sound* LoadSound(const std::string& Name, const std::string& Filename);

    /// <summary>
    /// Load functions will automatically get the asset, if its already loaded
    /// </summary>
    Music* LoadMusic(const std::string& Name, const std::string& Filename);

    /// <summary>
    /// Load functions will automatically get the asset, if its already loaded
    /// </summary>
    Font* LoadFont(const std::string& Name, const std::string& Filename, int FontSize = 32);

    /// <summary>
    /// Load functions will automatically get the asset, if its already loaded
    /// </summary>
    Model* LoadModel(const std::string& Name, const std::string& Filename);

    ~AssetManager() 
    {
        UnloadAll();
    }
};