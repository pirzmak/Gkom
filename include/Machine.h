#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED
#include "Object.h"
#include "Saw.h"

class Machine :public Object
{
    Shader ourShader;
    GLuint texture1,texture2,texture3;
    Saw saw;
    int a=0;
    float k=0.0f;
    void drawConst(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
public:
    Machine();
    void draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
    bool update(Wood::Stan);
    void reset();
};


#endif // MACHINE_H_INCLUDED
