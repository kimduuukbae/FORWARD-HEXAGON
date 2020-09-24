#include <string.h>
#include "Scene.h"
#include "Define.h"
#ifndef __SCNEE_MANAGER_H__
#define __SCENE_MANAGER_H__

class SceneManager{
private:
	SceneManager(){}
	~SceneManager(){ Exit(); }
	static SceneManager *instance;
	char* SceneName;
	Scene* m_CurrentScene;
	int CommitNum;
	int m_nMode;
	char* SceneCommit[__D_SCENE__MAX__];
	Scene* SceneValue[__D_SCENE__MAX__];
private:
	/*�ۿ��� ������ ���� �Լ��� ���� ���*/
public:
	/*
	@Brief : Singleton ���� , �� �Ŵ����� ����մϴ�
	@factor : NULL
	@return : NULL
	*/
	static SceneManager *getInstance(){
		if (instance == 0)
			instance = new SceneManager();
		return instance;
	}
	/*
	@Brief : ������ �� �ڵ����� ��� ���� ������ �ݴϴ�.
	@factor : NULL
	@return : NULL
	*/
	static void *deleteInstance(){
		delete instance;
	}
	/*
	@Brief : ���� �������ݴϴ�.
	@factor : ���� �̸�
	@return : NULL
	*/
	void ChangeScene(char* _SceneName){
		for (int i = 0; i < CommitNum; i++){
			if (strcmp(_SceneName, SceneCommit[i]) == 0){
				m_CurrentScene->Exit();
				m_CurrentScene = SceneValue[i];
				SceneName = _SceneName;
				if (m_nMode != NULL)
					m_CurrentScene->SetMode(m_nMode);
				m_CurrentScene->Init();
				return;
			}
		}
	}
	/*
	@Brief : ���� ���� �̸��� �˾ƿɴϴ�.
	@factor : NULL
	@return : char*
	*/
	char* ReturnScene() { return SceneName; }
	/*
	@Brief : ���� �迭�� �����մϴ�. ù ��° Ŀ���� ���� ó������ �����մϴ�. ���� ����� �Ѳ����� �����˴ϴ�.
	@factor : char* �� �̸� , Scene* �������� �� ��
	@return : NULL
	*/
	void Commit(char* _SceneName, Scene* sValue){
		if (SceneCommit[CommitNum] == NULL){
			SceneCommit[CommitNum] = _SceneName;
			SceneValue[CommitNum] = sValue;
			if (CommitNum == 0){
				m_CurrentScene = SceneValue[0];
				m_CurrentScene->Init();
			}
			CommitNum++;
			printf("Ŀ�Լ��� ! �̸� : %s\n", _SceneName);
		}
	}
	void Init(){ m_CurrentScene->Init(); }
	void Draw(){ m_CurrentScene->Draw();/* DrawFade();*/ }
	void Update(float dt){ 
		if (m_CurrentScene->GetChangeScene() == true)
		{
			SceneName = m_CurrentScene->GetSceneName();
			m_nMode = m_CurrentScene->GetMode();
			ChangeScene(SceneName);
			m_CurrentScene->SetChangeScene(false, "NULL");
		}
		m_CurrentScene->Update(dt); 
	}
	void Exit(){ deleteInstance();}
	void SpeicalKeyDown(int key, int x, int y) {m_CurrentScene->SpecialKeyDown(key, x, y);}
	void NormalKeyDown(unsigned char key, int x, int y) {m_CurrentScene->NormalKeyDown(key, x, y); }
};
SceneManager* SceneManager::instance = NULL;
#endif
