#ifndef SAW_H_INCLUDED
#define SAW_H_INCLUDED
#include <cstdlib>

#include "Object.h"
#include "Wood.h"


class Saw :public Object
{
    Shader ourShader;
    GLuint texture1;
    GLuint texture2;
    GLfloat sawX,sawdX,sawY,sawdY;
    bool run;
    bool up;

public:
    Saw();
    void draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
    void drawWo(GLint);
    bool update(Wood::Stan);
    void reset();
};



#endif // SAW_H_INCLUDED
