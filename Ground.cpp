#include "include/Ground.h"

Ground::Ground()
{
	Object();
	ourShader = Shader("primitives/shader.vs", "primitives/lighting.frag");
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.specular"), 1);

	texture1 = loadTextures("images/ground.png");

}

void Ground::draw(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{

	ourShader.Use();
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(ourShader.Program, "viewPos"), camX, camY, camZ);

	// Set lights properties
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	// Set material properties
	glUniform1f(glGetUniformLocation(ourShader.Program, "material.shininess"), 32.0f);

	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glBindVertexArray(GAO);
	drawElement(modelLoc, numberGround, glm::vec3(0.0f, -1.0f, -500.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(500.0f, 500.0f, 500.0f), 1.57f);
	glBindVertexArray(0);
}
