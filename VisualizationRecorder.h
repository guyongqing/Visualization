#pragma once

// ϵͳ¼����
#include <IRecorder.h>
#include <IRecorder_Guid.h>

// ��ͼ����
#include "VisualizationDraw.h"

// ��ʼ����
#define RECORDER_SAMPLE_WIDTH		16			// �������
#define RECORDER_SAMPLE_RATE		32000		// ������
#define RECORDER_BYTES_PER_SEC		64000		// ÿ������ֽ���
#define RECORDER_CHANNEL_COUNT		1			// ������
#define RECORDER_BLOCK_ALIGN		1			// ÿ���������ֽ���
#define RECORDER_BUFFER_SIZE		1440		// ��������С
#define RECORDER_BUFFER_COUNT		64			// ����������

//************************************************************************************************
//*************************** ¼ �� ��   *********************************************************
//************************************************************************************************

// ¼������ʼ��
bool RecorderInit(HWND);
// ��¼���豸ǰ�Բ�����������
void RecorderSetParameter(WORD, DWORD, WORD, WORD, WORD, DWORD);
// ��ʼ¼��
void RecorderStart(void);
// ֹͣ¼��
void RecorderStop(void);
// ��ͣ¼��
void RecorderPause(void);
// ����¼��
void RecorderEnd(void);
// ������Ƶ����
void RecorderData(UINT, WPARAM, LPARAM);
// �豸��
void RecorderOpen(UINT, WPARAM, LPARAM);
// �豸�ر�
void RecorderClose(UINT, WPARAM, LPARAM);