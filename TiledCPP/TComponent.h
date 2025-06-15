#pragma once

#include "Engine.h"
#include "IRenderableAsset.h"

FORWARD_DECLARE(TObject);

class ENGINE_API TComponent : IRenderableAsset
{
public:
	typedef TComponent Super;

	~TComponent() = default;
	bool IsActive() const { return m_Active; }
	void SetActive(const bool active) { m_Active = active; }
	void SetOwner(TObject* newOwner) { if (newOwner != nullptr) { m_Owner = newOwner; } }

	virtual void Update(float deltaTime);
	virtual void Initialize();

	virtual bool CanRender() { return false; };
	virtual void Render() override;

protected:
	bool m_Active = true;
	TObject* m_Owner;
};