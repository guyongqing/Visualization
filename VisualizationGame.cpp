
// Ԥ����
#include "stdafx.h"

// ��Ϸ����
#include "VisualizationGame.h"

HWND TheGameHwnd;

// ��Ϸȫ�ֱ���
bool TheGameLive = false;		// ��Ϸ�״̬
bool TheGamePause = false;		// ��Ϸ��ͣ״̬

// ��ǰ��Ϸ״̬
int TheGameStatus = GAME_STATUS_START;

//************************************************************************************************
//*************************** �� Ϸ �� �� ********************************************************
//************************************************************************************************

// ��Ϸ����
void GameError(LPTSTR msg)
{

	// ��Ϸ��ͣ
	GamePause();

	// ��Ϸ����
	GameEnd();

	// ��ʾ������Ϣ
	MzMessageBox(0,msg,GAME_ERROR,MB_OK,0,false);

	// �˳�����
	PostQuitMessage(0);

}

// ��Ϸ��ʼ��
bool GameInit(HWND hwnd)
{

	// ����û����ȷ����
	if(!hwnd){
		return false;
	}

	// ��ʼ�� DirectDraw ʧ��
	if(!DirectDrawInit(hwnd)){
		return false;
	}

	// ���ھ��
	TheGameHwnd = hwnd;

	// ��ʼ���ɹ���������ʾ��־����
	GameStatus(GAME_STATUS_RUN);

	// ������Ϸ
	TheGameLive = true;

	return true;

}

// ��ʼ����Ϸ����
void GameDataInit(void)
{

	

}

// ��Ϸ��ʼ
void GameRun(void)
{
	
	// ���ƻ���
	Draw();

}

// ������Ϸ
void GameContinue(void)
{

	// ��ͣ��Ϸ
	TheGamePause = false;

}		

// ��ͣ��Ϸ
void GamePause(void)
{

	// ��ͣ��Ϸ
	TheGamePause = true;	

}

// ֹͣ��Ϸ
void GameDead(void)
{

	// �ر���Ϸ״̬
	TheGameLive = false;	
	// ��ͣ��Ϸ
	GamePause();	
	// ��ʾ����
	ShowMzTopBar();
	// ֹͣ¼��
	RecorderStop();

}

// ��Ϸ����
void GameEnd(void)
{

	// ֹͣ��Ϸ
	GameDead();	
	// ����¼��
	RecorderEnd();
	// ���� DDraw ����
	DirectDrawEnd();

}

// ��Ϸ����
void GameLive(void)
{

	// ���ھ��
	if(TheGameHwnd){

		// ����Ϸ״̬
		TheGameLive = true;						
		// ���ض���
		HideMzTopBar();
		// ��ʼ¼��
		RecorderStart();
		
	}

}

// ������Ϸ״̬
void GameStatus(int s)
{

	// ������Ϸ״̬
	TheGameStatus = s;

}

// �Ƿ񼤻�
bool GameIsLive(void)
{

	return TheGameLive;

}