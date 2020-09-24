#pragma once
#include "Scene.h"
#include "Map.h"
#include <fmod.hpp>

#ifndef __SCENE__LOGO__H__
#define __SCENE__LOGO__H__
class cSceneLogo : public Scene
{
private:
	FMOD::System	*m_System;
	FMOD::Sound		*m_Sound;
	FMOD::Channel	*m_Channel = 0;

	GLubyte*	m_pLogo;
	BITMAPINFO *m_pBitmap;

public:
	void Init();
	void Update(float dt);
	void Draw();
	void Exit();
	void SpecialKeyDown(int key, int x, int y);
	void NormalKeyDown(unsigned char key, int x, int y);
};

#endif