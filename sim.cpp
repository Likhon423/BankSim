#include <iostream>
#include <vector>

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
std::vector<Texture2D> charThreeIdle;
std::vector<Texture2D> charThreeWalk;
std::vector<Texture2D> charFourIdle;
std::vector<Texture2D> charFourWalk;

CharacterObject* bankerOne;
CharacterObject* bankerTwo;
CharacterObject* bankerThree;

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
    delete bankerTwo;
    delete bankerThree;
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
    ResourceManager::LoadTexture("textures/pc.png", true, "computer");

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
        // char three
            // idle
    ResourceManager::LoadTexture("textures/char3/idle_0.png", true, "charThreeIdle0");
    ResourceManager::LoadTexture("textures/char3/idle_1.png", true, "charThreeIdle1");
    ResourceManager::LoadTexture("textures/char3/idle_2.png", true, "charThreeIdle2");
    ResourceManager::LoadTexture("textures/char3/idle_3.png", true, "charThreeIdle3");
    ResourceManager::LoadTexture("textures/char3/idle_4.png", true, "charThreeIdle4");
    ResourceManager::LoadTexture("textures/char3/idle_5.png", true, "charThreeIdle5");
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle0"));
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle1"));
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle2"));
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle3"));
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle4"));
    charThreeIdle.push_back(ResourceManager::GetTexture("charThreeIdle5"));
            // walk
    ResourceManager::LoadTexture("textures/char3/walk_0.png", true, "charThreeWalk0");
    ResourceManager::LoadTexture("textures/char3/walk_1.png", true, "charThreeWalk1");
    ResourceManager::LoadTexture("textures/char3/walk_2.png", true, "charThreeWalk2");
    ResourceManager::LoadTexture("textures/char3/walk_3.png", true, "charThreeWalk3");
    ResourceManager::LoadTexture("textures/char3/walk_4.png", true, "charThreeWalk4");
    ResourceManager::LoadTexture("textures/char3/walk_5.png", true, "charThreeWalk5");
    ResourceManager::LoadTexture("textures/char3/walk_6.png", true, "charThreeWalk6");
    ResourceManager::LoadTexture("textures/char3/walk_7.png", true, "charThreeWalk7");
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk0"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk1"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk2"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk3"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk4"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk5"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk6"));
    charThreeWalk.push_back(ResourceManager::GetTexture("charThreeWalk7"));    
        // char four
            // idle
    ResourceManager::LoadTexture("textures/char4/idle_0.png", true, "charFourIdle0");
    ResourceManager::LoadTexture("textures/char4/idle_1.png", true, "charFourIdle1");
    ResourceManager::LoadTexture("textures/char4/idle_2.png", true, "charFourIdle2");
    ResourceManager::LoadTexture("textures/char4/idle_3.png", true, "charFourIdle3");
    ResourceManager::LoadTexture("textures/char4/idle_4.png", true, "charFourIdle4");
    ResourceManager::LoadTexture("textures/char4/idle_5.png", true, "charFourIdle5");
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle0"));
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle1"));
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle2"));
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle3"));
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle4"));
    charFourIdle.push_back(ResourceManager::GetTexture("charFourIdle5"));
            // walk
    ResourceManager::LoadTexture("textures/char4/walk_0.png", true, "charFourWalk0");
    ResourceManager::LoadTexture("textures/char4/walk_1.png", true, "charFourWalk1");
    ResourceManager::LoadTexture("textures/char4/walk_2.png", true, "charFourWalk2");
    ResourceManager::LoadTexture("textures/char4/walk_3.png", true, "charFourWalk3");
    ResourceManager::LoadTexture("textures/char4/walk_4.png", true, "charFourWalk4");
    ResourceManager::LoadTexture("textures/char4/walk_5.png", true, "charFourWalk5");
    ResourceManager::LoadTexture("textures/char4/walk_6.png", true, "charFourWalk6");
    ResourceManager::LoadTexture("textures/char4/walk_7.png", true, "charFourWalk7");
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk0"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk1"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk2"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk3"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk4"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk5"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk6"));
    charFourWalk.push_back(ResourceManager::GetTexture("charFourWalk7"));

    bankerOne = new CharacterObject(glm::vec2(this->Width + 50.0f, this->Height / 6), charOneIdle, charOneWalk, 0.07f, glm::vec3(-1.0f, 1.0f, 1.0f));
    bankerTwo = new CharacterObject(glm::vec2(this->Width + 50.0f, this->Height / 2.8), charTwoIdle, charTwoWalk, 0.07f, glm::vec3(-1.0f, 1.0f, 1.0f));
    bankerThree = new CharacterObject(glm::vec2(this->Width + 50.0f, this->Height / 1.8), charFourIdle, charFourWalk, 0.07f, glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Sim::Update(float dt)
{
    bankerOne->Update(dt);
    bankerTwo->Update(dt);
    bankerThree->Update(dt);
}

void Sim::ProcessInput(GLFWwindow *window, float dt)
{

}

void Sim::Render()
{
    Texture2D backgroundTex = ResourceManager::GetTexture("background");
    Texture2D tableTex = ResourceManager::GetTexture("table");
    Texture2D computerTex = ResourceManager::GetTexture("computer");

    Renderer->DrawSprite(backgroundTex, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

    // banker one
    Renderer->DrawSprite(tableTex, glm::vec2(this->Width - 230.0f, this->Height / 8 * 3 + 25.0f), glm::vec2(75.0f, 75.0f), 0.0f, glm::vec3(0.0f, 0.5f, 1.0f));
    Renderer->DrawSprite(computerTex, glm::vec2(this->Width - 163.0f, this->Height / 8 * 3 - 5.0f), glm::vec2(62.0f, 71.0f), 0.0f, glm::vec3(0.0f, 0.5f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f));
    bankerOne->Idle(*Renderer);
    // banker two
    Renderer->DrawSprite(tableTex, glm::vec2(this->Width - 230.0f, this->Height / 5.3 * 3 + 25.0f), glm::vec2(75.0f, 75.0f), 0.0f, glm::vec3(1.0f, -1.0f, 1.0f));
    Renderer->DrawSprite(computerTex, glm::vec2(this->Width - 163.0f, this->Height / 5.3 * 3 - 5.0f), glm::vec2(62.0f, 71.0f), 0.0f, glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f));
    bankerTwo->Idle(*Renderer);
    // banker three
    Renderer->DrawSprite(tableTex, glm::vec2(this->Width - 230.0f, this->Height / 3.95 * 3 + 25.0f), glm::vec2(75.0f, 75.0f), 0.0f, glm::vec3(0.7f, 0.0f, 0.0f));
    Renderer->DrawSprite(computerTex, glm::vec2(this->Width - 163.0f, this->Height / 3.95 * 3 - 5.0f), glm::vec2(62.0f, 71.0f), 0.0f, glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 1.0f));
    bankerThree->Idle(*Renderer);
}