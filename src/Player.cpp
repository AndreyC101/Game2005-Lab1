#include "Player.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");
	
	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;

	getRigidBody()->velocity += Util::limitMagnitude(getRigidBody()->acceleration, SPEED);

	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
	slow(); //  <---------
}

void Player::clean()
{

}

void Player::moveLeft() {
	getRigidBody()->acceleration.x -= SPEED;
}

void Player::moveRight() {
	getRigidBody()->acceleration.x += SPEED;
}

void Player::moveUp() {
	getRigidBody()->acceleration.y -= SPEED;
}

void Player::moveDown() {
	getRigidBody()->acceleration.y += SPEED;
}

void Player::accelerateToMouse()
{
	glm::vec2 mousePosition = EventManager::Instance().getMousePosition();
	if (Util::distance(getTransform()->position, mousePosition) > getHeight()) {
		SetTargetPosition(mousePosition);
		getRigidBody()->acceleration = Util::normalize(GetTargetPosition() - getTransform()->position) * SPEED;
	}
}

void Player::slow()
{
	getRigidBody()->acceleration *= 0.5f;
	getRigidBody()->velocity *= 0.8f;
}

void Player::stop()
{
	getRigidBody()->acceleration = { 0.0f, 0.0f };
	getRigidBody()->velocity = { 0.0f, 0.0f };
}

float Player::checkDistance(GameObject* pGameObject) {
	return Util::distance(getTransform()->position, pGameObject->getTransform()->position);
}
