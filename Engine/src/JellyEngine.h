#pragma once

#include<iostream>

namespace Renderer {
	void Setup();
}

class Engine {
public:
	template<typename Game>
	static void InitializeEngine() {
		std::cout << "Engine initialized" << std::endl;
		Renderer::Setup();
		Game game;
		game.Start();

		std::cout << "Press any key to continue...";
		std::cin.get();
		int i = 0;
		while (true) {
			float dt = 0;
			game.Update(dt);
			game.Draw();
			i++;
			if (i > 10) break;
		}
		game.Exit();
	}
	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit() = 0;
	virtual void Draw() = 0;
};


