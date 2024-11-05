#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene")
{
}

void ClearScene::Initialize()
{
	sprite = new Sprite;
	hImage_ = sprite->Load("Assets\\CLEAR.png");
}

void ClearScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)(FindObject("SceneManager"));
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void ClearScene::Draw()
{
	sprite->Draw(transform_);
}

void ClearScene::Release()
{
}
