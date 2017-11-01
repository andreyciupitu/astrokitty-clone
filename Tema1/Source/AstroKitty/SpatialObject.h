#pragma once

#include <Core/Engine.h>
#include <AstroKitty/Transform2D.h>

class SpatialObject
{
public:
	SpatialObject() : currentPos(glm::vec3(0, 0, 0)), orientation(0.0f), scale(glm::vec3(1, 1, 1)) {}
	virtual ~SpatialObject() {};

	// Update the parameters of the object between frames.
	virtual void Update(float deltaTimeSeconds) = 0;

	// Generate a modelMatrix rotating and scaling form the origin.
	// Override for a more complex behavior or for non-centered meshes.
	virtual glm::mat3 GetModelMatrix();

	glm::vec3 GetPosition();
	void SetPosition(const glm::vec3 &position);

	float GetOrientation();
	void SetOrientation(float radians);

	glm::vec3 GetScale();
	void SetScale(const glm::vec3 &scaleFactor);

	void SetMesh(Mesh *mesh);
	Mesh* GetMesh();

protected:
	Mesh *mesh;
	glm::vec3 currentPos;
	float orientation;
	glm::vec3 scale;
};