#ifndef __HERO__H__
#define __HERO__H__
struct stPoint_2
{
	float PosX;
	float PosY;
	float PosZ;
};

struct stHero
{
	stPoint_2 stPos;
	float fSize;
	bool  m_bLive;
	int TileNum;
};

class cHero{
private:
	stHero	m_Hero;
public:
	void Init();
	void Draw();
	void Update();
	void Exit();
	void SpecialKeyDown(int key, int x, int y);
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	int	  GetTile();
	void SetHeroLive(bool _Live);
	bool GetHeroLive();
};
#endif
