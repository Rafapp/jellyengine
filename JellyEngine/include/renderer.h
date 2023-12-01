/*
 * RENDERER: Takes care of OpenGL rendering backend
 */

#include <camera.h>
#include <shader.h>

using namespace std;

class Renderer {
public:
	void setup();
	void draw();
	Camera* camera;
	Shader* mainShader;
} renderer;