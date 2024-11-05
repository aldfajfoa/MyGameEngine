#include "OverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Sprite.h"

OverScene::OverScene(GameObject* parent)
	:GameObject(parent, "OverScene")
{
}

void OverScene::Initialize()
{
	sprite = new Sprite;
	hImage_ = sprite->Load("Assets\\GAMEOVER.png");
}

void OverScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		SceneManager* pSceneManager = (SceneManager*)(FindObject("SceneManager"));
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void OverScene::Draw()
{
	sprite->Draw(transform_);
}

void OverScene::Release()
{
}
