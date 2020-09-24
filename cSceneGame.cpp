#include <GL/glut.h>
//#include <stdio.h>
#include <stdlib.h>
#include "cSceneGame.h"
#include "Define.h"
#include <iostream>
#include <string>
void cSceneGame::Init(){
	FMOD::System_Create(&m_System);
	m_System->init(2, FMOD_INIT_NORMAL, 0);
	if (GetMode() == __D_MODE_NORMAL)
	{
		m_Speed = 20;
		m_System->createSound("Sound/Normal.mp3", FMOD_DEFAULT, 0, &m_Sound);
	}
	else if (GetMode() == __D_MODE_CRAZY)
	{
		m_Speed = 50;
		m_System->createSound("Sound/Crazy.mp3", FMOD_DEFAULT, 0, &m_Sound);
	}
	m_Sound->setMode(FMOD_LOOP_NORMAL);
	m_System->playSound(FMOD_CHANNEL_FREE, m_Sound, FALSE, &m_Channel);

	m_Map.Init();
	m_Obstacle.Init();
	m_Hero.Init();
	bPause = false;
	InitScore();
}
void cSceneGame::Update(float dt){
	if (m_Obstacle.VsCollision(m_Hero.GetPosX(), m_Hero.GetPosY(), m_Hero.GetPosZ(), m_Hero.GetTile()) == true)
	{
		m_Hero.SetHeroLive(false);
		SaveScore();
	}

	if (m_Hero.GetHeroLive() == true && bPause == false)
	{
		if (m_NowScore <= 99.00f)
			m_NowScore += dt;

		if (fDt >= 15.0f)
		{
			m_Speed += 10.0f;
			fDt = 0.0f;
		}
		else
			fDt += dt;

		m_Map.Update(dt, m_Speed);
		if (GetMode() == __D_MODE_CRAZY)
			m_Obstacle.Update(dt, m_Speed, true);
		else
			m_Obstacle.Update(dt, m_Speed, false);
	}
}
void cSceneGame::Draw(){
	glClearColor(0.05f, 0.05f, 0.05f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluPerspective(10.0f, __D__WINDOWS__WIDTH/__D__WINDOWS__HEIGHT, 1.0f, 700.0f);
	gluLookAt(0.0f, -2.0f, -100.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);			// Y -2.0f , Z - 100.0f

	m_Hero.Draw();
	m_Obstacle.Draw();
	m_Map.CreateMap_N_1();
	m_Map.CreateMap_N_2();
	if (bPause == true || m_Hero.GetHeroLive() == false)
		ViewScore();
	glutSwapBuffers();
}
void cSceneGame::Exit(){
	m_Obstacle.Exit();
	//SaveScore();
	m_System->close();
}

void cSceneGame::SpecialKeyDown(int key, int x, int y)
{
	m_Hero.SpecialKeyDown(key, x, y);
}

void cSceneGame::NormalKeyDown(unsigned char key, int x, int y)
{
	if (key == 'a' || key == 'd')
		m_Obstacle.ChangeMonster(key);
	if (key == ' ')
	{
		if (bPause == false)
			bPause = true;
		else
			bPause = false;
	}
	if (key == 27 && (bPause == true || m_Hero.GetHeroLive() == false))
		SetChangeScene(true, "Menu");
}

void cSceneGame::ViewScore()
{
	glPushMatrix();
	glScalef(0.2f, 0.2f, 1.0f);
	glTranslatef(0.0f, 0.0f, -20.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	UseBitmap(GL_TEXTURE_2D, 40, 20, 400, 200, m_pScore[0], m_pScore[0], 0.0f, 0.0f);
	glPopMatrix();

		int Show = m_NowScore;
		glPushMatrix();
		glScalef(0.1f, 0.1f, 1.0f);
		glTranslatef(-6.0f,-13.5f,-21.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 10, 10, 64, 64, m_pScore[Show / 10 + 1], m_pScore[Show / 10 + 1], 0.0f, 0.3f);
		glPopMatrix();
		glPushMatrix();
		glScalef(0.1f, 0.1f, 1.0f);
		glTranslatef(-16.0f,-13.5f,-21.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		UseBitmap(GL_TEXTURE_2D, 10, 10, 64, 64, m_pScore[Show - ((Show / 10) * 10) + 1], m_pScore[Show - ((Show / 10) * 10) + 1], 0.0f, 0.3f);
		glPopMatrix();
}
void cSceneGame::InitScore()
{
	m_NowScore = 0.0f;
	m_pScore[0] = LoadDIBitmap("ingame.bmp", &m_pBitmap);
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
}

void cSceneGame::SaveScore()
{
	FILE *fp;
	if (GetMode() == __D_MODE_CRAZY)
		fp = fopen("Ranking/Crazy_Ranking.txt", "r+");
	else
		fp = fopen("Ranking/Normal_Ranking.txt", "r+");

	int Score;
	fscanf(fp, "%d", &Score);
	fclose(fp);
	if (Score <= (int)m_NowScore)
	{
		if (GetMode() == __D_MODE_CRAZY)
			fp = fopen("Ranking/Crazy_Ranking.txt", "w+");
		else
			fp = fopen("Ranking/Normal_Ranking.txt", "w+");
		fprintf(fp, "%d", (int)m_NowScore);

		fclose(fp);
	}

}