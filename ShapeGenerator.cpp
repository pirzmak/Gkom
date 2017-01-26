#include "include/ShapeGenerator.h"
#include "primitives/Vertex.h"
#include "primitives/ShapeData.h"
#include <iostream>

/*Funkcja do generowania walca*/
ShapeData ShapeGenerator::makeCylinder()
{
    ShapeData ret;
	const int numVertices = 360;
    Vertex vertices[numVertices];

    float theta = 2 * 3.1415926 / float(numVertices/12);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = 0.5;
	float y = 0;
	
	float dx,dy;

    for(int i=0; i<numVertices; ){
		
		dx = x;
		dy = y;
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
		
		vertices[i++] = Vertex(0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.75f,0.0f);
		vertices[i++] = Vertex(dx  ,dy  ,0.0f,1.0f,0.0f,0.0f,0.5f,1.0f);		
		vertices[i++] = Vertex(x   ,y   ,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f);
		
		vertices[i++] = Vertex(0.0f,0.0f,1.0f,-1.0f,0.0f,0.0f,0.75f,0.0f);
		vertices[i++] = Vertex(dx  ,dy  ,1.0f,-1.0f,0.0f,0.0f,0.5f,1.0f);		
		vertices[i++] = Vertex(x   ,y   ,1.0f,-1.0f,0.0f,0.0f,1.0f,1.0f);
		
		vertices[i++] = Vertex(dx  ,dy  ,0.0f,dx   ,0.0f,dy  ,0.0f,0.0f);		
		vertices[i++] = Vertex(x   ,y   ,0.0f,dx   ,0.0f,dy  ,0.5f,0.0f);
		vertices[i++] = Vertex(dx  ,dy  ,1.0f,dx   ,0.0f,dy  ,0.0f,1.0f);
		vertices[i++] = Vertex(dx  ,dy  ,1.0f,dx   ,0.0f,dy  ,0.0f,1.0f);		
		vertices[i++] = Vertex(x   ,y   ,1.0f,dx   ,0.0f,dy  ,0.5f,1.0f);
		vertices[i++] = Vertex(x   ,y   ,0.0f,dx   ,0.0f,dy  ,0.5f,0.0f);
		
		//std::cout<<x<<" "<<y<<std::endl;
		
    }
   
    ret.numVertices = numVertices;
    ret.vertices = new Vertex[numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));

    return ret;
}

