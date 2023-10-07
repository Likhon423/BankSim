#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"
#include <vector>

class CharacterObject : public GameObject {
public:
	glm::vec2 Position;
	std::vector<Texture2D> IdleAnimation;
	std::vector<Texture2D> WalkAnimation;
	int CurrentFrame;
	float FrameDuration;
	float FrameTimer;
	glm::vec3 Transform;

	CharacterObject(glm::vec2 position, std::vector<Texture2D> idleAnimation, std::vector<Texture2D> walkAnimation, float frameDuration, glm::vec3 transform = glm::vec3(1.0f));

	void Update(float dt);
	void Idle(SpriteRenderer& renderer);
	void Walk(SpriteRenderer& renderer);
};