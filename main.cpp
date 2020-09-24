#include "stdafx.h"

GLvoid Reshape(int w, int h);
GLvoid Frame(int value) {glutPostRedisplay();   glutTimerFunc(17, Frame, 1); }		// 30 FRAME
GLvoid Update(int value) { G_SCENE->Update((1000/30)*0.001f); glutTimerFunc(30, Update, 1); }		// 
GLvoid GLUTFUNCTION() { glutTimerFunc(17, Frame, 1);  glutTimerFunc(30, Update, 1); }
GLvoid Commit() { G_SCENE->Commit("Logo", new cSceneLogo); G_SCENE->Commit("Menu", new cSceneMenu); G_SCENE->Commit("Game", new cSceneGame); GLUTFUNCTION(); }
GLvoid Init() { /*G_SCENE->Init();*/ }
GLvoid SpecialKey(int key, int x, int y){ G_SCENE->SpeicalKeyDown(key, x, y); }
GLvoid NormalKey(unsigned char key, int x, int y){ G_SCENE->NormalKeyDown(key, x, y); }
GLvoid drawScene(GLvoid) { G_SCENE->Draw(); }

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(__D__WINDOWS__WIDTH, __D__WINDOWS__HEIGHT);
	glutCreateWindow("FORWARD HEXAGON");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(NormalKey);
	Commit();
	Init();
	glutMainLoop();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
}