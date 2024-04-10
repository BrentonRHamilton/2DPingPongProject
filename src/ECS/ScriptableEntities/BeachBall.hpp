#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/Entity.hpp>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/Scene.hpp>

class BeachBall : public Canis::ScriptableEntity
{
private:
    glm::vec2   m_direction;
    float       m_speed;
    float       m_timeBetweenAnimation = 3.0f;
    float       m_countDown = 0.0f;
    unsigned int m_animIndex = 0;
    int m_scoreLeft;
    int m_scoreRight;
    //Canis::Scene& scene;

    std::vector<glm::vec2> m_spawnPoints = {};
public:

    //BeachBall(Canis::Scene& _scene) : scene(_scene) {}
    


    void OnCreate()
    {
        m_countDown = m_timeBetweenAnimation;
    }

    void OnReady()
    {
        m_direction = glm::vec2(1.0f, 0.4f);
        m_speed = 150.0f;
        m_scoreLeft = 0; // Initialize scores
        m_scoreRight = 0;
    }

    void ResetBallPosition() {
        auto& ballRect = GetComponent<Canis::RectTransformComponent>();
        ballRect.position = { GetWindow().GetScreenWidth() / 2.0f, GetWindow().GetScreenHeight() / 2.0f }; // Reset ball position to the center
        m_direction = glm::vec2(1.0f, 0.4f);
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        auto& rect = GetComponent<Canis::RectTransformComponent>();
        //auto entities = scene.GetEntities();

        //ballRect.position += m_direction * (m_speed * _dt);

        auto& ballRect = GetComponent<Canis::RectTransformComponent>(); 
        Canis::Entity leftPaddle = entity.GetEntityWithTag("PADDLELEFT");
        auto& leftPaddleRect = leftPaddle.GetComponent<Canis::RectTransformComponent>(); 
        //auto& rightPaddleRect = GetRightPaddle().GetComponent<Canis::RectTransformComponent>(); 

        float halfSizeX = rect.size.x/2.0f;
        float halfSizeY = rect.size.y/2.0f;
        auto& scene =GetScene();


        //float rect.position.x= GetWindow().GetScreenWidth()/2.0f;
        //float rect.position.y= GetWindow().GetScreenWidth()/2.0f;

        if (rect.position.x + halfSizeX >= GetWindow().GetScreenWidth()/2.0f ||
                rect.position.x - halfSizeX <= GetWindow().GetScreenWidth()/-2.0f)
            m_direction.x *= -1.0f;

        if (rect.position.y + halfSizeY >= GetWindow().GetScreenHeight()/2.0f ||
                rect.position.y - halfSizeY <= GetWindow().GetScreenHeight()/-2.0f)
            m_direction.y *= -1.0f;
        
        rect.position += (m_direction * (m_speed * _dt));

        if (GetInputManager().JustPressedKey(SDLK_p))
            m_speed += 50.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_r))
            m_speed = 150.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_d))
        {
            GetScene().Instantiate("assets/prefebs/test_character.scene");
        }

        if (GetInputManager().GetKey(SDL_SCANCODE_W))
        {
            //Canis::Log("DOWN");
        }
        else
        {
            //Canis::Log("UP");
        }
        ////updates every time
        if (rect.position.x < ballRect.position.x + ballRect.size.x &&
                rect.position.x + rect.size.x > ballRect.position.x &&
                rect.position.y < ballRect.position.y + ballRect.size.y &&
                rect.position.y + rect.size.y > ballRect.position.y)
            {
                // Ball collides with paddle, reverse direction both horizontally and vertically
                m_direction.x *= -1.0f;
                m_direction.y *= -1.0f;
                 // Exit the loop after the first collision to prevent multiple collisions per frame
            }

                // Check if ball goes out of bounds (score condition)
        if (ballRect.position.x < 0) {
            // Ball goes out on the left side, increase right player's score
            ++m_scoreRight;
            ResetBallPosition();
        }
        else if (ballRect.position.x + ballRect.size.x > GetWindow().GetScreenWidth()) {
            // Ball goes out on the right side, increase left player's score
            ++m_scoreLeft;
            ResetBallPosition();
        }

    };

};

bool DecodeBeachBall(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "BeachBall")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<BeachBall>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}