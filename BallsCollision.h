#pragma once

#include <Windows.h>
#include <cstdio>
#include "glut.h"
#include <queue>

#include "Particle.h"
#include "Event.h"
#include "Vec.h"

// Временной шаг вычислений
double timeStep = 0.5;
extern int PARTICLES_COUNT;
extern double currentTime;
extern Particle particles[];
extern std::priority_queue<Event> ct;

Particle particles[2000];

Vec camDirection(0.0, 0.0, -10.0);
Vec camPosition(0, -50, 0);

double cameraRotation = 0;
double cameraTilt = 0;

GLUquadricObj *cylinderObj;
GLuint texture[1];

int wnd;
bool velocityColor = true;

Event dummy = Event(0, nullptr, nullptr, 5);

GLvoid resizeGLScene(GLsizei width, GLsizei height);
GLboolean initGLScene(GLvoid);
GLint drawGLScene(GLvoid);
GLvoid createWin(char* title, GLfloat winWidth, GLfloat winHeight);
GLvoid renderScene(GLvoid);
GLvoid keyPressed(unsigned char key, int x, int y);
GLvoid idle();
GLvoid initVariables();
GLboolean loadTexture(LPTSTR szFileName, GLuint &texid);
void test(int i);