#pragma once
#include "Engine/GameObject.h"

class Fbx;//�O���錾 

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

