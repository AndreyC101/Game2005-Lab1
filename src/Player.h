#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
private:
	const float SPEED = 50.0f;
	glm::vec2 m_targetPosition;

public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	
	//Movement
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void accelerateToMouse();
	void slow();
	void stop();

	//temp
	float checkDistance(GameObject* pGameObject);

	//get/set
	glm::vec2 GetTargetPosition() { return m_targetPosition; }
	void SetTargetPosition(glm::vec2 n) { m_targetPosition = n; }
};

#endif /* defined (__PLAYER__) */