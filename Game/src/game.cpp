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
	}

	// Update is called every frame
	void Update(float dt) 
	{
		std::cout << mouseX << ", " << mouseY << std::endl;
	}

	void Draw() 
	{
		//m.draw();
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