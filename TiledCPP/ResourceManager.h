#pragma once
#include "Common.h"

template<typename T>
class ENGINE_API ResourceManager
{
public:
    template<typename... Args>
    std::shared_ptr<T> Load(const std::string& name, Args&&... args)
    {
        auto it = m_Resources.find(name);
        if (it != m_Resources.end())
        {
            return it->second;
        }

        auto resource = std::make_shared<T>(std::forward<Args>(args)...);
        m_Resources[name] = resource;
        return resource;
    }

    void Unload(const std::string& name)
    {
        m_Resources.erase(name);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_Resources;
};