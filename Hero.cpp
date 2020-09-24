#include "Hero.h"
#include <GL\glut.h>
void cHero::Init()
{
	m_Hero.stPos.PosX = 2.4f;
	m_Hero.stPos.PosY = -25.0f;
	m_Hero.stPos.PosZ = -90.0f;
	m_Hero.fSize = 0.2f;
	m_Hero.m_bLive = true;
	m_Hero.TileNum = 0;
}

void cHero::Update()
{

}

void cHero::Draw()
{
	glPushMatrix();
	glScalef(m_Hero.fSize, m_Hero.fSize, m_Hero.fSize);
	glTranslatef(m_Hero.stPos.PosX, m_Hero.stPos.PosY, m_Hero.stPos.PosZ);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	if (m_Hero.m_bLive == true)
		glColor3f(0.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 0.0f, 0.0f);
	glutWireDodecahedron();
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidDodecahedron();
	glPopMatrix();
}

void cHero::Exit()
{


}
void cHero::SpecialKeyDown(int key, int x, int y)
{
	if (m_Hero.m_bLive == true)
	{
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			if (m_Hero.stPos.PosX >= -7.2f)
			{
				m_Hero.stPos.PosX -= 4.6f;
				m_Hero.TileNum--;
			}
			break;
		case GLUT_KEY_LEFT:
			if (m_Hero.stPos.PosX <= 7.2f)
			{
				m_Hero.stPos.PosX += 4.6f;
				m_Hero.TileNum++;
			}
			break;
		}
	}
}
float cHero::GetPosX()
{
	return m_Hero.stPos.PosX;
}
float cHero::GetPosY()
{
	return m_Hero.stPos.PosY;
}
float cHero::GetPosZ()
{
	return m_Hero.stPos.PosZ;
}

void cHero::SetHeroLive(bool _Live)
{
	m_Hero.m_bLive = false;
}
bool cHero::GetHeroLive()
{
	return m_Hero.m_bLive;
}
int cHero::GetTile()
{
	return m_Hero.TileNum;
}