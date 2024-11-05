#include "Player.h"
#include "Engine/FBX.h"
#include "ChildOden.h"
#include "Engine/Input.h"
#include "Model.h"
#include "SphereCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel = Model::Load("Assets/oden.fbx");
	transform_.position_.y = -4.0;
	transform_.scale_ = { 0.3,0.3,0.3 };
	SphereCollider* col = new SphereCollider(0.1f);
	this->AddCollider(col);
}

void Player::Update()
{
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.01;
	}

	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.01;
	}

	if (Input::IsKeyDown(DIK_H))
	{
		GameObject* p = Instantiate<ChildOden>(this);
		p->SetPosition(transform_.position_);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
}
