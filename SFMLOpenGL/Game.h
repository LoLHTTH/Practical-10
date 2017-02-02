#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector.h>
#include <Matrix.h>

#include <Vector3.h>
#include <Matrix3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <fstream>

using namespace std;
using namespace sf;
using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	string readShader();
	string readFragment();
	void translate();
	void applyMatrix(Matrix matrix);
	void rotate(Matrix matrixRotation);

	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};

#endif