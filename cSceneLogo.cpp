#include <GL/glut.h>
#include <stdio.h>
#include "Define.h"
#include "cSceneLogo.h"
void cSceneLogo::Init(){
	FMOD::System_Create(&m_System);
	m_System->init(2, FMOD_INIT_NORMAL, 0);
	m_System->createSound("Sound/Logo.mp3", FMOD_DEFAULT, 0, &m_Sound);
	m_Sound->setMode(FMOD_LOOP_NORMAL);
	m_System->playSound(FMOD_CHANNEL_FREE, m_Sound, FALSE, &m_Channel);
	m_pLogo= LoadDIBitmap("Intro.bmp", &m_pBitmap);
}
void cSceneLogo::Update(float dt){


}

void cSceneLogo::Draw(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-__D__WINDOWS__WIDTH / 2, __D__WINDOWS__WIDTH / 2, -__D__WINDOWS__HEIGHT / 2, __D__WINDOWS__HEIGHT / 2, -400, 400);
	UseBitmap(GL_TEXTURE_2D, 800, 600, 800, 600, m_pLogo, m_pLogo,0.0f,0.0f);
	glutSwapBuffers();
}
void cSceneLogo::Exit(){
	if (m_System != NULL)
	{
		m_System->close();
		free(m_pLogo);
	}
}

void cSceneLogo::SpecialKeyDown(int key, int x, int y)
{
	SetChangeScene(true, "Menu");
}
void cSceneLogo::NormalKeyDown(unsigned char key, int x, int y)
{
	SetChangeScene(true, "Menu");
}