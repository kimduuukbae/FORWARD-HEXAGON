#ifndef __MAP__H__
#define __MAP__H__

class cMap{

private:
	float fMapColor[3];
	bool  bMapColor[3];
	int	  nMapPattern;
	int nMapZ;
	float fCurrentZ[2];
	float fDt = 0.0f;
public:
	
	void Init();
	void CreateMap_N_1();			// MAP_1
	void CreateMap_N_2();			// MAP_2			1 AND 2 SCROLL
	void CreateBox(float fX,float fY, float fZ,float Colorf[]);		// MAKE BOX
	void CreateBox(float fX,float  fY, float  fZ, float Colorf[],float Angle);	// MAKE BOX WITH ROTATE
	void CreateBox(float fX, float  fY, float  fZ, float Colorf[], float Angle, int Grad,int Type);	//MAKE BOX WITH GRAD
	void CreateMap_R();			// USED COLOR BY RANDOM
	void Update(float dt, float Speed);				// MOVE Z MAP
	void Exit();				// DELETE MAP
	void SetColor(float c1,float c2, float c3);
};
#endif