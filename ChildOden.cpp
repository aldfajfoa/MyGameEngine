#include "ChildOden.h"
#include "Player.h"
#include "Engine/FBX.h"
#include "ChildOden.h"
#include "Model.h"
#include "Enemy.h"
#include "SphereCollider.h"
#include "Engine/SceneManager.h"

ChildOden::ChildOden(GameObject* parent)
	:GameObject(parent, "ChildOden")
{
}

void ChildOden::Initialize()
{
	hModel = Model::Load("Assets/oden.fbx");
	transform_.scale_ = { 0.1,0.1,0.1 };
	transform_.position_.x = 0.0f;
	transform_.position_.y = 1.0f;
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void ChildOden::Update()
{
	transform_.position_.y += 0.005f;

	Enemy* enemy = (Enemy*)FindObject("Enemy");

	if (transform_.position_.y >= 9)
	{
		KillMe();
	}
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}

void ChildOden::OnCollision(GameObject* pTarget)
{
	Enemy* e = (Enemy*)FindObject("Enemy");
	if (pTarget == e)
	{
		KillMe();
		pTarget->KillMe();
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}
