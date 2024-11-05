#include "ChildEnemy.h"
#include "Model.h"
#include "SphereCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/SceneManager.h"

ChildEnemy::ChildEnemy(GameObject* parent)
	:GameObject(parent, "ChildEnemy")
{
}

void ChildEnemy::Initialize()
{
	hModel = Model::Load("Assets/Enemy_.fbx");
	transform_.position_.y = 3.0;
	transform_.rotate_.x = 90;
	transform_.rotate_.z = 180;
	transform_.scale_ = { 0.6,0.6,0.6 };
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void ChildEnemy::Update()
{
	transform_.position_.y -= 0.005f;

	Player* player = (Player*)FindObject("Player");

	if (transform_.position_.y <= -5)
	{
		KillMe();
	}
}

void ChildEnemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildEnemy::Release()
{
}

void ChildEnemy::OnCollision(GameObject* pTarget)
{
	Player* p = (Player*)FindObject("Player");
	if (pTarget == p)
	{
		KillMe();
		pTarget->KillMe();
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}
}
