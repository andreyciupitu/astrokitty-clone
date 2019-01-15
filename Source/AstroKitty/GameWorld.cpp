#include "GameWorld.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <AstroKitty/Geometry2D.h>
#include <AstroKitty/Transform2D.h>


GameWorld::~GameWorld()
{
	for (auto platform : platforms)
		delete platform;
	for (auto asteroid : asteroids)
		delete asteroid;
	delete astronaut;
}

void GameWorld::Init()
{
	// Camera ----------------------------------------------------------------
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Meshes ----------------------------------------------------------------
	Mesh *mesh = Geometry2D::CreateCharacter("astronaut", 50, glm::vec3(0.482, 0.109, 0.509), glm::vec3(1, 1, 0));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateRectangle("platform-start", 200, 25, glm::vec3(0.811, 0.074, 0.866));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateRectangle("platform-station", 200, 25, glm::vec3(0.262, 0.909, 0.066));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateRectangle("platform-reflection", 200, 25, glm::vec3(0.266, 0.247, 0.776));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateRectangle("platform-finish", 200, 25, glm::vec3(0.949, 0.341, 0.172));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateRectangle("border", window->GetResolution().x, 100, glm::vec3(0.266, 0.094, 0.486));
	meshes[mesh->GetMeshID()] = mesh;
	mesh = Geometry2D::CreateAsteroid("asteroid", 25, glm::vec3(0.698, 0.686, 0.643), 10);
	meshes[mesh->GetMeshID()] = mesh;

	// Character -------------------------------------------------------------
	astronaut = new Character();
	astronaut->SetPosition(glm::vec3(150, 250, 0));
	astronaut->SetOrientation(M_PI / 2);
	astronaut->SetMaxSpeed(200.0f);
	astronaut->SetMesh(meshes["astronaut"]);

	// Platforms -------------------------------------------------------------
	Platform *platform = new Platform(Platform::PLATFORMTYPE_STATION);	
	platform->SetPosition(glm::vec3(300, 450, 0));
	platform->SetMesh(meshes["platform-station"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_STATION);
	platform->SetPosition(glm::vec3(150, 250, 0));
	platform->SetScale(glm::vec3(0.5, 1, 1));
	platform->SetMesh(meshes["platform-start"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_REFLECTION);
	platform->SetPosition(glm::vec3(500, 250, 0));
	platform->SetMesh(meshes["platform-reflection"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_STATION);
	platform->SetPosition(glm::vec3(650, 450, 0));
	platform->SetMesh(meshes["platform-station"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_REFLECTION);
	platform->SetPosition(glm::vec3(900, 300, 0));
	platform->SetOrientation(M_PI / 6);
	platform->SetMesh(meshes["platform-reflection"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_STATION);
	platform->SetPosition(glm::vec3(950, 550, 0));
	platform->SetMesh(meshes["platform-station"]);
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_FINISH);
	platform->SetPosition(glm::vec3(1275, 410, 0));
	platform->SetOrientation(M_PI / 2);
	platform->SetScale(glm::vec3(2.4, 2, 1));
	platform->SetMesh(meshes["platform-finish"]);
	platforms.push_back(platform);

	// Asteroids -------------------------------------------------------------
	Asteroid *asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(400, 325, 0));
	asteroid->MakeSpawnPoint();
	asteroid->SetMaxSpeed(90.0f);
	asteroid->SetPatrolRadius(90.0f);
	asteroid->SetPatrolDirection(glm::vec3(1, 1, 0));
	asteroids.push_back(asteroid);

	asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(700, 300, 0));
	asteroid->SetRotationRadius(75);
	asteroid->SetAngularVelocity(2);
	asteroid->SetScale(glm::vec3(0.5, 0.5, 1));
	asteroid->MakeSpawnPoint();
	asteroids.push_back(asteroid);

	asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(1175, 565, 0));
	asteroid->MakeSpawnPoint();
	asteroid->SetMaxScale(2.0f);
	asteroid->SetScaleRate(2.0f);
	asteroids.push_back(asteroid);

	asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(1175, 465, 0));
	asteroid->MakeSpawnPoint();
	asteroid->SetMaxScale(2.0f);
	asteroid->SetScaleRate(2.0f);
	asteroids.push_back(asteroid);

	asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(1175, 365, 0));
	asteroid->MakeSpawnPoint();
	asteroid->SetMaxScale(2.0f);
	asteroid->SetScaleRate(2.0f);
	asteroids.push_back(asteroid);

	asteroid = new Asteroid();
	asteroid->SetMesh(meshes["asteroid"]);
	asteroid->SetPosition(glm::vec3(1175, 265, 0));
	asteroid->MakeSpawnPoint();
	asteroid->SetMaxScale(3.0f);
	asteroid->SetScaleRate(2.0f);
	asteroids.push_back(asteroid);

	// Screen borders --------------------------------------------------------
	platform = new Platform(Platform::PLATFORMTYPE_REFLECTION);
	platform->SetMesh(meshes["border"]);
	platform->SetPosition(glm::vec3(640.0f, 700.0f, 0));
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_REFLECTION);
	platform->SetMesh(meshes["border"]);
	platform->SetPosition(glm::vec3(640.0f, 50.0f, 0));
	platform->SetScale(glm::vec3(1, 2.5, 1));
	platforms.push_back(platform);

	platform = new Platform(Platform::PLATFORMTYPE_REFLECTION);
	platform->SetMesh(meshes["border"]);
	platform->SetPosition(glm::vec3(0.0f, 360.0f, 0));
	platform->SetOrientation(M_PI / 2);
	platform->SetScale(glm::vec3(0.5, 1, 1));
	platforms.push_back(platform);
}

