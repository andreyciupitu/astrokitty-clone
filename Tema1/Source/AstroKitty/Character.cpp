#include "Character.h"

#include <AstroKitty/Geometry2D.h>
#include <AstroKitty/Platform.h>
#include <AstroKitty/SpatialObject.h>

Character::Character()
{
	maxSpeed = 0.0f;
	angularVelocity = 0.0f;
	aligning = false;
	moving = false;
	angularVelocity = 0.0f;
	velocity = glm::vec3(0, 0, 0);
	targetOrientation = 0.0f;
}

void Character::Update(float deltaTimeSeconds)
{
	// Update orientation and position
	orientation += angularVelocity * deltaTimeSeconds;
	currentPos += velocity * deltaTimeSeconds;

	// Keep the orientation in (-PI, PI)
	if (orientation > M_PI)
		orientation -= 2 * M_PI;
	if (orientation < -1 * M_PI)
		orientation += 2 * M_PI;
}

void Character::Seek(const glm::vec3 &target)
{
	glm::vec3 direction = target - currentPos;
	Align(direction);
	float distance = glm::distance(target, currentPos);
	velocity = direction / distance * maxSpeed;
	moving = true;
}

void Character::Align(const glm::vec3 &direction)
{
	orientation = atan2(direction.y, direction.x);
}

bool Character::IsMoving()
{
	return moving;
}

glm::vec3 Character::GetVelocity()
{
	return velocity;
}

void Character::SetVelocity(glm::vec3 v)
{
	velocity = v;
}

float Character::GetMaxSpeed()
{
	return maxSpeed;
}

void Character::SetMaxSpeed(float speed)
{
	maxSpeed = speed;
}

float Character::GetMaxAnglarSpeed()
{
	return maxAngularSpeed;
}

void Character::SetMaxAngularSpeed(float speed)
{
	maxAngularSpeed = speed;
}

void Character::OnCollision(SpatialObject *o, glm::vec3 collisionNormal)
{
	velocity = glm::vec3(0);
	moving = false;
	aligning = false;
}

void Character::OnCollision(Platform *platform, glm::vec3 collisionNormal)
{
	switch (platform->GetType())
	{
	case Platform::PLATFORMTYPE_STATION:
		if (glm::dot(velocity, collisionNormal) < 0) // prevent getting stuck at high angular speeds
		{
			Align(collisionNormal);
			moving = false;
			velocity = collisionNormal * -9.81f * 10.0f; // Simulate gravity
		}
		break;
	case Platform::PLATFORMTYPE_REFLECTION:
		if (glm::dot(velocity, collisionNormal) <= 0) // prevent re-reflection if angular speed is really high
		{
			velocity = glm::reflect(velocity, collisionNormal);
			Align(velocity);
		}
		break;
	case Platform::PLATFORMTYPE_FINISH:
		velocity = collisionNormal * -9.81f * 10.0f; // Simulate gravity
		Align(collisionNormal);
		break;
	}
}

void Character::OnCollision(Asteroid *asteroid, glm::vec3 collisionNormal)
{
	if (glm::dot(velocity, collisionNormal) <= 0) // prevent re-reflection if angular speed is really high
	{
		velocity = glm::reflect(velocity, collisionNormal);
		Align(velocity);
	}
}