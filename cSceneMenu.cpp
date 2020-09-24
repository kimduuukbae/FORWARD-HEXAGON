#include <GL/glut.h>
#include "cSceneMenu.h"
#include "Define.h"
#include <math.h>
void cSceneMenu::Init(){
	m_pBackGround = LoadDIBitmap("Menu.bmp", &m_pBitmap);
	m_pSpace = LoadDIBitmap("Space.bmp", &m_pBitmap);
	m_pSelect[0] = LoadDIBitmap("normal.bmp", &m_pBitmap);
	m_pSelect[1] = LoadDIBitmap("crazy.bmp", &m_pBitmap);
	m_pSelect[2] = LoadDIBitmap("credit.bmp", &m_pBitmap);
	m_pButton[0] = LoadDIBitmap("button.bmp", &m_pBitmap);
	m_pButton[1] = LoadDIBitmap("button2.bmp", &m_pBitmap);
	InitScore();
	m_nSelectNum = 0;
	buttonXPos[0] = 0;
	buttonXPos[1] = 0;
	Power = 1.4f;
	nPos = 9.0f;

	FMOD::System_Create(&m_System);
	m_System->init(2, FMOD_INIT_NORMAL, 0);
	m_System->createSound("Sound/Menu.mp3", FMOD_DEFAULT, 0, &m_Sound);
	m_Sound->setMode(FMOD_LOOP_NORMAL);
	m_System->playSound(FMOD_CHANNEL_FREE, m_Sound, FALSE, &m_Channel);


}
void cSceneMenu::ButtonManager(float dt)
{
	if (m_bButtonOn[0] == true)
	{
		buttonXPos[0] = SmoothStep(buttonXPos[0], 16.0f, dt*20.0f);
		if (buttonXPos[0] >= 15.0f)
		{
			m_bButtonOn[2] = true;
			m_bButtonOn[0] = false;
			m_nSelectNum++;
			if (m_nSelectNum >= 3)
				m_nSelectNum = 0;
		}
	}
	else if (m_bButtonOn[1] == true)
	{
		buttonXPos[1] = SmoothStep(buttonXPos[1], -16.0f, dt*20.0f);
		if (buttonXPos[1] <= -15.0f)
		{
			m_bButtonOn[3] = true;
			m_bButtonOn[1] = false;
			m_nSelectNum--;
			if (m_nSelectNum <= -1)
				m_nSelectNum = 2;
		}
	}
	else if (m_bButtonOn[2] == true)
	{
		buttonXPos[0] = SmoothStep(buttonXPos[0], -1.0f, dt*10.0f);
		if (buttonXPos[0] <= 0.0f)
		{
			m_bButtonOn[2] = false;
			buttonXPos[0] = 0.0f;
		}
	}
	else if (m_bButtonOn[3] == true)
	{
		buttonXPos[1] = SmoothStep(buttonXPos[1], 1.0f, dt*10.0f);
		if (buttonXPos[1] >= 0.0f)
		{
			m_bButtonOn[3] = false;
			buttonXPos[1] = 0.0f;
		}
	}
}
void cSceneMenu::Update(float dt){
	ButtonManager(dt);
	if (fDt >= 0.25f)
	{
		nPos -= dt * 3.0f;
		PosY = sinf(nPos * 5.0f) * pow(Power, nPos);
		PosDt += dt;
		if (PosDt >= 0.1f)
		{
			fDt = 0.0f;
			PosDt = 0.0f;
			nPos = 9.0f;
			PosY = 0.0f;
		}
	}
	else
		fDt += dt;
}
void cSceneMenu::Draw(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-__D__WINDOWS__WIDTH / 2, __D__WINDOWS__WIDTH / 2, -__D__WINDOWS__HEIGHT / 2, __D__WINDOWS__HEIGHT / 2, -400, 400);
	glPushMatrix();
	glTranslatef(0.0f, PosY, 0.0f);
	UseBitmap(GL_TEXTURE_2D, 800, 600, 800, 600, m_pBackGround, m_pBackGround, 0.0f,0.0f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -190.0f, 0.0f);
	UseBitmap(GL_TEXTURE_2D, 279.5, 32.5, 559, 65, m_pSpace, m_pSpace, 0.0f, 0.1f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, -240.0f, 0.0f);
	UseBitmap(GL_TEXTURE_2D, 559, 65, 559, 65, m_pSelect[m_nSelectNum], m_pSelect[m_nSelectNum], 0.0f, 0.1f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(340.0f + buttonXPos[0], -240.0f , 0.0f);
	UseBitmap(GL_TEXTURE_2D, 110, 63, 163, 94, m_pButton[0], m_pButton[0], 0.0f, 0.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-340.0f + buttonXPos[1], -240.0f , 0.0f);
	UseBitmap(GL_TEXTURE_2D, 110, 63, 163, 94, m_pButton[1], m_pButton[1], 0.0f, 0.2f);
	glPopMatrix();
	ViewScore();
	glutSwapBuffers();
}
void cSceneMenu::Exit(){
	if (m_System != NULL)
		m_System->close();
}
void cSceneMenu::SpecialKeyDown(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		m_bButtonOn[0] = true;
		break;
	case GLUT_KEY_LEFT:
		m_bButtonOn[1] = true;
		break;
		//case GLUT_space
	}
}
void cSceneMenu::InitScore()
{
	m_pScore[0] = LoadDIBitmap("score.bmp", &m_pBitmap);
	m_pScore[1] = LoadDIBitmap("0.bmp", &m_pBitmap);
	m_pScore[2] = LoadDIBitmap("1.bmp", &m_pBitmap);
	m_pScore[3] = LoadDIBitmap("2.bmp", &m_pBitmap);
	m_pScore[4] = LoadDIBitmap("3.bmp", &m_pBitmap);
	m_pScore[5] = LoadDIBitmap("4.bmp", &m_pBitmap);
	m_pScore[6] = LoadDIBitmap("5.bmp", &m_pBitmap);
	m_pScore[7] = LoadDIBitmap("6.bmp", &m_pBitmap);
	m_pScore[8] = LoadDIBitmap("7.bmp", &m_pBitmap);
	m_pScore[9] = LoadDIBitmap("8.bmp", &m_pBitmap);
	m_pScore[10] = LoadDIBitmap("9.bmp", &m_pBitmap);
	m_pScore[11] = LoadDIBitmap("10.bmp", &m_pBitmap);

	FILE *fp[2];

	fp[0] = fopen("Ranking/Normal_Ranking.txt", "r");
	fp[1] = fopen("Ranking/Crazy_Ranking.txt", "r");

	fscanf(fp[0], "%d", &n_Score[0]);
	fscanf(fp[1], "%d", &n_Score[1]);

	fclose(fp[0]);
	fclose(fp[1]);
}
void cSceneMenu::ViewScore()
{
	if (m_nSelectNum != 2)
	{
		glPushMatrix();
		glTranslatef(-310.0f, 285.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 192, 32, 384, 64, m_pScore[0], m_pScore[0], 0.0f, 0.2f);
		glPopMatrix();
	}
	if (m_nSelectNum == 0)
	{
		glPushMatrix();
		glTranslatef(-252.0f, 285.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 24, 24, 64, 64, m_pScore[n_Score[0] / 10 + 1], m_pScore[n_Score[0] / 10 + 1], 0.0f, 0.3f);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-232.0f, 285.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 24, 24, 64, 64, m_pScore[n_Score[0] - ((n_Score[0] / 10) * 10) + 1], m_pScore[n_Score[0] - ((n_Score[0] / 10) * 10) + 1], 0.0f, 0.3f);
		glPopMatrix();
	}
	if (m_nSelectNum == 1)
	{
		glPushMatrix();
		glTranslatef(-252.0f, 285.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 24, 24, 64, 64, m_pScore[n_Score[1] / 10 + 1], m_pScore[n_Score[1] / 10 + 1], 0.0f, 0.3f);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-232.0f, 285.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 24, 24, 64, 64, m_pScore[n_Score[1] - ((n_Score[1] / 10) * 10) + 1], m_pScore[n_Score[1] - ((n_Score[1] / 10) * 10) + 1], 0.0f, 0.3f);
		glPopMatrix();
	}
}
void cSceneMenu::NormalKeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		Power += 0.1f;
		break;
	case '-':
		Power -= 0.1f;
		break;
	case ' ':
		switch (m_nSelectNum)
		{
		case 0:
			SetMode(__D_MODE_NORMAL);
			SetChangeScene(true, "Game");
			break;
		case 1:
			SetMode(__D_MODE_CRAZY);
			SetChangeScene(true, "Game");
			break;
		case 2:
			break;
		}
		break;
	}
}