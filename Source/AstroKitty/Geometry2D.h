#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <AstroKitty/SpatialObject.h>

#define FLOAT_EPS 0.01f

namespace Geometry2D
{
	struct Projection
	{
		float left, right;
		glm::vec3 axis;
	};

	// Creates a rectangle centered in the origin of the system.
	// @param name - the name of the new mesh
	// @param length1, length2 - lengths of the sides of the rectangle
	// @param color - the color of the rectangle
	// @param fill - whether the rectangle should be filled with color
	Mesh* CreateRectangle(std::string name, float length1, float length2, glm::vec3 color);

	// Creates a triangle centered in the origin of the system.
	// @param name - the name of the new mesh
	// @param length - length of the side of the triangle
	// @param color - the color of the triangle
	// @param tipColor - the color of the "head" of the triangle
	Mesh* CreateCharacter(std::string name, float length, glm::vec3 color, glm::vec3 tipColor);

	// Creates a mesh for an asteroid(polygon with n vertices)
	// @param name - the name of the mesh
	// @param radius - radius of the asteroid
	// @param color - the color of the asteroid
	// @param verticesCount - the number of vertices to be used
	Mesh* CreateAsteroid(std::string name, float radius, glm::vec3 color, int verticesCount);

	// Collision Detection using SAT algorithm.
	// The algorithm projects the vertices of both objects on the same axis
	// and checks for intersections.
	glm::vec3 CheckCollision(SpatialObject* o1, SpatialObject* o2);

	// Projects an object specified by the given vertices on an axis, returns the versor of the axis
	// and the extremities of the projection.
	// @param vertices - the positions of the vertices of the object
	// @param axis - the axis to project on
	Projection ProjectObjectOnAxis(const std::vector<glm::vec3> &vertices, const glm::vec3 &axis);

} // namespace Geometry2D