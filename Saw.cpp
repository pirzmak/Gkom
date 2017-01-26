#include "include\Saw.h"

Saw::Saw()
{
	Object();
	ourShader = Shader("primitives/shader.vs", "primitives/lighting.frag");

	texture1 = loadTextures("images/metal.png");
	texture2 = loadTextures("images/w.png");

	glUniform1i(glGetUniformLocation(ourShader.Program, "material.diffuse"), 0.50754);
	glUniform1i(glGetUniformLocation(ourShader.Program, "material.specular"), 0.508273);

	reset();
}

void Saw::reset()
{
	run = false;
	up = false;
	sawX = 0.0f;
	sawdX = 0.005f;
	sawY = 0.0f;
	sawdY = 0.001f;
}

void Saw::draw(glm::mat4 view, glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

	ourShader.Use();
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.position"), 5.0f, 5.0f, 3.0f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "viewPos"), camX, camY, camZ);

	// Set lights properties
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(ourShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	// Set material properties
	glUniform1f(glGetUniformLocation(ourShader.Program, "material.shininess"), 0.4f);


	GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(PAO);
	drawElement(modelLoc, numberSaw, glm::vec3(0.0f, 2.5f + sawY, 0.0f + sawX), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(3.0f, 1.0f, 0.2f), 1.57f);

	if (sawY <= -1.4f)
		drawWo(modelLoc);

	glBindVertexArray(0);
}

void Saw::drawWo(GLint modelLoc)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
	glBindVertexArray(VAO);
	float wX, wY, wZ;



	for (int i = 0; i<100; i++)
	{
		wY = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.9f)));
		wX = -(1.5f - wY) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * (1.5f - wY))));
		wZ = -(0.6f - wY) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * (0.6f - wY))));

		drawElement(modelLoc, numberBox, glm::vec3(wZ, wY, wX), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.02f, 0.05f, 0.02f), 1.57f);
	}

}

bool Saw::update(Wood::Stan a)
{
	if (sawX >= 0.4f || sawX <= -0.4f)
		sawdX = -sawdX;

	if (a == Wood::Stan::STOP)
		run = true;

	if (sawY <= -1.7f)
	{
		sawdY = -sawdY;
		up = !up;
	}

	if (sawY >= 0.0f && up)
		run = false;

	sawX += sawdX;

	if (run)
		sawY -= sawdY;

	return sawY >= -1.3f && up;
}
