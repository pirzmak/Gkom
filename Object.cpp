#include "include/Object.h"

GLuint Object::VAO = 0;
GLuint Object::CAO = 0;
GLuint Object::PAO = 0;
GLuint Object::GAO = 0;
glm::vec3 Object::lightPos = glm::vec3(0.0f, 5.0f, 0.0f);
GLushort Object::numberBox = 0;
GLushort Object::numberCylinder = 0;
GLushort Object::numberSaw = 0;
GLushort Object::numberGround = 0;

Object::Object()
{
	if (VAO == 0)
		numberBox = sendDataToOpenGL(VAO, BOX);
	if (CAO == 0)
		numberCylinder = sendDataToOpenGL(CAO, CYLINDER);
	if (PAO == 0)
		numberSaw = sendDataToOpenGL(PAO, SAW);
	if (GAO == 0)
		numberGround = sendDataToOpenGL(GAO, GROUND);

}

void Object::clear()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &CAO);
	glDeleteVertexArrays(1, &PAO);
	glDeleteVertexArrays(1, &GAO);
}

GLuint Object::loadTextures(char* path)
{
	GLuint texture1;
	glGenTextures(1, &texture1);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	return texture1;
}

GLushort Object::sendDataToOpenGL(GLuint& VAO, dataType type)
{
	ShapeData object;

	if (type == BOX)
		object = ShapeGenerator::makeBox();
	else if (type == CYLINDER)
		object = ShapeGenerator::makeCylinder();
	else if (type == SAW)
		object = ShapeGenerator::makeSaw();
	else if (type == GROUND)
		object = ShapeGenerator::makeGround();
	else
		return -1;
	GLuint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, object.vertexBufferSize(), object.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO



	GLushort ret = object.numVertices;

	object.cleanup();
	return ret;
}

void Object::drawElement(GLuint modelLoc, GLuint number, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float angle)
{
	glm::mat4 model;
	model = glm::translate(model, translate);
	model = glm::rotate(model, angle, rotate);
	model = glm::scale(model, scale);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, number);
}

