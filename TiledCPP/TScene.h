#pragma once

#include "Engine.h"
#include "IRenderableAsset.h"

FORWARD_DECLARE(TObject);
FORWARD_DECLARE(TTileMap);

class ENGINE_API TScene : public IRenderableAsset
{
private:
    const char* m_Identifier = nullptr;
    std::vector<std::unique_ptr<TObject>> m_Objects;
    TTileMap* m_Tilemap = nullptr;

    const char* GenerateIdentifier();

public:
    TScene();
    ~TScene();

    Camera2D* activeCamera = nullptr;

    std::vector<TObject*>& GetObjects();
    bool RegisterObject(std::unique_ptr<TObject> obj);
    bool UnregisterObject(TObject* o);

    const char* GetIdentifier();

    TTileMap* InitTileMap(int w, int h);
    TTileMap* GetTileMap();
    void DestroyTileMap();

    //utility

    Rectangle GetCameraFrustum();
    
    void Init();
    void Update(float deltaTime);
    virtual void Render() override;
};