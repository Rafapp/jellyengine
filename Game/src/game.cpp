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
		Renderer::camera->Position = glm::vec3(15, 5, 0);
		Renderer::camera->type = STATIC;

		std::cout << "Game initialized" << std::endl;

		// Create a light
		light = new Model(RESOURCES_PATH "3D/cube.obj");
		light->p = glm::vec3(0, 5, 0);
		light->color = glm::vec3(1.0f, 1.0f, 1.0f);
		light->s = glm::vec3(0.25, 0.25, 0.25);

		// Create a ground plane
		bottomPlane = new Model(RESOURCES_PATH "3D/plane.obj");
		bottomPlane->color = glm::vec3(1.0, 1.0, 1.0);
		bottomPlane->p = glm::vec3(0.0f, -0.0f, 0.0f);
		bottomPlane->s = glm::vec3(10.0, -1.0, 10.0);
		scene.push_back(bottomPlane);

		// Create a back plane
		backPlane = new Model(RESOURCES_PATH "3D/plane.obj");
		backPlane->color = glm::vec3(1.0, 1.0, 1.0);
		backPlane->p = glm::vec3(-10.0f, 5.0f, 0.0f);
		backPlane->r = glm::vec3(0.0f, 0.0, 90.0);
		backPlane->s = glm::vec3(10.0, -1.0, 10.0);
		scene.push_back(backPlane);

		// Create a left plane
		leftPlane = new Model(RESOURCES_PATH "3D/plane.obj");
		leftPlane->color = glm::vec3(1.0, 0.0, 0.0);
		leftPlane->p = glm::vec3(0.0, 5.0, 10.0);
		leftPlane->r = glm::vec3(90.0f, 0.0, 0.0);
		leftPlane->s = glm::vec3(10.0, -1.0, 10.0);
		scene.push_back(leftPlane);

		// Create a right plane
		rightPlane = new Model(RESOURCES_PATH "3D/plane.obj");
		rightPlane->color = glm::vec3(0.0, 1.0, 0.0);
		rightPlane->p = glm::vec3(0.0, 5.0, -10.0);
		rightPlane->r = glm::vec3(90.0f, 0.0, 0.0);
		rightPlane->s = glm::vec3(10.0, -1.0, 10.0);
		scene.push_back(rightPlane);

		// Create soft body with cube model
		// std::string path, float restitution, float mass, float stiffness, float damping
		softBody = new SoftBody(RESOURCES_PATH "3D/fun/cube.obj", 0.5, 1, 5, 0.1);
		softBody->color = glm::vec3(0.0, 1.0, 0.0);
		softBody->p = glm::vec3(0, 2.0, 0.0);
		softBody->s = glm::vec3(1);
		scene.push_back(softBody); 
	}

	// Update is called every frame
	bool rPress = false;
	bool spacePress = false;
	bool tPress = false;
	int object = 0;
	vector<std::string> objectPaths = {
		RESOURCES_PATH "3D/fun/cube.obj",
		RESOURCES_PATH "3D/fun/diamond.obj",
		RESOURCES_PATH "3D/fun/star.obj",
		RESOURCES_PATH "3D/fun/donut.obj",
		RESOURCES_PATH "3D/fun/acrobat.obj"
	};

	void Update(float dt) 
	{
		// Additive time function
		static float t = 0;
		t += dt;

		// Make camera and light loop around using time and sin, cos
		light->p = glm::vec3(glm::cos(t/2) * 3.5, 1, glm::sin(t/2) * 3.5);
		//Renderer::camera->Position = glm::vec3(glm::cos(t/2) * 7.5, 5, glm::sin(t/2) * 7.5);

		softBody->AddForce(glm::vec3(0.0, -9.81, 0.0));
		softBody->Update(dt);

		// 'r' to reset
		if (keyPressed("r") && !rPress) {
			softBody->Reset();
			rPress = true;
		}
		if (keyReleased("r")) rPress = false;

		// 'space' to jump
		if (keyPressed("space") && !spacePress) {
			softBody->AddForce(glm::vec3(0, 250, 0));
			spacePress = true;
		}
		if (keyReleased("space")) spacePress = false;

		// 't' to change to the next model
		if (keyPressed("t") && !tPress) {
			object++;
			object %= 5;

			delete softBody;

			// Cube
			if (object == 0) {
				softBody = new SoftBody(objectPaths[object], 0.0, 1, 5, 0.1);
				softBody->color = glm::vec3(0.0, 1.0, 0.0);
				softBody->p = glm::vec3(0, 2.0, 0.0);
				softBody->s = glm::vec3(1.5);
			} 
			// Diamond
			else if (object == 1) {
				softBody = new SoftBody(objectPaths[object], 0.0, 1, 5, 0.1);
				softBody->color = glm::vec3(0.0, 1.0, 1.0);
				softBody->p = glm::vec3(0, 2.0, 0.0);
				softBody->s = glm::vec3(2);
			} 
			// Star
			else if (object == 2) {
				softBody = new SoftBody(objectPaths[object], 0.0, 1, 5, 0.1);
				softBody->color = glm::vec3(1.0, 1.0, 0.0);
				softBody->p = glm::vec3(0, 2.0, 0.0);
				softBody->s = glm::vec3(2);
			} 
			// Donut
			else if (object == 3) {
				softBody = new SoftBody(objectPaths[object], 0.0, 1, 5, 0.1);
				softBody->color = glm::vec3(1, 0, 1);
				softBody->p = glm::vec3(0, 2.0, 0.0);
				softBody->s = glm::vec3(1.5);
			} 
			// Acrobat
			else if (object == 4) {
				softBody = new SoftBody(objectPaths[object], 0.0, .5, 2.5, 0.1);
				softBody->color = glm::vec3(1, 0.75, 0.0);
				softBody->p = glm::vec3(0, 2.0, 0.0);
				softBody->s = glm::vec3(0.3);
			}

			scene.pop_back();
			scene.push_back(softBody);

			tPress = true;
		}
		if (keyReleased("t")) tPress = false;

		// 'wasd' to move
		if(keyPressed("w")) softBody->AddForce(glm::vec3(-7.5, 0, 0));
		if(keyPressed("s")) softBody->AddForce(glm::vec3(7.5, 0, 0));
		if(keyPressed("a")) softBody->AddForce(glm::vec3(0, 0, 7.5));
		if(keyPressed("d")) softBody->AddForce(glm::vec3(0, 0, -7.5));
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