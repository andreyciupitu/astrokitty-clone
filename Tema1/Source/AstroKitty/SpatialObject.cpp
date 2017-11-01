#include "AstroKitty/SpatialObject.h"

#include <Core/Engine.h>

glm::mat3 SpatialObject::GetModelMatrix()
{
	glm::mat3 modelMatrix(1);
	modelMatrix *= Transform2D::Translate(currentPos);
	modelMatrix *= Transform2D::Rotate(orientation);
	modelMatrix *= Transform2D::Scale(scale);

	return modelMatrix;
}

glm::vec3 SpatialObject::GetPosition()
{
	return currentPos;
}

void SpatialObject::SetPosition(const glm::vec3 &position)
{
	currentPos = position;
}

float SpatialObject::GetOrientation()
{
	return orientation;
}

void SpatialObject::SetOrientation(float radians)
{
	orientation = radians;
}

glm::vec3 SpatialObject::GetScale()
{
	return scale;
}

void SpatialObject::SetScale(const glm::vec3 &scaleFactor)
{
	scale = scaleFactor;
}

void SpatialObject::SetMesh(Mesh *mesh)
{
	this->mesh = mesh;
}

Mesh* SpatialObject::GetMesh()
{
	return mesh;
}