#pragma once

#include "Engine.h"
#include "raylib.h"
#include <functional>

struct FActionMapping
{
	KeyboardKey key = KEY_A;
	bool pressed = false;
	bool released = false;
};

struct FAxisMapping
{
	KeyboardKey key;
	float scalar;

	FAxisMapping()
	{
		key = KEY_A;
		scalar = 0.0f;
	}

	FAxisMapping(KeyboardKey key)
	{
		this->key = key;
		scalar = 0.0f;
	}

	void SetAxisValue(float newVal)
	{
		scalar = newVal;
	}
};

class ENGINE_API Mappings
{
	static std::unordered_map<std::string, FActionMapping> m_ActionMappings;
	static std::unordered_map<std::string, FAxisMapping> m_AxisMappings;
	static std::unordered_map<std::string, std::function<void(float)>> m_AxisBindings;

public:
	static void InitializeMappings();
	static void UpdateMappings();
	static void Process();

	static void BindToAction(const std::string& axisName, std::function<void(float)> callback);

	static void AddAxisMapping(const std::string mappingName, const KeyboardKey key, const float scalar);
	static void RemoveAxisMapping(std::string mappingName);
};