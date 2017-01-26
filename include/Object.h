#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <iostream>
#include <SOIL.h>

#include "../primitives/Shader.h"
#include "../primitives/ShapeData.h"
#include "ShapeGenerator.h"

enum dataType
{
    CYLINDER,BOX,SAW,GROUND
};

class Object
{
protected:
    static GLuint VAO;
    static GLushort numberBox;
    static GLuint CAO;
    static GLushort numberCylinder;
    static GLuint PAO;
    static GLushort numberSaw;
    static GLuint GAO;
    static GLushort numberGround;
    static glm::vec3 lightPos;
    GLuint loadTextures(char* path);
    GLushort sendDataToOpenGL(GLuint& O,dataType type);
    void drawElement(GLuint modelLoc,GLuint number,glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale, float angle);
public:
    Object();
    void virtual draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ) {};
    void clear();

};

#endif // OBJECT_H_INCLUDED
