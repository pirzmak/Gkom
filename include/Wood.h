#ifndef BELT_H_INCLUDED
#define BELT_H_INCLUDED

#include "Object.h"

class Wood :public Object
{

public:
    enum Stan {GO,RAWE,STOP,END};
private:
    Shader ourShader;
    GLuint texture1;
    GLfloat x,x2;
    GLfloat y,y2;
    GLfloat z,z2;
	GLfloat k,k2;
    Stan stan;
public:
    Wood();
    void draw(glm::mat4 view,glm::mat4 projection, GLfloat camX, GLfloat camY, GLfloat camZ);
    void update(bool);
    void reset();
    Stan getStan();
};


#endif // BELT_H_INCLUDED
