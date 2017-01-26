#include "include/Light.h"

Light::Light()
{
	Object();
	ourShader = Shader("primitives/shader.vs", "primitives/lamp.frag");
}

void Light::draw(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{
	ourShader.Use();

	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	drawElement(modelLoc, numberBox, glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f);
	lightPos = glm::vec3(500.0f, 100.0f, 100.0f);
	glBindVertexArray(0);
}