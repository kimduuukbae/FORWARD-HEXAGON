#ifndef __OBSTACLE__H__
#define __OBSTACLE__H__
struct stPoint
{
	float nX;
	float nY;
	float nZ;
};
struct stObstacle
{
	stPoint	m_Pos;
	bool	m_bLive;
};
class cObstacle{
private:
	float fDt;
	stObstacle m_Monster[19][6][6];
	bool	m_bPattern_Normal[19][6][6];
	bool	m_bPattern_On_Normal[19];
	float	m_fPatternSpeed[19];
	int		m_nRandomPattern;
public:

	void Init();
	void Update(float dt, float Speed,bool	_MODE);
	void Draw();
	void Exit();
	void SetSpawn();
	void SetColor();
	void SetPattern();
	void ChangeMonster(int _Direction);
	void CreateMonster();
	bool VsCollision(float fX, float fY, float fZ, int TileNum);
};
#endif