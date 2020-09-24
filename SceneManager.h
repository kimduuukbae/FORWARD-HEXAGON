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
	/*밖에서 사용되지 않을 함수들 선언 장소*/
public:
	/*
	@Brief : Singleton 패턴 , 씬 매니저로 사용합니다
	@factor : NULL
	@return : NULL
	*/
	static SceneManager *getInstance(){
		if (instance == 0)
			instance = new SceneManager();
		return instance;
	}
	/*
	@Brief : 종료할 때 자동으로 모든 값을 제거해 줍니다.
	@factor : NULL
	@return : NULL
	*/
	static void *deleteInstance(){
		delete instance;
	}
	/*
	@Brief : 씬을 변경해줍니다.
	@factor : 씬의 이름
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
	@Brief : 현재 씬의 이름을 알아옵니다.
	@factor : NULL
	@return : char*
	*/
	char* ReturnScene() { return SceneName; }
	/*
	@Brief : 씬을 배열에 저장합니다. 첫 번째 커밋한 씬이 처음으로 시작합니다. 게임 종료시 한꺼번에 삭제됩니다.
	@factor : char* 씬 이름 , Scene* 재정의한 씬 값
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
			printf("커밋성공 ! 이름 : %s\n", _SceneName);
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
