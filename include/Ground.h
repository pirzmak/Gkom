#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED

#include "Object.h"

class Ground :public Object
{
    Shader ourShader;
    GLuint texture1;
    public:
    Ground();
    void draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
};

#endif // GROUND_H_INCLUDED
