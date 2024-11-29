#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InitializeScene.h"

void SceneManager::Init()
{
	currentScene = nullptr;

	// �� ���
	RegisterScene(L"InitializeScene", std::make_shared<InitializeScene>());

	// �� �ε�
	LoadScene(L"InitializeScene");
}

void SceneManager::Update()
{
	if (currentScene == nullptr)
		return;
	currentScene->Update();
	currentScene->LateUpdate();
}

void SceneManager::Render(HDC _hdc)
{
	if (currentScene == nullptr)
		return;
	currentScene->Render(_hdc);
}

void SceneManager::RegisterScene(const wstring& sceneName, std::shared_ptr<Scene> scene)
{
	if (sceneName.empty() || scene == nullptr)
		return;
	sceneMap.insert(sceneMap.end(), { sceneName, scene });
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	// ���� ������
	if (currentScene != nullptr)
	{
		currentScene->Release();
		currentScene = nullptr;
	}

	auto iter = sceneMap.find(_sceneName);
	if (iter != sceneMap.end())
	{
		currentScene = iter->second;
		currentScene->Init();
	}
}
