#include "Scene.h"
#include <fmod.hpp>
#ifndef __SCENE__MENU__H__
#define __SCENE__MENU__H__

class cSceneMenu : public Scene
{
private:
	float fDt,PosDt;
	float nPos,PosY;
	float buttonXPos[2];
	float Power;
	int m_nSelectNum;
	int n_Score[2];

	GLboolean m_bButtonOn[4];
	GLubyte*	m_pBackGround;
	GLubyte*	m_pSpace;
	GLubyte*	m_pSelect[3];
	GLubyte*	m_pButton[2];
	BITMAPINFO *m_pBitmap;
	GLubyte*	m_pScore[11];


	FMOD::System	*m_System;
	FMOD::Sound		*m_Sound;
	FMOD::Channel	*m_Channel = 0;


public:
	void ButtonManager(float dt);
	void Init();
	void Update(float dt);
	void Draw();
	void Exit();
	void SpecialKeyDown(int key, int x, int y);
	void NormalKeyDown(unsigned char key, int x, int y);
	void ViewScore();
	void InitScore();
};

#endif