#pragma once
class Scene;
class SceneManager
{
	DECLARE_SINGLE(SceneManager);
public:
	void Init(); // start
	void Update();
	void Render(HDC _hdc);
public:
	void RegisterScene(const wstring& sceneName,
		std::shared_ptr<Scene> scene);
	void LoadScene(const wstring& sceneName);
public:
	const std::shared_ptr<Scene>& GetCurrentScene() const
	{
		return currentScene;
	}
private:
	// ������ map���� ����
	map<wstring, std::shared_ptr<Scene>> sceneMap;
	//Scene* m_pCurrentScene;
	// ���� ��
	std::shared_ptr<Scene> currentScene;
};

