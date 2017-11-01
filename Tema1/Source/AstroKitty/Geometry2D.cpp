#include "Geometry2D.h"

#include <string>

#include <Core/Engine.h>

namespace Geometry2D
{
	Mesh* CreateRectangle(std::string name, float length1, float length2, glm::vec3 color)
	{
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(-1 * length1 / 2, -1 * length2 / 2, 0), color),
			VertexFormat(glm::vec3(length1 / 2, -1 * length2 / 2, 0), color),
			VertexFormat(glm::vec3(length1 / 2, length2 / 2, 0), color),
			VertexFormat(glm::vec3(-1 * length1 / 2, length2 / 2, 0), color)
		};

		Mesh* rectangle = new Mesh(name);
		std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };
		
		rectangle->InitFromData(vertices, indices);
		return rectangle;
	}

	Mesh* CreateCharacter(std::string name, float length, glm::vec3 color, glm::vec3 tipColor)
	{
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(-1 * length * sqrt(3.0f) / 6, -1 * length / 2, 0), color),
			VertexFormat(glm::vec3(length * sqrt(3.0f) / 3, 0, 0), tipColor),
			VertexFormat(glm::vec3(-1 * length * sqrt(3.0f) / 6, length / 2, 0), color)
		};

		Mesh* triangle = new Mesh(name);
		std::vector<unsigned short> indices = { 0, 1, 2 };
		
		triangle->InitFromData(vertices, indices);
		return triangle;
	}

	Mesh* CreateAsteroid(std::string name, float radius, glm::vec3 color, int verticesCount)
	{
		std::vector<VertexFormat> vertices;

		for (int i = 0; i < verticesCount; i++)
		{
			float x = radius * cos(2 * M_PI * i / verticesCount);
			float y = radius * sin(2 * M_PI * i / verticesCount);
			vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		}

		Mesh* asteroid = new Mesh(name);
		std::vector<unsigned short> indices;

		for (int i = 2; i < verticesCount; i++)
		{
			indices.push_back(0);
			indices.push_back(i - 1);
			indices.push_back(i);
		}

		asteroid->InitFromData(vertices, indices);
		return asteroid;
	}

	glm::vec3 CheckCollision(SpatialObject* o1, SpatialObject* o2)
	{
		std::vector<glm::vec3> updatedVertices1;
		std::vector<glm::vec3> updatedVertices2;
		std::vector<glm::vec3> normals;
		
		// Compute vertex positions in Global Space
		glm::mat3 modelMatrix = o1->GetModelMatrix();
		for (auto vertex : o1->GetMesh()->vertices)
		{
			vertex.position.z = 1; // Homogeneous coordinates
			updatedVertices1.push_back(modelMatrix * vertex.position);
		}

		modelMatrix = o2->GetModelMatrix();
		for (auto vertex : o2->GetMesh()->vertices)
		{
			vertex.position.z = 1; // Homogeneous coordinates
			updatedVertices2.push_back(modelMatrix * vertex.position);
		}

		// Find the outward normal for each edge of the polygons
		int previousIndex = updatedVertices1.size() - 1;
		for (int i = 0; i < updatedVertices1.size(); i++)
		{
			glm::vec3 edge = updatedVertices1[i] - updatedVertices1[previousIndex];
			normals.push_back(glm::vec3(edge.y, -1 * edge.x, edge.z));
			previousIndex = i;
		}
		
		previousIndex = updatedVertices2.size() - 1;
		for (int i = 0; i < updatedVertices2.size(); i++)
		{
			glm::vec3 edge = updatedVertices2[i] - updatedVertices2[previousIndex];
			normals.push_back(glm::vec3(edge.y, -1 * edge.x, edge.z));
			previousIndex = i;
		}

		glm::vec3 mtv;
		float offset = (float)INT_MAX;

		// Project the vertexes on each normal to test for intersections
		for (auto normal : normals)
		{
			Projection p1 = ProjectObjectOnAxis(updatedVertices1, normal);
			Projection p2 = ProjectObjectOnAxis(updatedVertices2, normal);

			// If there's a gap we can stop -> NO COLLISION
			if (p1.right < p2.left || p2.right < p1.left)
				return glm::vec3(0);

			// Remember the smallest intersection
			if (fabs(p1.right - p2.left) < offset)
			{
				offset = fabs(p1.right - p2.left);
				mtv = p1.axis; 
			}
			if (fabs(p2.right - p1.left) < offset)
			{
				offset = fabs(p2.right - p1.left);
				mtv = p1.axis;
			}
		}

		// We want to move only the first object
		if (glm::dot(mtv, o2->GetPosition() - o1->GetPosition()) >= 0)
			mtv *= -1;
		return mtv * offset;
	}

	Projection ProjectObjectOnAxis(const std::vector<glm::vec3> &vertices, const glm::vec3 &axis)
	{
		Projection p;
		p.axis = glm::normalize(axis);
		p.left = (float)INT_MAX;
		p.right = (float)INT_MIN;
		for (auto vertexPos : vertices)
		{
			float proj = glm::dot(p.axis, vertexPos);
			if (proj < p.left)
				p.left = proj;
			if (proj > p.right)
				p.right = proj;
		}
		return p;
	}

} // namespace Geometry2D
