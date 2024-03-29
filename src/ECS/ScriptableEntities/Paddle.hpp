#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
// Thrown in some ifs statements 
class Paddle : public Canis::ScriptableEntity
{
private:
    glm::vec2   m_direction;
    float       m_speed;
    float       m_timeBetweenAnimation = 3.0f;
    float       m_countDown = 0.0f;
    unsigned int m_animIndex = 0;
    std::vector<glm::vec2> m_spawnPoints = {};
public:
    void OnCreate()
    {
      Canis ::Log("Paddle Loaded");
    }

    void OnReady()
    {
        m_direction = glm::vec2(0.0f, 0.0f);
        m_speed = 150.0f;
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
         m_direction = glm::vec2(0.0f, 0.0f);

        if (GetInputManager().GetKey(SDL_SCANCODE_S))
        {
            m_direction = glm::vec2(0.0f, -1.0f);//direction
        }

        if (GetInputManager().GetKey(SDL_SCANCODE_W))
        {
            m_direction = glm::vec2(0.0f, 1.0f);
        }

        if (GetInputManager().GetKey(SDL_SCANCODE_A))
        {

        }

        if (GetInputManager().GetKey(SDL_SCANCODE_D))
        {
            
        }

        if (GetInputManager().GetKey(SDL_SCANCODE_UP))
        {
            m_direction = glm::vec2(0.0f, 1.0f);
        }
        else
        {
            //Canis::Log("UP");
        }
        if (GetInputManager().GetKey(SDL_SCANCODE_DOWN))
        {
            m_direction = glm::vec2(0.0f, -1.0f);
        }
        else
        {
            //Canis::Log("UP");
        }
        auto& rect = GetComponent<Canis::RectTransformComponent>();
        rect.position += (m_direction * (m_speed * _dt));
    }
};

bool DecodePaddle(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "Paddle")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<Paddle>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}