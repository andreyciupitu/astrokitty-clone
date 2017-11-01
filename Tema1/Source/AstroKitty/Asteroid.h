#pragma once

#include <AstroKitty/SpatialObject.h>
#include <Core/Engine.h>

class Asteroid : public SpatialObject
{
public:
	Asteroid();
	virtual ~Asteroid() {};

	virtual void Update(float deltaTimeSeconds) override;

	// Sets the current position as spawn point(pivot for patrol and rotation)
	void MakeSpawnPoint();

	bool Asteroid::IsDestroyed();
	void Asteroid::SetDestroyed(bool val);

	float GetAngularVelocity();
	void SetAngularVelocity(float w);

	float GetRotationRadius();
	void SetRotationRadius(float r);

	float GetMaxSpeed();
	void SetMaxSpeed(float s);

	float GetMaxScale();
	void SetMaxScale(float val);

	float GetPatrolRadius();
	void SetPatrolRadius(float val);

	glm::vec3 GetPatrolDirection();
	void SetPatrolDirection(const glm::vec3 &d);

	float GetScaleRate();
	void SetScaleRate(float val);

	float GetRotation();

private:
	glm::vec3 spawnPoint;
	glm::vec3 patrolDirection;
	float maxSpeed;
	float patrolRadius;
	float angularVelocity;
	float rotationRadius;
	float rotation;
	float maxScale;
	float scaleRate;
	bool destroyed;
};