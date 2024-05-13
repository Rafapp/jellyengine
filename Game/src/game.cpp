#include <iostream>

#include <jellyEngine.h>
#include <input.h>

#include "game.h"

class Game : Engine {
public:
	//Mesh m;
	// Start is called on the first frame
	void Start() 
	{
		Renderer::camera->LookAt = glm::vec3(0.0);
		Renderer::camera->Position = glm::vec3(8.0, 0.25, 0);
		Renderer::camera->type = STATIC;

		std::cout << "Game initialized" << std::endl;

		// Create a light
		light = new Model(RESOURCES_PATH "3D/cube.obj");
		light->p = glm::vec3(0, 5, 0);
		light->color = glm::vec3(1.0f, 1.0f, 1.0f);
		light->s = glm::vec3(0.125f, 0.125f, 0.125f);


		// Create a ground plane
		plane = new Model(RESOURCES_PATH "3D/plane.obj");
		plane->color = glm::vec3(0.0f, 0.0f, 1.0f);
		plane->p = glm::vec3(0.0f, -0.0f, 0.0f);
		plane->s = glm::vec3(5.0f, -1.0f, 5.0f);
		scene.push_back(plane);

		// Create soft body with cube model
		softBody = new SoftBody(RESOURCES_PATH "3D/cube.obj", 0.9, 1.0, 0.1, 0.99);
		softBody->color = glm::vec3(0.0, 1.0, 0.0);
		softBody->p = glm::vec3(0, 2.0, 0.0);
		softBody->s = glm::vec3(0.5);
		scene.push_back(softBody);
	}

	// Update is called every frame
	bool rPress = false;
	void Update(float dt) 
	{
		// Additive time function
		static float t = 0;
		t += dt;

		// Make camera and light loop around using time and sin, cos
		light->p = glm::vec3(glm::cos(t/2) * 2.5, 1, glm::sin(t/2) * 2.5);
		Renderer::camera->Position = glm::vec3(glm::cos(t/2) * 7.5, 5, glm::sin(t/2) * 7.5);

		softBody->AddForce(glm::vec3(0.0, -9.81, 0.0));
		softBody->Update(dt);

		if (keyPressed("r") && !rPress) {
			softBody->Reset();
			rPress = true;
		}
		if (keyReleased("r")) rPress = false;
	}

	// Exit is called before the game closes
	void Exit() 
	{
		std::cout << "Exiting game" << std::endl;
	}
};

int main() {
	Engine::InitializeEngine<Game>();
}