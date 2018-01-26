#include <iostream> // we need this to output to console this file contains cout
#include "SimpleObj.h"

using namespace std;

//we are going to draw a triangle so we need a list of offsets we will hold in array called TriVertices
static const GLfloat TriVertices[] =
{
	0.0f,
	0.1f,
	0.0f, // 1st vertex x,y,z

	-0.1f,
	-0.1f,
	0.0f, // 2nd vertexc x,y,z

	0.1f,
	-0.1f,
	0.0f  // 3d vertex x,y,z notice all the z's are 0
};




SimpleObj::SimpleObj()
{
	Xspeed = 0.01f; // lets make our construc
	Yspeed = 0.01f;
	// we need to give a start position
	Xpos = Ypos = 0.0f;
}

SimpleObj::~SimpleObj() {} // no code yet in the destructor

/************************************************************************
Update has to do some work, in this case we'll print out some info on our position and
move our object in clip space (-1 to +1), then Draw something.
************************************************************************/

void SimpleObj::Update()
{// output our name and say something about our position
	cout << "Hello my name is " + m_MyName + " and my Xpos is: " << Xpos << endl;

// lets move our object	by just adding the speed value
	Xpos += Xspeed;
	if (Xspeed > 0)
	{
		if (Xpos > 1.0f) Xspeed = -Xspeed;
	}
	else
	{
		if (Xpos < -1.0f) Xspeed = -Xspeed;
	}
// why not try changing the Ypos and Yspeed yourself ?


// now lets draw our object
	SimpleObj::Draw(); // we don't really need to prefix this, this method is in SimpleObj, so it can just type Draw(); I only do it for emphasis.
}


/************************************************************************
The Draw system needs a bit of setting up
The shader will draw what we tell it but we have to send it some
************************************************************************/
void SimpleObj::Draw()
{
// its important we tell our draw system what Program Object (PO) we are using, intially its the same one as in the OGL::OpenGLES instance but that may change
	glUseProgram(ProgramObject); // this was set up when we created the instance of SimpleObj
	// Get the attribute locations which are the offset buffers, we'll store these in values we can call handles.
	GLint positionLoc = glGetAttribLocation(ProgramObject, "a_position");

	// if we want to position it somewhere we need to ask for the handle for the position uniform
	GLint positionUniformLoc = glGetUniformLocation(ProgramObject, "u_position");

/***********************************************************************
This is a rather hacky way to send position data, we'll refine this soon!
In this primitive shader, our screen goes from -1 to +1 in the X and Y position
we need to pass our new Xpos and Ypos to the shader in 2 steps
************************************************************************/

// 1st create a dummy array	of 4 values
	float Pos[4] = { 0.0f, 0.0f, 0.0f,0.0f };

// now load our X and Y in to this, we don't care about the last 2 entries they are set to 0
	Pos[0] =	Xpos;
	Pos[1] =	Ypos;

// 2nd, we can now transfer this to the u_position value in the shader which we have a handle for in positionUniformLoc
	glUniform4fv(positionUniformLoc, 1, &Pos[0]);

// So we've told the shader to use our Xpos and Ypos values as the centre point, now tell it to use the array of vertices in TriVertices
	glVertexAttribPointer	(
		positionLoc,
		3,  // we send 3 values at a time (x,y,z offsets)
		GL_FLOAT,  // they are floats
		GL_FALSE,  // then are not normalised(explained later)
		0, //0 means no step needed, just go to the next set
		TriVertices
		);

	glEnableVertexAttribArray(0); // when we enable it, the shader can now use it

// now its been set up, tell it to draw 3 vertices which make up a triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

// we could have this after each GL function but having one here will tell us if there was an error
	if (glGetError() != GL_NO_ERROR) printf("OpenGLES2.0 reports an error!");

}
