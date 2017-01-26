#ifndef SHAPEDATA_INCLUDED
#define SHAPEDATA_INCLUDED
#include <GL/glew.h>
#include "Vertex.h"

struct ShapeData
{
    Vertex* vertices;
    GLuint numVertices;

    ShapeData():
        vertices(0), numVertices(0){};

    GLsizeiptr vertexBufferSize() const
    {
        return numVertices*(8 * sizeof(GLfloat));
    }

    void cleanup()
    {
        delete[] vertices;
        numVertices = 0;
    }
};


#endif // SHAPEDATA_INCLUDED
