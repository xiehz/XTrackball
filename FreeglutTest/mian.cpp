#include "stdafx.h"

#include "gl/glut.h"
#include <GL/glut.h>
#include "trackball.h"

GLfloat m[4][4];
float last[4];
float cur[4] = { 0.0f, 0.0f,0.0f,1.0f };
int width;
int height;
int beginx;
int beginy;
float p1x;
float p1y;
float p2x;
float p2y;

float translate[4] = { 0.0f,0.0f,0.0f,0.0f };
float scales[4] = { 1.0f,1.0f,1.0f,1.0f };

int button_mark;

void display()
{
	m[0][0] = 1.0;	m[0][1] = 0.0;	m[0][2] = 0.0;	m[0][3] = 0.0;
	m[1][0] = 0.0;	m[1][1] = 1.0;	m[1][2] = 0.0;	m[1][3] = 0.0;
	m[2][0] = 0.0;	m[2][1] = 0.0;	m[2][2] = 1.0;	m[2][3] = 0.0;
	m[3][0] = 0.0;	m[3][1] = 0.0;	m[3][2] = 0.0;	m[3][3] = 1.0;
	/*buildScaleMatrix(m, scales);
	build_rotmatrix(m, cur);*/
	buildTranslateMatrix(m, translate);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixf(*m);

	//glTranslatef(-5.0f, 0.0f, 0.0f);
	float mat[16] = { 0 };
	glGetFloatv(GL_MODELVIEW_MATRIX,mat);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidTeapot(0.5);
	glPopMatrix();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			button_mark = 2;
		}
		else {
			button_mark = -1;
		}
	}
	else if(button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			button_mark = 1;
		}
		else {
			button_mark = -1;
		}
	}
	else {
		if (state == GLUT_DOWN)
		{
			button_mark = 0;
		}
		else {
			button_mark = -1;
		}
	}
	beginx = x;
	beginy = y;
}

void motion(int x, int y)
{
	p1x = (2.0*beginx - width) / width;
	p1y = (height - 2.0*beginy) / height;
	p2x = (2.0 * x - width) / width;
	p2y = (height - 2.0 * y) / height;

	if (button_mark == 2)
	{
		scale(y > beginy? 1 : -1, p2x, p2y, scales);
	}
	else if(button_mark == 1){
		pan(p1x, p1y, p2x, p2y, translate);
	}
	else if(button_mark == 0){
		trackball(last, p1x, p1y, p2x, p2y);
		add_quats(last, cur, cur);
	}
	else {
		
	}

	beginx = x;
	beginy = y;
	glutPostRedisplay();
}

void reshape(int w, int h)
{

	width = w;
	height = h;
	double l;
	l = 6;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-l, l, -l, l, -l, l);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	trackball(cur, 0.0, 0.0, 0.0, 0.0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Rotacija z misko");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutReshapeFunc(reshape);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}