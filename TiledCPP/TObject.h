#pragma once

#include "Engine.h"
#include "TComponent.h"
#include "TObjectBase.h"
#include "TWorld.h"

FORWARD_DECLARE(TScene);

class ENGINE_API TObject : TObjectBase
{

protected:
    std::string m_Name;
    std::vector<std::unique_ptr<TComponent>> m_Components;
    TScene* m_ParentScene = nullptr;

public: 
    typedef TObject Super;
    TObject() = default;

    bool bPendingDestroy = false;

    void SetScene(TScene& scene);
    virtual void BeginDestroy();
    virtual void Cleanup();
    virtual void Initialize();

    template<typename T>
    T* GetComponent() const
    {
        for (auto& component : m_Components)
        {
            if (T* comp = dynamic_cast<T*>(component.get()))
            {
                return comp;
            }
        }
        return nullptr;
    }

    template<typename T>
    T* AddComponent()
    {
        auto newComponent = std::make_unique<T>();
        T* rawPtr = newComponent.get();

        static_cast<TComponent*>(newComponent.get())->Initialize();
        static_cast<TComponent*>(newComponent.get())->SetOwner(this);
        m_Components.push_back(std::move(newComponent));

        return rawPtr;
    }
    
    std::vector<std::unique_ptr<TComponent>>* GetComponents();

    template<typename T, typename... Args>
    static T* CreateObject(Args&&... args)
    {
        static_assert(std::is_base_of_v<TObject, T>, "T must derive from TObject");
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = obj.get();
        static_cast<TObject*>(rawPtr)->Initialize();
        TWorld::Instance().GetScene()->GetObjects().push_back(rawPtr);
        //static_cast<TObject*>(rawPtr)->SetScene(*GEngine.GScene);
        obj.release(); // Release ownership
        return rawPtr;
    }

    virtual void Update(float deltaTime);
};