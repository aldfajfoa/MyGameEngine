#include "Enemy.h"
#include "Model.h"
#include "SphereCollider.h"
#include "Engine/Input.h"
#include "ChildEnemy.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Assets/Enemy_.fbx");
	transform_.position_.y = 3.0;
	transform_.rotate_.x = 90;
	transform_.rotate_.z = 180;
	transform_.scale_ = { 1.3,1.3,1.3 };
	SphereCollider* col = new SphereCollider(0.1f);
	this->AddCollider(col);
}

void Enemy::Update()
{
	static int dt;
	dt++;
	float nTime = dt / (60.0f * 10.0f) - 2.0;
	transform_.position_.x = 4.0 * sin(nTime);

	int num = rand() % 300;
	if (Input::IsKeyDown(DIK_G)||num==1)
	{
		GameObject* e = Instantiate<ChildEnemy>(this);
		e->SetPosition(transform_.position_);
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
