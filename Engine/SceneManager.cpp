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
    //�V�[�������ۂɐ؂�ւ���
    //���݂̃V�[���ƁA�l�N�X�g�V�[�����ʂ�������؂�ւ�
    if (currentSceneID_ != nextSceneID_)
    {
        //���̃V�[���̃I�u�W�F�N�g��S�폜(�q�I�u�W�F�N�g��S�č폜)
        auto delScene = childList_.begin();
        (*delScene)->ReleaseSub();
        SAFE_DELETE(*delScene);
        childList_.clear();
        Model::Release();

        //���̃V�[�����쐬
        switch (nextSceneID_)
        {
        case SCENE_ID_TEST:  Instantiate<TestScene>(this); break;
        case SCENE_ID_PLAY:  Instantiate<PlayScene>(this); break;
        case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
        case SCENE_ID_OVER:  Instantiate<OverScene>(this); break;
        }
        //�����V�[���𐶐��o������A�J�����g�V�[�����X�V
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
