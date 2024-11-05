#include "RootJob.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent,"RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	//PlayScene* pPlayScene;
	//pPlayScene = new PlayScene(this);
	//pPlayScene->Initialize();
	//childList_.push_back(pPlayScene);
	Instantiate<SceneManager>(this);
	//↑ここをシーンマネージャーに置き換えてシーン制御を行いたい
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
