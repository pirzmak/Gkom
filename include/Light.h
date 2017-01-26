#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#include "Object.h"

class Light :public Object
{
    Shader ourShader;
public:
    Light();
    void draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
};

#endif // LIGHT_H_INCLUDED
