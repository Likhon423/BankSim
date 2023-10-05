#pragma once
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Sim
{
public:
    // sim state
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;

    // constructor/destructor
    Sim(unsigned int width, unsigned int height);
    ~Sim();
    // initialize sim state (load all shaders/textures)
    void Init();
    // sim loop
    void ProcessInput(GLFWwindow* window, float dt);
    void Update(float dt);
    void Render();
};