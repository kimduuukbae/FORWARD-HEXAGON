#ifndef __STDAFX__H__
#define __STDAFX__H__
#include <crtdbg.h>
#include "Define.h"
/// ��� ��������� �̰����� ������

#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//fmod

#include "SceneManager.h"
#include "cSceneLogo.h"
#include "cSceneMenu.h"
#include "cSceneGame.h"

SceneManager* G_SCENE = SceneManager::getInstance();
#endif

