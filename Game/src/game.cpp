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
		std::cout << "Game initialized" << std::endl;
		light = new Model(RESOURCES_PATH "3D/cube.obj");
		light->p = glm::vec3(0, 5, 0);
		light->color = glm::vec3(1.0f, 1.0f, 1.0f);
		light->s = glm::vec3(0.125f, 0.125f, 0.125f);

		plane = new Model(RESOURCES_PATH "3D/plane.obj");
		plane->color = glm::vec3(0.0f, 0.0f, 1.0f);
		plane->p = glm::vec3(0.0f, -0.25f, 0.0f);
		plane->s = glm::vec3(5.0f, -1.0f, 5.0f);
		scene.push_back(plane);

		dragon = new Model(RESOURCES_PATH "3D/cube.obj");
		dragon->color = glm::vec3(1.0f, 0.0f, 0.0f);
		dragon->p = glm::vec3(2.5, 1.0, 0.0);
		dragon->s = glm::vec3(1.0f);
		scene.push_back(dragon);

		dragon2 = new Model(RESOURCES_PATH "3D/cube.obj");
		dragon2->color = glm::vec3(0.0f, 1.0f, 0.0f);
		dragon2->p = glm::vec3(0.0, 1.0, 0.0);
		dragon2->s = glm::vec3(1.0f);
		scene.push_back(dragon2);

		dragon3 = new Model(RESOURCES_PATH "3D/cube.obj");
		dragon3->color = glm::vec3(0.0f, 0.0f, 1.0f);
		dragon3->p = glm::vec3(-2.5, 1.0, 0.0);
		dragon3->s = glm::vec3(1.0f);
		scene.push_back(dragon3);
	}

	// Update is called every frame
	void Update(float dt) 
	{
		dragon->r += glm::vec3(0,0.5,0);
		dragon2->r += glm::vec3(0,0.5,0);
		dragon3->r += glm::vec3(0,0.5,0);
		static float t = 0;
		t += dt;
		light->p = glm::vec3(glm::cos(t), 1, glm::sin(t));
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