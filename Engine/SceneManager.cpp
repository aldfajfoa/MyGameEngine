#include "SceneManager.h"
#include "../TestScene.h"
#include "../PlayScene.h"
#include "../OverScene.h"
#include "../ClearScene.h"
#include "Direct3D.h"
#include "../Model.h"

SceneManager::SceneManager(GameObject* parent)
    :GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
    //シーンを実際に切り替える
    //現在のシーンと、ネクストシーンが別だったら切り替え
    if (currentSceneID_ != nextSceneID_)
    {
        //そのシーンのオブジェクトを全削除(子オブジェクトを全て削除)
        auto delScene = childList_.begin();
        (*delScene)->ReleaseSub();
        SAFE_DELETE(*delScene);
        childList_.clear();
        Model::Release();

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_TEST:  Instantiate<TestScene>(this); break;
        case SCENE_ID_PLAY:  Instantiate<PlayScene>(this); break;
        case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
        case SCENE_ID_OVER:  Instantiate<OverScene>(this); break;
        }
        //無事シーンを生成出来たら、カレントシーンを更新
        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID next)
{
    nextSceneID_ = next;
}
