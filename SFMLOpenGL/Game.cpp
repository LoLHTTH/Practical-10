#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "minecraft.tga";
//const string filename = "cube.tga";

const string filename = "texture.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;
Matrix matrixRotateX;
Matrix matrixRotateY;
Matrix matrixRotateZ;

Matrix matrixRotation;
Matrix matrixScale;
float angle = 0.5f;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	matrixRotateX = matrixRotateX.rotationX(angle);
	matrixRotateY = matrixRotateY.rotationY(angle);
	matrixRotateZ = matrixRotateZ.rotationZ(angle);
	matrixRotation = matrixRotation.rotation(angle);
	matrixScale = matrixScale.scale(100.5f, 100.5f);

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */
	// FRONT FACE

	// Left Bottom
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = 0.0f;

	// Right Bottom
	vertex[1].coordinate[0] = 0.5f;
	vertex[1].coordinate[1] = -0.5f;
	vertex[1].coordinate[2] = 0.0f;

	// Top Left
	vertex[2].coordinate[0] = -0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.0f;

	// Top Right
	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = 0.0f;

	// BACK FACE

	// Left Bottom
	vertex[4].coordinate[0] = -0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = -1.0f;

	// Right Bottom
	vertex[5].coordinate[0] = 0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = -1.0f;

	// Top Left
	vertex[6].coordinate[0] = -0.5f;
	vertex[6].coordinate[1] = 0.5f;
	vertex[6].coordinate[2] = -1.0f;

	// Top Right
	vertex[7].coordinate[0] = 0.5f;
	vertex[7].coordinate[1] = 0.5f;
	vertex[7].coordinate[2] = -1.0f;

	//vertex[0].texel[0] = 0.5f;
	//vertex[0].texel[1] = 0.5f;

	//vertex[1].texel[0] = 1.0f;
	//vertex[1].texel[1] = 1.0f;

	//vertex[2].texel[0] = 1.0f;
	//vertex[2].texel[1] = 0.0f;

	vertex[3].texel[0] = 0.5f;

	/*Index of Poly / Triangle to Draw */
	//DRAWING TRIAGNLES 

	//FRONT
	triangles[0] = 3;   triangles[1] = 2;   triangles[2] = 0; // TRIANGLE 1
	triangles[3] = 3;   triangles[4] = 0;   triangles[5] = 1; // TRIANGLE 2

	//BACK
	triangles[30] = 6;   triangles[31] = 7;   triangles[32] = 5; // TRIANGLE 3
	triangles[33] = 6;   triangles[34] = 5;   triangles[35] = 4; // TRIANGLE 4

	//LEFT SIDE
	triangles[6] = 2;   triangles[7] = 6;   triangles[8] = 4; // TRIANGLE 5
	triangles[9] = 2;   triangles[10] = 4;   triangles[11] = 0; // TRIANGLE 6

	//RIGHT SIDE
	triangles[12] = 7;   triangles[13] = 3;   triangles[14] = 1; // TRIANGLE 7
	triangles[15] = 7;   triangles[16] = 1;   triangles[17] = 5; // TRIANGLE 8

	//TOP SIDE
	triangles[18] = 7;   triangles[19] = 6;   triangles[20] = 2; // TRIANGLE 9
	triangles[21] = 7;   triangles[22] = 2;   triangles[23] = 3; // TRIANGLE 10

	//BOT SIDE
	triangles[24] = 1;   triangles[25] = 0;   triangles[26] = 4; // TRIANGLE 11
	triangles[27] = 1;   triangles[28] = 4;   triangles[29] = 5; // TRIANGLE 12

	//glEnable(GL_CULL_FACE); // To cull the faces

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	string shader = readShader();
	const char* vs_src = shader.c_str();

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	string fragment = readFragment();
	const char* fs_src = fragment.c_str();

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::X))
	{
		rotate(matrixRotateX);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Y))
	{
		rotate(matrixRotateY);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Z))
	{
		rotate(matrixRotateZ);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Space))
	{
		applyMatrix(matrixRotation);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::S))
	{
		applyMatrix(matrixScale);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::T))
	{
		translate();
	}

	//Change vertex data
	if (sf::Keyboard::isKeyPressed(Keyboard::I))
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				vertex[i].coordinate[j] += -0.0001f;
			}
		}
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}
string Game::readShader()
{
	string line;
	ifstream myfile("../shaders.txt");
	string shader;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			shader += line + '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return shader;
}
string Game::readFragment()
{
	string line;
	ifstream myfile("../fragment.txt");
	string fragment;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fragment += line + '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return fragment;
}
void Game::translate()
{
	Matrix matrixTranslate = matrixTranslate.translate(0.005f, 0);
	Vector vec[8];

	for (int i = 0; i < 8; i++)
	{
		vec[i] = Vector(vertex[i].coordinate[0], vertex[i].coordinate[1], 1);
		vec[i] = matrixTranslate * vec[i];
		vertex[i].coordinate[0] = vec[i].x();
		vertex[i].coordinate[1] = vec[i].y();
	}
}
void Game::applyMatrix(Matrix matrix)
{
	Vector vec[8];
	for (int i = 0; i < 8; i++)
	{
		vec[i] = Vector(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);
		vec[i] = matrix * vec[i];
		vertex[i].coordinate[0] = vec[i].x();
		vertex[i].coordinate[1] = vec[i].y();
		vertex[i].coordinate[2] = vec[i].z();
	}
}
void Game::rotate(Matrix matrix)
{
	Vector vec[8];
	//Matrix matrixTrans;
	for (int i = 0; i < 8; i++)
	{
		//matrixTrans = matrixTrans.translate(-vertex[i].coordinate[0], -vertex[i].coordinate[1]);
		vec[i] = Vector(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

		//vec[i] = matrixTrans * vec[i];
		vec[i] = matrix * vec[i];

		//matrixTrans = matrixTrans.translate(vertex[i].coordinate[0], vertex[i].coordinate[1]);
		//vec[i] = matrixTrans * vec[i];

		vertex[i].coordinate[0] = vec[i].x();
		vertex[i].coordinate[1] = vec[i].y();
		vertex[i].coordinate[2] = vec[i].z();
	}
}
