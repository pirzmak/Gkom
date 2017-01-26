#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED
#include <vector>
#include "../primitives/Shader.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class SkyBox {

    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
	Shader skyboxShader;

    GLuint loadCubemap(std::vector<const GLchar*> faces);
	GLuint loadTextures(char* path);
public:
    SkyBox();
	void draw(glm::mat4 view, glm::mat4 projection, glm::mat4 cameraView );
};


#endif // SKYBOX_H_INCLUDED