void GameWorld::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void GameWorld::Simulate(float deltaTimeSeconds)
{
	astronaut->Update(deltaTimeSeconds);

	for (auto platform : platforms)
	{
		// Check if the character has collided with the obstacle
		glm::vec3 mtv = Geometry2D::CheckCollision(astronaut, platform);

		if (glm::length(mtv) > 0)
		{
			// Correct the position in case of collision
			astronaut->SetPosition(astronaut->GetPosition() + mtv);

			// Apply game logic in case of collision
			astronaut->OnCollision(platform, glm::normalize(mtv));
		}
	}

	for (auto asteroid : asteroids)
	{
		if (!asteroid->IsDestroyed())
		{
			asteroid->Update(deltaTimeSeconds);

			// Check if the character has collided with the obstacle
			glm::vec3 mtv = Geometry2D::CheckCollision(astronaut, asteroid);

			if (glm::length(mtv) > 0)
			{
				// Correct the position in case of collision
				astronaut->SetPosition(astronaut->GetPosition() + mtv);

				// Apply game logic in case of collision
				astronaut->OnCollision(asteroid, glm::normalize(mtv));

				// Destroy the asteroid so it doesn't get rendered & checked again
				asteroid->SetDestroyed(true);
			}
		}
	}
}

void GameWorld::Update(float deltaTimeSeconds)
{
	// Update the positions of all objects and check for collisions
	Simulate(deltaTimeSeconds);

	// Render the character
	glm::vec3 charPosition = astronaut->GetPosition();
	float charRotation = astronaut->GetOrientation();
	RenderMesh2D(astronaut->GetMesh(), shaders["VertexColor"], astronaut->GetModelMatrix());
	
	// Render the obstacles in the scene
	for (auto obstacle : platforms)
		RenderMesh2D(obstacle->GetMesh(), shaders["VertexColor"], obstacle->GetModelMatrix());
	for (auto obstacle : asteroids)
		if (!obstacle->IsDestroyed())
			RenderMesh2D(obstacle->GetMesh(), shaders["VertexColor"], obstacle->GetModelMatrix());
}

void GameWorld::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !(astronaut->IsMoving()))
		astronaut->Seek(glm::vec3(mouseX, window->GetResolution().y - mouseY, 0));
}