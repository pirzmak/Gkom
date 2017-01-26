#include "include/Machine.h"

Machine::Machine()
{
	Object();
	ourShader = Shader("primitives/shader.vs", "primitives/lighting.frag");
	texture1 = loadTextures("images/container.jpg");

	texture2 = loadTextures("images/belt2.png");
	texture3 = loadTextures("images/belt.png");

	glUniform1i(glGetUniformLocation(ourShader.Program, "material.diffuse"), 0.5);
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.specular"), 0.7);
}

void Machine::reset(){
	saw.reset();
}

void Machine::draw(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{
	drawConst(view, projection, camX, camY, camZ);
	saw.draw(view, projection, camX, camY, camZ);
}

bool Machine::update(Wood::Stan s)
{
	if (s != Wood::Stan::STOP)
	{
		a++;
		k += 0.05f;
	}
	return saw.update(s);
}

void Machine::drawConst(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{

	ourShader.Use();
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.position"), 5.0f, 5.0f, 3.0f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "viewPos"), camX, camY, camZ);

	// Set lights properties
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	// Set material properties
	glUniform1f(glGetUniformLocation(ourShader.Program, "material.shininess"), 3.078125f);

	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);


	glBindVertexArray(VAO);

	//long lower cuboid
	drawElement(modelLoc, numberBox, glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 1.0f, 0.5f), 0.0f);
	drawElement(modelLoc, numberBox, glm::vec3(0.0f, 0.0f, -1.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 1.0f, 0.5f), 0.0f);
	//vertical cuboid
	drawElement(modelLoc, numberBox, glm::vec3(-0.125f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 0.2f, 0.4f), 1.57f);
	drawElement(modelLoc, numberBox, glm::vec3(0.125f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 0.2f, 0.4f), 1.57f);
	drawElement(modelLoc, numberBox, glm::vec3(-0.125f, 1.5f, -1.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 0.2f, 0.4f), 1.57f);
	drawElement(modelLoc, numberBox, glm::vec3(0.125f, 1.5f, -1.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 0.2f, 0.4f), 1.57f);
	//up cuboid
	drawElement(modelLoc, numberBox, glm::vec3(-0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(3.75f, 0.3f, 0.5f), 1.57f);
	//short lower cuboid
	drawElement(modelLoc, numberBox, glm::vec3(4.75f, -0.3f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.5f, 0.4f, 0.3f), 1.57f);
	drawElement(modelLoc, numberBox, glm::vec3(-4.75f, -0.3f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.5f, 0.4f, 0.3f), 1.57f);

	if (a % 2)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);
	}
	//beld
	drawElement(modelLoc, numberBox, glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(9.5f, 0.5f, 2.0f), 0.0f);


	glBindVertexArray(CAO);

	//small cylinder
	drawElement(modelLoc, numberCylinder, glm::vec3(4.75f, 0.25f, -1.7f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 3.3f), k);
	drawElement(modelLoc, numberCylinder, glm::vec3(-4.75f, 0.25f, -1.7f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.2f, 0.2f, 3.3f), k);
	//big cylinder
	drawElement(modelLoc, numberCylinder, glm::vec3(4.75f, 0.25f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 2.0f), k);
	drawElement(modelLoc, numberCylinder, glm::vec3(-4.75f, 0.25f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 2.0f), k);


	glBindVertexArray(0);
}