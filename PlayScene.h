#pragma once
#include "Engine/GameObject.h"

class Fbx;//‘O•ûéŒ¾ 

class PlayScene :
    public GameObject
{
public:
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

