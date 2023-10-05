#include "character_object.h"

CharacterObject::CharacterObject(glm::vec2 position, std::vector<Texture2D> idleTextures, std::vector<Texture2D> walkTextures, float frameDuration)
	: Position(position), IdleAnimation(idleTextures), WalkAnimation(walkTextures), CurrentFrame(0), FrameDuration(frameDuration), FrameTimer(0.0f) {}

void CharacterObject::Update(float dt) {
	FrameTimer += dt;
	if (FrameTimer >= FrameDuration) {
		CurrentFrame++;
		FrameTimer = 0.0f;
	}
}

void CharacterObject::Idle(SpriteRenderer& renderer)
{
	if (CurrentFrame >= 6) {
		CurrentFrame = 0;
	}

	renderer.DrawSprite(this->IdleAnimation[CurrentFrame], this->Position, glm::vec2(300.0f, 300.0f), this->Rotation);
}

void CharacterObject::Walk(SpriteRenderer& renderer)
{
	if (CurrentFrame >= 8) {
		CurrentFrame = 0;
	}
	renderer.DrawSprite(this->WalkAnimation[CurrentFrame], this->Position, glm::vec2(300.0f, 300.0f), this->Rotation);
}