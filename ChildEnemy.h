#pragma once
#include "Engine/GameObject.h"
class ChildEnemy :
    public GameObject
{
	int hModel;
public:
	ChildEnemy(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject* pTarget) override;
};

