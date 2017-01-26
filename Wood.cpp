#include "include\Wood.h"

Wood::Wood()
{

	Object();
	ourShader = Shader("primitives/shader.vs", "primitives/lighting.frag");
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.specular"), 1);

	texture1 = loadTextures("images/wood.png");
	stan = Stan::GO;
	reset();
}

void Wood::reset(){
	stan = Stan::GO;
	x = 3.0f;
	x2 = 1.5f;
	y = 0.75f;
	y2 = 0.75f;
	k2 = k = z2 = z = 0.0f;
}

void Wood::update(bool a)
{
	if (stan == Stan::GO)
	{
		x -= 0.01f;
		x2 -= 0.01f;
		if (x <= 0.0f)
			stan = Stan::STOP;
	}
	if (stan == Stan::STOP && a)
	{
		stan = Stan::RAWE;
		x2 -= 0.1f;
	}

	if (stan == Stan::RAWE)
	{
		if (y >= 0.2)
		{
			x -= 0.01f;
			if (x <= -6)
			{
				y -= 0.01f;
				z += 0.005f;
				k -= 0.012f;
			}
		}
		if (y2 >= -0.3)
		{
			x2 -= 0.01f;
			if (x2 <= -6)
			{
				y2 -= 0.01f;
				z2 -= 0.0001f;
			}
		}
	}
	if (y <= 0.0 && y2 <= -0.3)
	{
		stan = Stan::END;
	}
}

void Wood::draw(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

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

	glBindVertexArray(CAO);

	drawElement(modelLoc, numberCylinder, glm::vec3(x2, y2, z2), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 1.5f), 1.57f);
	drawElement(modelLoc, numberCylinder, glm::vec3(x, y, z), glm::vec3(0.0f, 1.0f, k), glm::vec3(0.5f, 0.5f, 1.5f), 1.57f);



	glBindVertexArray(0);
}

Wood::Stan Wood::getStan()
{
	return stan;
}