#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <cstdlib>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/RootJob.h"
#include "Engine/Input.h"
#include "Model.h"
#include "string"

#pragma comment(lib, "d3d11.lib")//�����J
#pragma comment(lib, "winmm.lib")

//�萔�錾
const wchar_t* WIN_CLASS_NAME = L"SampleGame";//�E�B���h�E�N���X��
const wchar_t* APP_NAME = L"�T���v���Q�[��";   //�A�v���P�[�V������

RootJob* pRootJob = nullptr;//���[�g�W���u(�S�Ă̐e)��錾

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;          //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc); //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
//(�\���̈��WINDOW_WIDTHxWINDOW_HEIGHT�Ɏw�肷�邽�߂̌v�Z�j
	RECT winRect = { 0, 0, Direct3D::WINDOW_WIDTH, Direct3D::WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;   //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;   //�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,      //�E�B���h�E�N���X��
		APP_NAME,			 //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                //�E�B���h�E��
		winH,                //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);
	//Direct3D������
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"DirectX�̏������Ɏ��s", NULL, MB_OK);
		return 0;
	}

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	Camera::Initialize();

	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;
			static DWORD countFps = 0;
			timeEndPeriod(1);

			if (nowTime - startTime >= 1000) {
				std::wstring str;
				wsprintf(str.data(), L"%u", nowTime - startTime);
				SetWindowTextW(hWnd, str.c_str());

				countFps = 0;
				startTime = nowTime;
			}
			if (nowTime - lastUpdateTime <= 1000.0f / 60.0f) 
			{
				continue;//1/60�b�o���Ă��Ȃ��̂ŃX���[
			}
			lastUpdateTime++;

			//�J�������X�V
			Camera::Update();

			//���͏��̏���
			Input::Update();
			pRootJob->UpdateSub();

			//�`��̊J�n����
			Direct3D::BeginDraw();

			//���[�g�W���u����q����S�ẴI�u�W�F�N�g��Draw����
			pRootJob->DrawSub();

			//�`��̏I������
			Direct3D::EndDraw();
		}
	}

	Model::Release();
	pRootJob->ReleaseSub();
	Input::Release();
	Direct3D::Release();

	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}