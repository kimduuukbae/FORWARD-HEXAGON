#ifndef __OPTION__H__
#define __OPTION__H__

#include <fmod.hpp>

struct stPoint
{
	float xPos;
	float yPos;
	float zPos;
};
struct stOption
{
	stPoint m_stPos;
	bool	m_bLive;
};

class cMap{
private:
	stOption	m_Option;

	GLubyte*	m_pLogo;
	BITMAPINFO *m_pBitmap;

public:

	void Init();
	void Update(float dt);
	void Draw();
	void Exit();
};
#endif