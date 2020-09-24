#ifndef __SCENE__H__
#define __SCENE__H__

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
class Scene{
private:
	float Max(float value1, float value2){ return value1 > value2 ? value1 : value2; }
	float Min(float value1, float value2){ return value1 < value2 ? value1 : value2; }
	float Clamp(float value, float min, float max) { return Max(min, Min(max, value)); }
	float Lerp(float value1, float value2, float amount){ return (value1 + (value2 - value1) * amount); }
	bool	m_bCheck = false;
	char*	m_bName;
	int		m_nMode;
public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;			//dt = deltatime
	virtual void Draw() = 0;
	virtual void Exit() = 0;
	virtual void SpecialKeyDown(int key, int x, int y) = 0;
	virtual void NormalKeyDown(unsigned char key, int x, int y) = 0;
	/*
		@Brief : 비트맵을 불러오는 함수입니다.
		@factor : 파일이름, info값 저장 변수
		@return : info
	*/
	virtual GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info)
	{
		FILE *fp;
		GLubyte *bits;
		int bitsize, infosize;
		char FolderName[40] = "Image/";
		strcat(FolderName, filename);
		BITMAPFILEHEADER header;
		if ((fp = fopen(FolderName, "rb")) == NULL)
			return NULL;
		if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
			fclose(fp);
			return NULL;
		}
		if (header.bfType != 'MB') {
			fclose(fp);
			return NULL;
		}
		infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
		if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
			fclose(fp);
			exit(0);
			return NULL;
		}
		if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
			free(*info);
			fclose(fp);
			return NULL;
		}
		if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
			bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.0 *
			abs((*info)->bmiHeader.biHeight);
		if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
			free(*info);
			fclose(fp);
			return NULL;
		}
		if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
			free(*info); free(bits);
			fclose(fp);
			return NULL;
		}
		fclose(fp);
		return bits;
	}

	/*
		@Brief : 비트맵을 사용하는 함수입니다 ( 블렌딩 X)
		@factor : 텍스쳐타입, X사이즈,Y사이즈,사진의 X크기,사진의 Y크기,시작 포인터,종료포인터,회전값
		@return : NULL
	*/
	virtual GLvoid   UseBitmap(GLint _TexTureType, GLint _nX, GLint _nY, GLint _tSizeX, GLint _tSizeY, GLubyte* _Start, GLubyte* _End, GLfloat _Angle,GLfloat _Z)
	{
		glPushMatrix();
		glRotatef(_Angle, 0.0f, 0.0f, 1.0f);
		glTexImage2D(_TexTureType, 0, 3, _tSizeX, _tSizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _Start);
		glTexParameteri(_TexTureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(_TexTureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(_TexTureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(_TexTureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glEnable(_TexTureType);

		glColor3f(1.0f, 1.0f, 1.0f);
		glTexImage2D(_TexTureType, 0, 3, _tSizeX, _tSizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _End);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-_nX/2, _nY/2, _Z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_nX / 2, _nY / 2, _Z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(_nX / 2, -_nY / 2, _Z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-_nX / 2, -_nY / 2, _Z);
		}
		glEnd();

		glDisable(_TexTureType);
		glPopMatrix();
	}
	/*
	@Brief : 비트맵을 사용하는 함수입니다 ( 블렌딩 O)
	@factor : 텍스쳐타입, X사이즈,Y사이즈,사진의 X크기,사진의 Y크기,앞면포인터,뒷면포인터,회전값
	@return : NULL
	*/
	virtual GLvoid   UseBitmapToBlend(GLint _TexTureType, GLint _nX, GLint _nY, GLint _tSizeX, GLint _tSizeY, GLubyte* _Foward, GLubyte* _Back, GLfloat _Angle,GLfloat _Z)
	{
		glEnable(GL_BLEND);
		glPushMatrix();
		glRotatef(_Angle, 0.0f, 0.0f, 1.0f);
		glTexImage2D(_TexTureType, 0, 3, _tSizeX, _tSizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _Foward);
		glTexParameteri(_TexTureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(_TexTureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(_TexTureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(_TexTureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glEnable(_TexTureType);
		glBlendFunc(GL_DST_COLOR, GL_ONE);
		glTexImage2D(_TexTureType, 0, 3, _tSizeX, _tSizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _Back);
		glBegin(GL_QUADS);
		{
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-_nX / 2, _nY / 2, _Z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_nX / 2, _nY / 2, _Z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(_nX / 2, -_nY / 2, _Z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-_nX / 2, -_nY / 2, _Z);
		}
		glEnd();
		glBlendFunc(GL_ONE, GL_ONE);
		glTexImage2D(_TexTureType, 0, 3, _tSizeX, _tSizeY, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _Foward);
		glBegin(GL_QUADS);
		{
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-_nX / 2, _nY / 2, _Z+0.1f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(_nX / 2, _nY / 2, _Z+0.1f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(_nX / 2, -_nY / 2, _Z+0.1f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-_nX / 2, -_nY / 2, _Z+0.1f);
		}
		glEnd();

		glDisable(_TexTureType);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	/*
		@Brief : 스무스 스텝입니다.
		@factor : value1 = 움직일 물체의 좌표! , value2 = 갈 곳 까지의 좌표! , amount = 속도 !
		@return : float
	*/
	virtual float SmoothStep(float value1, float value2, float amount)
	{
		float num = Clamp(amount, 0.0f, 1.0f);
		return Lerp(value1, value2, (num*num) * (3.0f - (2.0f * num)));
	}
	/*
		@Brief : 각 씬 에서도 씬을 변경해 줄 수 있습니다.
		@factor : _Set == TRUE일 시 씬변경, _SceneName == 변경할 씬 네임,	_Mode = 모드 (기본 NULL)
		@return : NULL
	*/
	virtual void SetChangeScene(bool _Set, char* _SceneName){ m_bCheck = _Set; m_bName = _SceneName;}
	bool GetChangeScene(){ 
		if (m_bCheck == true)
			return true;
		else
			return false;
	}
	char* GetSceneName(){ return m_bName; }
	int		GetMode(){ return m_nMode; }
	void	SetMode(int _Mode){ m_nMode = _Mode; }
};

#endif