/*Funkcja do piły*/
ShapeData ShapeGenerator::makeSaw()
{
    ShapeData ret;
	const int numElem = 30;
	const int numVertices = 30 + numElem*4*3;
    Vertex vertices[numVertices];
    
    float x = -0.5;
    float dx = 1.0/numElem;
    int n=0;
    vertices[n++]=Vertex(-0.5f,0.25,0.0 ,-1.0f,1.0f,0.0f,0.0f,0.0f);
    vertices[n++]=Vertex( 0.5f,0.25,0.0 ,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.25,0.25,-1.0f,1.0f,0.0f,1.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);    
    
    vertices[n++]=Vertex( 0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);    
    vertices[n++]=Vertex(-0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex(-0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,0.0f,0.0f);    
    
    vertices[n++]=Vertex(0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,0.0f,0.0f);    
    vertices[n++]=Vertex(0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex(0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(0.5f,0.25,0.25,-1.0f,1.0f,0.0f,1.0f,1.0f);
    vertices[n++]=Vertex(0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    
    vertices[n++]=Vertex( 0.5f,0.25,0.25,-1.0f,1.0f,0.0f,1.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,1.0f,0.0f);    
    vertices[n++]=Vertex(-0.5f,0.25,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex( 0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex(-0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,0.0f,0.0f);
    
    vertices[n++]=Vertex(-0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,0.0f,0.0f);    
    vertices[n++]=Vertex(-0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.0f,-1.0f,1.0f,0.0f,1.0f,0.0f);
    vertices[n++]=Vertex(-0.5f,0.25,0.25,-1.0f,1.0f,0.0f,1.0f,1.0f);
    vertices[n++]=Vertex(-0.5f,0.0f,0.25,-1.0f,1.0f,0.0f,0.0f,1.0f);
    
   for(int i=n; i<numVertices; ){
		vertices[i++] = Vertex(x     , 0.0f,0.0f ,0.0f,0.0f,0.0f,1.0f,0.0f);
		vertices[i++] = Vertex(x     , 0.0f,0.25 ,0.0f,0.0f,0.0f,0.0f,1.0f);
		vertices[i++] = Vertex(x+dx/2,-0.25,0.125,0.0f,0.0f,0.0f,0.0f,0.0f);
		
		vertices[i++] = Vertex(x+dx  , 0.0f,0.0f ,0.0f,0.0f,0.0f,1.0f,0.0f);
		vertices[i++] = Vertex(x+dx  , 0.0f,0.25 ,0.0f,0.0f,0.0f,0.0f,1.0f);
		vertices[i++] = Vertex(x+dx/2,-0.25,0.125,0.0f,0.0f,0.0f,0.0f,0.0f);
		
		vertices[i++] = Vertex(x+dx  , 0.0f, 0.25,0.0f,0.0f,0.0f,1.0f,0.0f);
		vertices[i++] = Vertex(x     , 0.0f, 0.25,0.0f,0.0f,0.0f,0.0f,1.0f);
		vertices[i++] = Vertex(x+dx/2,-0.25,0.125,0.0f,0.0f,0.0f,0.0f,0.0f);
		
		vertices[i++] = Vertex(x     , 0.0f,0.0f ,0.0f,0.0f,0.0f,1.0f,0.0f);
		vertices[i++] = Vertex(x     , 0.0f,0.25 ,0.0f,0.0f,0.0f,0.0f,1.0f);
		vertices[i++] = Vertex(x+dx/2,-0.25,0.125,0.0f,0.0f,0.0f,0.0f,0.0f);
		x+=dx;		
    }
    
    ret.numVertices = numVertices;
    ret.vertices = new Vertex[numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));

    
    return ret;

}

ShapeData ShapeGenerator::makeBox()
{
    ShapeData ret;
	int numVertices = 36;
	
    Vertex vertices[] = {
		Vertex(-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f),
		Vertex( 0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f),
		Vertex( 0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f),
		Vertex( 0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f),
		Vertex(-0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f),
		Vertex(-0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f),
		
		Vertex(-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
		Vertex( 0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
		Vertex( 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		Vertex( 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
		
        Vertex(-0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f, 0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(-0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.5f,-0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		
        Vertex( 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex( 0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex( 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		Vertex( 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		Vertex( 0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex( 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		
        Vertex(-0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f),
		Vertex( 0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 1.0f),
		Vertex( 0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f),
		Vertex( 0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f),
		
        Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex( 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		Vertex( 0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex( 0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f)        
		};
		
    	
    ret.numVertices = numVertices;
    ret.vertices = new Vertex[numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));

    
    return ret;

}

ShapeData ShapeGenerator::makeGround()
{
    ShapeData ret;
	const int numVertices = 150;
    Vertex vertices[numVertices];
    
    int n = 0;
	
	for(int j=0; j<5;j++)
    for(int i=0; i<5;i++){
		vertices[n++] = Vertex(-1.0f + i*0.4f,j*0.4f,0.0f,       0.0f,1.0f,0.0f,0.0f,1.0f);
		vertices[n++] = Vertex(-0.6f + i*0.4f,j*0.4f,0.0f,       0.0f,1.0f,0.0f,1.0f,1.0f);
		vertices[n++] = Vertex(-0.6f + i*0.4f,0.4f + j*0.4f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f);
		
		vertices[n++] = Vertex(-0.6f + i*0.4f,0.4f + j*0.4f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f);
		vertices[n++] = Vertex(-1.0f + i*0.4f,0.4f + j*0.4f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f);
		vertices[n++] = Vertex(-1.0f + i*0.4f,j*0.4f,0.0f,       0.0f,1.0f,0.0f,0.0f,1.0f);		
    }
   
    ret.numVertices = numVertices;
    ret.vertices = new Vertex[numVertices];
    memcpy(ret.vertices, vertices, sizeof(vertices));
	
    return ret;

}


