#pragma once
#include "Engine/GameObject.h"

class FBX;

class ChildOden :
    public GameObject
{
	int hModel;
public:
	ChildOden(GameObject* parent);

	void Initialize();
	void Update();
	void Draw();
	void Release();
	void OnCollision(GameObject* pTarget) override;
};

