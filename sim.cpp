#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <irrklang/irrKlang.h>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

#include "sim.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "character_object.h"

SpriteRenderer* Renderer;
TextRenderer* Text;
std::vector<Texture2D> charOneIdle;
std::vector<Texture2D> charOneWalk;
std::vector<Texture2D> charTwoIdle;
std::vector<Texture2D> charTwoWalk;
CharacterObject* bankerOne;

float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

Sim::Sim(unsigned int width, unsigned int height)
    : Keys(), KeysProcessed(), Width(width), Height(height)
{
    
}

Sim::~Sim()
{
    delete Renderer;
    delete bankerOne;
    delete Text;
}

void Sim::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);

    // load textures
    ResourceManager::LoadTexture("textures/bg-cube.jpg", false, "background");
    ResourceManager::LoadTexture("textures/banker1.png", true, "banker");
    ResourceManager::LoadTexture("textures/table.png", true, "table");

    // load characters
        // char one
            // idle
    ResourceManager::LoadTexture("textures/char1/idle_0.png", true, "charOneIdle0");
    ResourceManager::LoadTexture("textures/char1/idle_1.png", true, "charOneIdle1");
    ResourceManager::LoadTexture("textures/char1/idle_2.png", true, "charOneIdle2");
    ResourceManager::LoadTexture("textures/char1/idle_3.png", true, "charOneIdle3");
    ResourceManager::LoadTexture("textures/char1/idle_4.png", true, "charOneIdle4");
    ResourceManager::LoadTexture("textures/char1/idle_5.png", true, "charOneIdle5");
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle0"));
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle1"));
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle2"));
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle3"));
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle4"));
    charOneIdle.push_back(ResourceManager::GetTexture("charOneIdle5"));
            // walk
    ResourceManager::LoadTexture("textures/char1/walk_0.png", true, "charOneWalk0");
    ResourceManager::LoadTexture("textures/char1/walk_1.png", true, "charOneWalk1");
    ResourceManager::LoadTexture("textures/char1/walk_2.png", true, "charOneWalk2");
    ResourceManager::LoadTexture("textures/char1/walk_3.png", true, "charOneWalk3");
    ResourceManager::LoadTexture("textures/char1/walk_4.png", true, "charOneWalk4");
    ResourceManager::LoadTexture("textures/char1/walk_5.png", true, "charOneWalk5");
    ResourceManager::LoadTexture("textures/char1/walk_6.png", true, "charOneWalk6");
    ResourceManager::LoadTexture("textures/char1/walk_7.png", true, "charOneWalk7");
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk0"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk1"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk2"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk3"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk4"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk5"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk6"));
    charOneWalk.push_back(ResourceManager::GetTexture("charOneWalk7"));
        // char two
            // idle
    ResourceManager::LoadTexture("textures/char2/idle_0.png", true, "charTwoIdle0");
    ResourceManager::LoadTexture("textures/char2/idle_1.png", true, "charTwoIdle1");
    ResourceManager::LoadTexture("textures/char2/idle_2.png", true, "charTwoIdle2");
    ResourceManager::LoadTexture("textures/char2/idle_3.png", true, "charTwoIdle3");
    ResourceManager::LoadTexture("textures/char2/idle_4.png", true, "charTwoIdle4");
    ResourceManager::LoadTexture("textures/char2/idle_5.png", true, "charTwoIdle5");
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle0"));
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle1"));
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle2"));
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle3"));
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle4"));
    charTwoIdle.push_back(ResourceManager::GetTexture("charTwoIdle5"));
            // walk
    ResourceManager::LoadTexture("textures/char2/walk_0.png", true, "charTwoWalk0");
    ResourceManager::LoadTexture("textures/char2/walk_1.png", true, "charTwoWalk1");
    ResourceManager::LoadTexture("textures/char2/walk_2.png", true, "charTwoWalk2");
    ResourceManager::LoadTexture("textures/char2/walk_3.png", true, "charTwoWalk3");
    ResourceManager::LoadTexture("textures/char2/walk_4.png", true, "charTwoWalk4");
    ResourceManager::LoadTexture("textures/char2/walk_5.png", true, "charTwoWalk5");
    ResourceManager::LoadTexture("textures/char2/walk_6.png", true, "charTwoWalk6");
    ResourceManager::LoadTexture("textures/char2/walk_7.png", true, "charTwoWalk7");
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk0"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk1"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk2"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk3"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk4"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk5"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk6"));
    charTwoWalk.push_back(ResourceManager::GetTexture("charTwoWalk7"));

    bankerOne = new CharacterObject(glm::vec2(this->Width - 250.0f, this->Height / 6), charOneIdle, charOneWalk, 0.07f);
}

void Sim::Update(float dt)
{
    bankerOne->Update(dt);
}

void Sim::ProcessInput(GLFWwindow *window, float dt)
{

}

void Sim::Render()
{
    Texture2D backgroundTex = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(backgroundTex, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    Texture2D tableTex = ResourceManager::GetTexture("table");
    Renderer->DrawSprite(tableTex, glm::vec2(this->Width - 250.0f, this->Height / 8 * 3), glm::vec2(100.0f, 100.0f), 0.0f);
    bankerOne->Idle(*Renderer);
}