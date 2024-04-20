#include <iostream>

#include "game.h"

class Game : Engine {
public:
	//Mesh m;
	void Start() 
	{
		std::cout << "Game initialized" << std::endl;
	}

	void Update(float dt) 
	{
		std::cout << "Running update: " << dt << std::endl;
	}

	void Draw() 
	{
		//m.draw();
	}

	void Exit() 
	{
		std::cout << "Exiting game" << std::endl;
	}
};

int main() {
	Engine::InitializeEngine<Game>();
}