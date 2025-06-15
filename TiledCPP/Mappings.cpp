#include "Mappings.h"

std::unordered_map<std::string, std::function<void(float)>> Mappings::m_AxisBindings;
std::unordered_map<std::string, FAxisMapping> Mappings::m_AxisMappings;

void Mappings::InitializeMappings()
{
    AddAxisMapping("move_forwards", KEY_W, 1.0f);
    AddAxisMapping("move_backwards", KEY_S, -1.0f);
    AddAxisMapping("move_left", KEY_A, -1.0f);
    AddAxisMapping("move_right", KEY_D, 1.0f);
}

void Mappings::UpdateMappings()
{
    Process();
}

void Mappings::AddAxisMapping(const std::string mappingName, const KeyboardKey key, const float scalar)
{
    FAxisMapping newMapping;
    newMapping.key = key;
    newMapping.scalar = scalar;

	m_AxisMappings.insert_or_assign(mappingName, newMapping);
}

void Mappings::RemoveAxisMapping(std::string mappingName)
{
	if (m_AxisMappings.find(mappingName) == m_AxisMappings.end()) return;

	m_AxisMappings.erase(mappingName);
}

void Mappings::BindToAction(const std::string& axisName, std::function<void(float)> callback) 
{
    m_AxisBindings[axisName] = callback;
}

void Mappings::Process()
{
    //Axes
    for (const std::pair<std::string, FAxisMapping> mapping : m_AxisMappings) 
    {
        float axisValue = 0.0f;

        if (IsKeyDown(mapping.second.key))
        {
            axisValue = 1.0f * mapping.second.scalar;
        }

        if (m_AxisMappings.find(mapping.first) != m_AxisMappings.end())
        {
            m_AxisBindings[mapping.first](axisValue);
        }
    }
}