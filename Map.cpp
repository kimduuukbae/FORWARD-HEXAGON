#include "Map.h"
#include <GL/glut.h>
#include <stdio.h>
void cMap::Init()
{
	fCurrentZ[0] = -250.0f; fCurrentZ[1] = 1090.0f;
	fMapColor[0] = 0.2f;
	fMapColor[1] = 0.0f;
	fMapColor[2] = 0.0f;
	nMapPattern = 1;
}
void cMap::CreateMap_N_1(){
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, fCurrentZ[0]);
	/*
		BOTTOM
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox((j-2.5f), -6.0f, 3.0f + (k*1.05f),fMapColor,0.0f,k,1);
		}
	}
	/*
		LEFT_BOTTOM	
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*0.7f) + 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f),fMapColor,45.0f,k,1);
		}
	}
	/*
		LEFT_TOP	
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*-0.7f) + 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f),fMapColor,45.0f,k,1);
		}
	}
	/* 
		TOP	
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox((j - 2.5f), 3.5f, 3.0f + (k*1.05f), fMapColor,0.0f,k,1);
		}
	}
	/*
		RIGHT_TOP	
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*0.7f) - 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f,k,1);
		}
	}
	/*
		RIGHT_BOTTOM
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*-0.7f) - 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f,k,1);
		}
	}
	glPopMatrix();
}
void cMap::CreateMap_N_2()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, fCurrentZ[1]);
	/*
	BOTTOM
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox((j - 2.5f), -6.0f, 3.0f + (k*1.05f), fMapColor, 0.0f, k, 2);
		}
	}
	/*
	LEFT_BOTTOM
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*0.7f) + 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f, k, 2);
		}
	}
	/*
	LEFT_TOP
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*-0.7f) + 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f, k, 2);
		}
	}
	/*
	TOP
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox((j - 2.5f), 3.5f, 3.0f + (k*1.05f), fMapColor, 0.0f, k, 2);
		}
	}
	/*
	RIGHT_TOP
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*0.7f) - 7.3f), -0.54f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f, k, 2);
		}
	}
	/*
	RIGHT_BOTTOM
	*/
	for (int j = 0; j < 6; j++)
	{
		for (int k = 0; k < 16; k++)
		{
			CreateBox(((j*-0.7f) - 3.8f), -5.5f + (j*0.7f), 3.0f + (k*1.05f), fMapColor, 45.0f, k, 2);
		}
	}
	glPopMatrix();
}
void cMap::CreateMap_R(){

}
//
void cMap::Update(float dt, float Speed){
	fCurrentZ[0] -= 5.0f * dt * Speed;
	fCurrentZ[1] -= 5.0f * dt * Speed;
	if (fCurrentZ[0] <= -1640.0f)
	{
		fCurrentZ[0] = 1040.0f;
		nMapPattern++;
		if (nMapPattern > 6)
			nMapPattern = 1;
	}
	if (fCurrentZ[1] <= -1640.0f)
		fCurrentZ[1] = 1040.0f;
}
void cMap::Exit(){


}
void cMap::CreateBox(float fX, float fY, float fZ, float Colorf[])
{
	glPushMatrix();
	glScalef(1.0f, 1.0f, 80.0f);
	glTranslatef(fX, fY, fZ);
	glLineWidth(1.5f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(1.01f);
	glColor3f(Colorf[0], Colorf[1], 0.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
}
void cMap::CreateBox(float fX, float fY, float fZ, float Colorf[],float Angle)
{
	glPushMatrix();
	glScalef(1.0f, 1.0f, 80.0f);
	glTranslatef(fX, fY, fZ);
	glRotatef(Angle, 0.0f, 0.0f, 1.0f);
	glLineWidth(1.5f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(1.01f);
	glColor3f(1 - Colorf[0], Colorf[1], 0.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
}
void cMap::CreateBox(float fX, float fY, float fZ, float Colorf[], float Angle, int Grad,int Type)
{
	glPushMatrix();
	glScalef(1.0f, 1.0f, 80.0f);
	glTranslatef(fX, fY, fZ);
	glRotatef(Angle, 0.0f, 0.0f, 1.0f);
	glLineWidth(1.5f);
	glColor3f(0.8f, 0.8f, 0.8f);
	glutWireCube(1.01f);
	switch (nMapPattern)
	{
	case 1:
		if (Type == 1)
			glColor3f(0.7f - ((float)Grad * 0.0325f), 0.0f, 0.0f);
		else if (Type == 2)
			glColor3f(0.0f + ((float)Grad * 0.0325f), 0.0f, 0.0f);
		break;
	case 2:
		if (Type == 1)
			glColor3f(0.7f - ((float)Grad * 0.033f), 0.35 - ((float)Grad * 0.033f), 0.0f);
		else if (Type == 2)
			glColor3f(0.0f + ((float)Grad * 0.033f),((float)Grad * 0.033f)/2, 0.0f);
		break;
	case 3:
		if (Type == 1)
			glColor3f(0.7f - ((float)Grad * 0.033f), 0.7f - ((float)Grad * 0.033f), 0.0f);
		else if (Type == 2)
			glColor3f(((float)Grad * 0.033f), ((float)Grad * 0.033f), 0.0f);
		break;
	case 4:
		if (Type == 1)
			glColor3f(0.0f, 0.7f - ((float)Grad * 0.033f), 0.0f);
		else if (Type == 2)
			glColor3f(0.0f, ((float)Grad * 0.033f), 0.0f);
		break;
	case 5:
		if (Type == 1)
			glColor3f(0.0f, 0.0f, 0.7f - ((float)Grad * 0.033f));
		else if (Type == 2)
			glColor3f(0.0f, 0.0f, ((float)Grad * 0.033f));
		break;
	case 6:
		if (Type == 1)
			glColor3f(0.7f - ((float)Grad * 0.033f), 0.0f, 0.7f - ((float)Grad * 0.033f));
		else if (Type == 2)
			glColor3f(((float)Grad * 0.033f), 0.0f, ((float)Grad * 0.033f));
		break;
	}
	glutSolidCube(1.0f);
	glPopMatrix();
}

void cMap::SetColor(float c1 ,float c2, float c3)
{
	fMapColor[0] = c1;
	fMapColor[1] = c2;
	fMapColor[2] = c3;
}