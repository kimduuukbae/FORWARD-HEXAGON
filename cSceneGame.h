#include "Scene.h"
#include "Map.h"
#include "Obstacle.h"
#include <fmod.hpp>
#include "cSceneLogo.h"
#include "Hero.h"
#ifndef __SCENE__GAME__H__
#define __SCENE__GAME__H__

class cSceneGame : public Scene
{
private:
	FMOD::System	*m_System;
	FMOD::Sound		*m_Sound;
	FMOD::Channel	*m_Channel = 0;

	BITMAPINFO *m_pBitmap;
	GLubyte*	m_pScore[11];
	float m_NowScore;

	cMap m_Map;
	cHero m_Hero;
	cObstacle m_Obstacle;
	float fDt;
	float m_Speed;
	bool bPause;
public:
	void Init();
	void Update(float dt);
	void Draw();
	void Exit();
	void SpecialKeyDown(int key, int x, int y);
	void NormalKeyDown(unsigned char key, int x, int y);
	void InitScore();
	void ViewScore();
	void SaveScore();
};

#endif