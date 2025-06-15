#pragma once

#include "Common.h"

class ENGINE_API Module {
public:
    virtual ~Module() = default;
    virtual bool Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Shutdown() = 0;
    virtual const char* GetName() const = 0;
};

class ENGINE_API ModuleManager 
{
    public:
        template<typename T>
        T* RegisterModule()
        {
            static_assert(std::is_base_of_v<Module, T>);
            auto module = std::make_unique<T>();
            T* ptr = module.get();
            m_Modules.push_back(std::move(module));
            return ptr;
        }
    
        void InitializeAll();
        void UpdateAll(float deltaTime);
        void ShutdownAll();
    
    private:
        std::vector<std::unique_ptr<Module>> m_Modules;
};