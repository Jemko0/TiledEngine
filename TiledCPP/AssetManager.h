#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include <iostream>
#include "raylib.h"

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

class AssetManager
{
public:
    static std::string GetAssetPath(const char* dir);
};