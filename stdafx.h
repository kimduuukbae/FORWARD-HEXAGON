#ifndef __STDAFX__H__
#define __STDAFX__H__
#include <crtdbg.h>
#include "Define.h"
/// 모든 헤더파일은 이곳에서 정리됨

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

