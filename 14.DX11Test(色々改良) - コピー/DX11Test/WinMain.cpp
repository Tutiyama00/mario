#include<crtdbg.h>

#include <Windows.h>
#include"Vertex.h"
#include"Sound.h"
#include"GameManager.h"
#include<sstream>

HWND  g_hwnd               = nullptr;
const UINT G_WINDOW_WIDTH  = 1000;
const UINT G_WINDOW_HEIGHT = 750;
MSG   g_msg = {0};
LPDIRECTSOUNDBUFFER g_BGMdirectSoundBuffer = nullptr;
char* g_baseClassName = (char*)"Base_Window";

const float G_MIN_FREAM_TIME = 1.0f / 60;
float g_frameTime = 0;
LARGE_INTEGER g_timeStart;
LARGE_INTEGER g_timeEnd;
LARGE_INTEGER g_timeFrequency;
float g_fps = 0;
DWORD g_sleepTime = 0;

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK BaseWindProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT MainLoop();
void FrameControl();

/*
hInstance�@�@ = ���݂̃C���X�^���X�̃n���h��
hInstancePrev = �ȑO�̃C���X�^���X�̃n���h��
pCmdLine      = �R�}���h���C��(���s�t�@�C���̃p�X�Ƃ��f�[�^�t�@�C���̃p�X������)
nCmdShow      = �E�B���h�E�̕\�����
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	//���������[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�B���h�E�N���X�\���̂̐ݒ�
	WNDCLASSEX wc = { 0 };
	wc.cbSize               = sizeof(wc);                          //WNDCLASSEX�\���̂̃T�C�Y
	wc.style                = CS_HREDRAW | CS_VREDRAW;             //�E�B���h�E�X�^�C��
	wc.lpfnWndProc          = BaseWindProc;                        //�E�B���h�E�v���V�[�W���̃A�h���X
	wc.cbClsExtra           = 0;                                   //�N���X�\���́A�E�B���h�E�\���̂̒ǉ��̈���o�C�g�P�ʂŗ\�񂷂���́�
	wc.cbWndExtra           = 0;                                   //���ʏ�͂O���w�肷��
	wc.hInstance            = hInstance;                           //WinMain()�̃C���X�^���X�n���h��
	wc.hIcon                = LoadIcon(nullptr, IDI_APPLICATION);  //�g�p����A�C�R���̃n���h��
	wc.hCursor              = LoadCursor(nullptr, IDC_ARROW);      //�g�p����}�E�X�J�[�\���̃n���h��
	wc.hbrBackground        = (HBRUSH)(COLOR_BACKGROUND);          //�E�B���h�E�̃N���C�A���g�̈�̔w�i�F
	wc.lpszMenuName         = nullptr;                             //���j���[
	wc.lpszClassName        = g_baseClassName;                     //���̃E�B���h�E�N���X�̖��O
	wc.hIconSm              = nullptr;                             //�g�p���鏬�����A�C�R��

	//�E�B���h�E�N���X�\���̂̓o�^
	if (!RegisterClassEx(&wc)) { return -1; }

	//�E�B���h�E�̍쐬
	g_hwnd = CreateWindowEx(
		WS_EX_LEFT,             //�g���E�B���h�E�X�^�C��
		g_baseClassName,        //�o�^����Ă���E�B���h�E�N���X��
		"�e�X�g",               //�쐬����E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,    //�E�B���h�E�X�^�C��
		0,                      //�E�B���h�E�̉������̈ʒu
		0,                      //�E�B���h�E�̏c�����̈ʒu
		G_WINDOW_WIDTH,         //�E�B���h�E�̕�
		G_WINDOW_HEIGHT,        //�E�B���h�E�̍���
		0,                      //�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		0,                      //���j���[�n���h���܂��͎q���ʎq
		hInstance,              //�A�v���P�[�V�����C���X�^���X�̃n���h��
		0                       //�E�B���h�E�쐬�f�[�^
	);

	//�E�B���h�E���������쐬���ꂽ���`�F�b�N
	if (g_hwnd == NULL) { return -1; }

	//�E�B���h�E�̕\��
	ShowWindow(g_hwnd, SW_SHOW);

	//�Q�[���}�l�[�W���[�̏�����
	GameManager::Instance()->Initialize(g_hwnd);

	//�t���[�����䏈��
	QueryPerformanceFrequency(&g_timeFrequency);  //�X�V�p�x�̎擾
	QueryPerformanceCounter(&g_timeStart);  //����v�Z�p��1�x���ݎ��Ԃ��擾

	//���b�Z�[�W���[�v�̊J�n
	while (true)
	{
		if (!MainLoop())
		{
			break;
		}
	}

	return g_msg.wParam;
}

HRESULT MainLoop()
{
	FrameControl();

	//���b�Z�[�W�����邩�Ȃ����`�F�b�N
	if (PeekMessage(&g_msg, NULL, 0, 0, PM_NOREMOVE))
	{
		//���b�Z�[�W�̎擾
		if (GetMessage(&g_msg, NULL, 0, 0))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
		}
		else
		{
			return FALSE;
		}
	}
	GameManager::Instance()->InputGet();
	GameManager::Instance()->UpDateGame();
	return TRUE;
}

//�x�[�X�E�B���h�E�v���V�[�W��
LRESULT CALLBACK BaseWindProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//�t���[������
void FrameControl()
{
	//��r�p�Ɍ��ݎ����̎擾
	QueryPerformanceCounter(&g_timeEnd);

	//�b�P�ʂŃt���[���Ԃ̕b���擾
	g_frameTime = (float)(g_timeEnd.QuadPart - g_timeStart.QuadPart) / (float)(g_timeFrequency.QuadPart);

	//�ݒ肵���Œ�t���[���ԕb���Z�����ǂ����̔�r
	if (g_frameTime < G_MIN_FREAM_TIME)
	{
		//OutputDebugString("sleep\n");

		//�~���b�ɕϊ����適Sleep()�̓~���b�ݒ�Ȃ̂�
		g_sleepTime = (DWORD)((G_MIN_FREAM_TIME - g_frameTime) * 1000);

		timeBeginPeriod(1);  //����\���グ��i�������Ȃ���Sleep()�̐��x�̓K�^�K�^�H�j
		Sleep(g_sleepTime);
		timeEndPeriod(1);    //����\�߂�

		return;
	}

	if (g_frameTime > 0.0) { // �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
		g_fps = (g_fps*0.99f) + (0.01f / g_frameTime); // ����fps���v�Z
#ifdef _DEBUG
// �f�o�b�O�p(�f�o�b�K��FSP�o��)
#ifdef UNICODE
		std::wstringstream stream;
#else
		std::stringstream stream;
#endif
		stream << g_fps << " FPS" << std::endl;
		//�J�E���^�t����10���1��o�́A�Ƃ��ɂ��Ȃ��ƌ��Â炢������
		OutputDebugString(stream.str().c_str());
#endif  //_DEBUG
	}

	g_timeStart = g_timeEnd;
}