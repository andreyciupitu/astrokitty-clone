#include "Asteroid.h"

#include <Core/Engine.h>

Asteroid::Asteroid() 
	: rotationRadius(0.0f), angularVelocity(0.0f), scaleRate(0.0f)
	, maxSpeed(0.0f), patrolRadius(0.0f), maxScale(1.0f)
	, rotation(0.0f), spawnPoint(glm::vec3(0)), patrolDirection(glm::vec3(0))
	, destroyed(false)
{
}

void Asteroid::Update(float deltaTimeSeconds)
{
	// Calculate the new orientation or rotation of the asteroid
	if (rotationRadius == 0)
	{
		orientation += angularVelocity * deltaTimeSeconds;

		// Calculate the next position
		currentPos += patrolDirection * maxSpeed * deltaTimeSeconds;
		// Go back if we reached the end of the patrol zone
		if (glm::length(currentPos - spawnPoint - patrolDirection * patrolRadius) < maxSpeed * 10/ patrolRadius)
			patrolDirection *= -1;
	}
	else
	{
		rotation += angularVelocity * deltaTimeSeconds;

		// If it's rotating against a point calculate the new position
		currentPos = spawnPoint + glm::vec3(cos(rotation), sin(rotation), 0) * rotationRadius;
	}

	// Scale the asteroid uniformly along OX and OY, revert when we reached the maxScale
	scale += glm::vec3(scaleRate, scaleRate, 0) * deltaTimeSeconds;
	if (glm::length(scale - glm::vec3(maxScale * scaleRate/fabs(scaleRate), maxScale * scaleRate/fabs(scaleRate), 1)) < 0.1)
		scaleRate *= -1;
}

void Asteroid::MakeSpawnPoint()
{
	spawnPoint = currentPos;
}

bool Asteroid::IsDestroyed()
{
	return destroyed;
}

void Asteroid::SetDestroyed(bool val)
{
	destroyed = val;
}

float Asteroid::GetAngularVelocity()
{
	return angularVelocity;
}

void Asteroid::SetAngularVelocity(float w)
{
	angularVelocity = w;
}

float Asteroid::GetRotationRadius()
{
	return rotationRadius;
}

void Asteroid::SetRotationRadius(float r)
{
	rotationRadius = r;
}

float Asteroid::GetMaxSpeed()
{
	return maxSpeed;
}

void Asteroid::SetMaxSpeed(float s)
{
	maxSpeed = s;
}

float Asteroid::GetMaxScale()
{
	return maxScale;
}

void Asteroid::SetMaxScale(float val)
{
	maxScale = val;
}

float Asteroid::GetPatrolRadius()
{
	return patrolRadius;
}

void Asteroid::SetPatrolRadius(float val)
{
	patrolRadius = val;
}

glm::vec3 Asteroid::GetPatrolDirection()
{
	return patrolDirection;
}

void Asteroid::SetPatrolDirection(const glm::vec3 &d)
{
	patrolDirection = d;
}

float Asteroid::GetScaleRate()
{
	return scaleRate;
}

void Asteroid::SetScaleRate(float val)
{
	scaleRate = val;
}

float Asteroid::GetRotation()
{
	return rotation;
}
