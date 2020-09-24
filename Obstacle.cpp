#include "Obstacle.h"
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
void cObstacle::Init()
{
	fDt = 0.0f;
	SetPattern();
	CreateMonster();
	srand(time(NULL));
}
void cObstacle::Update(float dt, float Speed,bool _MODE)
{
	for (int i = 0; i < 19; i++)
	{
		if (m_bPattern_On_Normal[i] == true)
		{
			m_fPatternSpeed[i] -= 5.0f * dt * Speed;
			if (m_fPatternSpeed[i] <= -600.0f)
			{
				m_fPatternSpeed[i] = 0.0f;
				m_bPattern_On_Normal[i] = false;
			}
		}
	}
	if (_MODE == false)
	{
		if (fDt >= 2.8f - (Speed * 0.015f))
		{
			SetSpawn();
			fDt = 0.0f;
		}
		else
			fDt += dt;
	}
	else
	{
		if (fDt >= 1.3f - (Speed * 0.007f))
		{
			SetSpawn();
			fDt = 0.0f;
		}
		else
			fDt += dt;
	}
}
void cObstacle::Draw()
{
	for (int i = 0; i < 19; i++)
	{
		if (m_bPattern_On_Normal[i] == true)
		{
			for (int j = 0; j < 6; j++)
			{
				glPushMatrix();
				glTranslatef(0.0f, 0.0f, 500.0f + m_fPatternSpeed[i]);
				for (int k = 0; k < 6; k++)
				{
					if (m_Monster[i][j][k].m_bLive == true)
					{
						glColor3f(0.0f, 0.0f, 0.0f);
						glPushMatrix();
						glScalef(1.0f, 1.0f, 20.0f);
						glTranslatef(m_Monster[i][j][k].m_Pos.nX, m_Monster[i][j][k].m_Pos.nY, 0.0f);
						if (j == 1 || j == 2 || j == 4 || j == 5)
							glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
						glutWireCube(1.06f);
						glColor3f(0.8f, 0.8f, 0.8f);
						glutSolidCube(1.0f);
						glPopMatrix();
					}
				}
				glPopMatrix();
			}
		}
	}
}

void cObstacle::Exit()
{
	for (int i = 0; i < 19; i++)
	{
		m_bPattern_On_Normal[i] = false;
		m_fPatternSpeed[i] = 0.0f;
	}
}
void cObstacle::SetSpawn()
{
	int nCount = 0;
	while ( 1 )
	{
		m_nRandomPattern = rand() % 19;
		if (m_bPattern_On_Normal[m_nRandomPattern] == false)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					m_Monster[m_nRandomPattern][j][k].m_bLive = m_bPattern_Normal[m_nRandomPattern][j][k];
				}
			}
			m_bPattern_On_Normal[m_nRandomPattern] = true;
			break;
		}
		nCount++;
		if (nCount > 19)
			break;
	}
}

void cObstacle::CreateMonster()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				switch (j)
				{
				case 0:		//BOTTOM
					m_Monster[i][j][k].m_Pos.nX = k - 2.5f;
					m_Monster[i][j][k].m_Pos.nY = -5.0f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				case 1:		//BOTTOM_LEFT CreateBox(((j*0.7f) + 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f),fMapColor,45.0f);
					m_Monster[i][j][k].m_Pos.nX = (k*0.7f) + 3.15f;
					m_Monster[i][j][k].m_Pos.nY = (k*0.7f) - 4.8f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				case 2:		//TOP_LEFT CreateBox(((j*-0.7f) + 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f),fMapColor,45.0f);
					m_Monster[i][j][k].m_Pos.nX = (k*-0.7f) + 6.7f;
					m_Monster[i][j][k].m_Pos.nY = (k*0.7f) - 1.24f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				case 3:		//TOP
					m_Monster[i][j][k].m_Pos.nX = k - 2.5f;
					m_Monster[i][j][k].m_Pos.nY = 2.5f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				case 4:		//TOP_RIGHT	CreateBox(((j*0.7f) - 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f);
					m_Monster[i][j][k].m_Pos.nX = (k*0.7f) - 6.7f;
					m_Monster[i][j][k].m_Pos.nY = (k*0.7f) - 1.24f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				case 5:		//BOTTOM_RIGHT CreateBox(((j*-0.7f) - 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f);
					m_Monster[i][j][k].m_Pos.nX = (k*-0.7f) - 3.15f;
					m_Monster[i][j][k].m_Pos.nY = (k*0.7f) - 4.8f;
					//m_Monster[i][j][k].m_Pos.nZ = 500.0f;
					break;
				}
			}
		}
	}
}

void cObstacle::SetPattern()
{
	FILE *fp;
	fp = fopen("Pattern/Pattern_Normal.txt", "r");
	if (fp == NULL)
		printf("왜 파일이 없는거죠? 끄겠슴다\n");
	else
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					fscanf(fp, "%d ", &m_bPattern_Normal[i][j][k]);
				}
				fscanf(fp, "\n");
			}
			fscanf(fp, "\n");
		}
	}
	fclose(fp);
}
void cObstacle::ChangeMonster(int _Direction)
{
	bool TempArray[19][6][6];
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
				TempArray[i][j][k] = m_bPattern_Normal[i][j][k];
		}
	}
	if (_Direction == 'd')
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					if (j == 0)
						m_bPattern_Normal[i][j][k] = TempArray[i][5][k];
					else
						m_bPattern_Normal[i][j][k] = TempArray[i][j - 1][k];

				}
			}
		}
	}
	else if (_Direction == 'a')
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					if (j == 5)
						m_bPattern_Normal[i][j][k] = TempArray[i][j - 5][k];
					else
						m_bPattern_Normal[i][j][k] = TempArray[i][j + 1][k];
				}
			}
		}
	}

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
				m_Monster[i][j][k].m_bLive = m_bPattern_Normal[i][j][k];
		}
	}
}


bool cObstacle::VsCollision(float fX, float fY, float fZ, int TileNum)
{
	for (int i = 0; i < 19; i++)
	{
		if (m_bPattern_On_Normal[i] == true)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					if (m_Monster[i][j][k].m_bLive == true)		// 4.6씩 이동함
					{
							// Hero = -90.0f
						if (m_Monster[i][j][k].m_Pos.nX + 0.1f >= 0.5f + (TileNum * 1.0f) && m_Monster[i][j][k].m_Pos.nX - 0.1f <= 0.5f + (TileNum * 1.0f) &&
							m_Monster[i][j][k].m_Pos.nY + 0.1f >= fY + 20.0f && m_Monster[i][j][k].m_Pos.nY - 0.1f <= fY + 20.0f &&
							500.0f + m_fPatternSpeed[i] - 90.0f - 10.0f <= fZ && 500.0f + m_fPatternSpeed[i] - 90.0f >= fZ)
							return true;
					}
				}
			}
		}
	}
	return false;
}