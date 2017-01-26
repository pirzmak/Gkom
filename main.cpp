#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/SkyBox.h"
#include "include/Camera.h"
#include "include/Machine.h"
#include "include/Light.h"
#include "include/Wood.h"
#include "include/Ground.h"

#include <iostream>


using namespace std;

// Prototypy funkcji
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow* init();

void reset();
void do_movement();

// Wielkosc okna
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera camera(glm::vec3(-15.0f, 6.0f, 2.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

bool res = false;
int speed = 1;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


int main()
{

	GLFWwindow* window = init();

	// Wielkoœæ ekranu
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, WIDTH, HEIGHT);

	Machine a;
	Light light;
	SkyBox s;
	Wood w;
	Ground g;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

		if (res){
			w.reset();
			a.reset();
			res = !res;
		}

		for (int i = 0; i<speed; ++i)
			w.update(a.update(w.getStan()));

		s.draw(view, projection, camera.GetViewMatrix());
		a.draw(view, projection, camera.Position.x, camera.Position.y, camera.Position.z);
		w.draw(view, projection, camera.Position.x, camera.Position.y, camera.Position.z);
		g.draw(view, projection, camera.Position.x, camera.Position.y, camera.Position.z);
		light.draw(view, projection, camera.Position.x, camera.Position.y, camera.Position.z);

		glfwSwapBuffers(window);
	}
	a.clear();
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}



GLFWwindow* init()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	std::cout << "W - kamera do przodu" << std::endl;
	std::cout << "S - kamera do ty³u" << std::endl;
	std::cout << "A - kamera w lewo" << std::endl;
	std::cout << "D - kamera w prawo" << std::endl;
	std::cout << "Mysz - obrót kamer¹" << std::endl;
	std::cout << "R - reset animacji" << std::endl;
	std::cout << "Strza³ka do góry - zwiêksz szybkoœæ" << std::endl;
	std::cout << "Strza³ka do do³u - zmniejsz szybkoœæ" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT, GL_LINE);

	return window;
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);

	//Reset
	if (keys[GLFW_KEY_R])
		reset();

	if (keys[GLFW_KEY_UP])
		if (speed<10)speed++;

	if (keys[GLFW_KEY_DOWN])
		if (speed>1)speed--;
}

void reset(){
	res = true;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}