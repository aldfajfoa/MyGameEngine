#pragma once
#include "Engine/GameObject.h"
class Sprite;

class TestScene :
    public GameObject
{
	int hImage_;
	Sprite* sprite;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

