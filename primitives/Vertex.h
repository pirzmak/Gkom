#ifndef CYLINDER_H
#define CYLINDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    Vertex() = default;
    Vertex(GLfloat x,GLfloat y,GLfloat z,GLfloat a,GLfloat b)
    {
        position = glm::vec3(x,y,z);
        normal = glm::vec3(0.65f,0.11f,0.18f);
        texture = glm::vec2(a,b);
    }
    Vertex(GLfloat x,GLfloat y,GLfloat z,GLfloat a,GLfloat b,GLfloat c,GLfloat m,GLfloat n)
    {
        position = glm::vec3(x,y,z);
        normal = glm::vec3(a,b,c);
        texture = glm::vec2(m,n);
    }
    ~Vertex() = default;

};

#endif // CYLINDER_H
