#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	// @param translate - vector containing the translations on each axis
	inline glm::mat3 Translate(const glm::vec3 &translate)
	{
		return glm::mat3(
			1, 0, 0,
			0, 1, 0,
			translate.x, translate.y, 1);
	}

	// Scale matrix
	// @param scale - vector containing the scale factors for each axis
	inline glm::mat3 Scale(const glm::vec3 &scale)
	{
		return glm::mat3(
			scale.x, 0, 0,
			0, scale.y, 0,
			0, 0, 1);
	}

	// Rotate matrix
	// @param radians - angle of rotation
	inline glm::mat3 Rotate(float radians)
	{
		return glm::mat3(
			cos(radians), sin(radians), 0,
			-1 * sin(radians), cos(radians), 0,
			0, 0, 1);
	}

} // namespace Transform2D

