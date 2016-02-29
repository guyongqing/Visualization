#pragma once

// Ԥ����
#include "stdafx.h"

// ͼ�λ���
#include "VisualizationRecorder.h"

// �����ṹ
WAVEFORMATEX	TheRecorderWaveFormat;

// �����豸���
HWAVEIN			TheRecorderWaveIn;

// ������
BYTE			TheRecorderBuffer[RECORDER_BUFFER_COUNT][RECORDER_BUFFER_SIZE];

// ���ݱ���
BYTE			TheRecorderWaveData[RECORDER_BUFFER_SIZE];

// �������
PWAVEHDR		TheRecorderWaveHandle[RECORDER_BUFFER_COUNT];

// ϵͳ¼��������
IRecord*		TheRecorder;

// ����������
int TheRecorderBufferIndex = 0;

// �Ƿ���¼��״̬
bool TheRecorderStatus = false;

//************************************************************************************************
//*************************** ¼ �� ��   *********************************************************
//************************************************************************************************

// ¼������ʼ��
bool RecorderInit(HWND hwnd)
{

	// ע��¼����COM����
	if(FAILED( CoCreateInstance(CLSID_Recorder,NULL,CLSCTX_INPROC_SERVER,IID_MZ_Record,(void **)&TheRecorder))){
      return false;
    }

	// �趨�ص�����
	TheRecorder->SetCallBackWindow(hwnd, RECORDER_MODE);

	// �ͷ�ϵͳ¼����
	if(TheRecorder){
		TheRecorder->Release();
	}

	// ׼������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// ���뻺����
		ZeroMemory(TheRecorderBuffer[i],RECORDER_BUFFER_SIZE);
		// ������������ڴ�
		TheRecorderWaveHandle[i]=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));

	}

	// ��ʼ�������ṹ
	RecorderSetParameter(RECORDER_SAMPLE_WIDTH,RECORDER_SAMPLE_RATE,RECORDER_CHANNEL_COUNT,WAVE_FORMAT_PCM, RECORDER_BLOCK_ALIGN, RECORDER_BYTES_PER_SEC);

	// ��¼���豸ʧ��
	if(waveInOpen(&TheRecorderWaveIn,WAVE_MAPPER,&TheRecorderWaveFormat,(DWORD)hwnd,NULL,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
		return false;
	}

	// ��ʼ���������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// �����������ṹ
		TheRecorderWaveHandle[i]->lpData = (LPSTR)TheRecorderBuffer[i];	
		TheRecorderWaveHandle[i]->dwBufferLength = RECORDER_BUFFER_SIZE;
		TheRecorderWaveHandle[i]->dwBytesRecorded = 0;
		TheRecorderWaveHandle[i]->dwUser = 0;
		TheRecorderWaveHandle[i]->dwFlags = 0;
		TheRecorderWaveHandle[i]->dwLoops = 1;
		TheRecorderWaveHandle[i]->lpNext = NULL;
		TheRecorderWaveHandle[i]->reserved = 0;

		// ׼��������
		waveInPrepareHeader(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof(WAVEHDR));
		// ��ӻ�����
		waveInAddBuffer(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof (WAVEHDR)) ;

	}

	// �����������
	ZeroMemory(TheRecorderWaveData,RECORDER_BUFFER_SIZE);

	// ����ͼģ�鷢������ָ��
	DrawSetWaveData((SHORT*)TheRecorderWaveData);

	// ������
	return true;

}

// ��¼���豸ǰ�Բ�����������
void RecorderSetParameter(WORD sampleWidth, DWORD sampleRate, WORD channelCount, WORD dataType, WORD blockAlign, DWORD bytesPerSec)
{

	// ��Ƶ��ʽ����
	TheRecorderWaveFormat.wFormatTag = dataType;
	// ������
	TheRecorderWaveFormat.nChannels = channelCount;
	// ����Ƶ��
	TheRecorderWaveFormat.nSamplesPerSec = sampleRate;
	// �������
	TheRecorderWaveFormat.wBitsPerSample = sampleWidth;
	// ÿ���������ֽ���
	TheRecorderWaveFormat.nBlockAlign = blockAlign;
	// ÿ��ɼ����ֽ���
	TheRecorderWaveFormat.nAvgBytesPerSec = bytesPerSec;

}

// ��ʼ¼��
void RecorderStart(void)
{

	// ��ʼ¼��
	waveInStart(TheRecorderWaveIn) ;

}

// ֹͣ¼��
void RecorderStop(void)
{

	// ֹͣ¼��
	waveInReset(TheRecorderWaveIn);

}

// ����¼��
void RecorderEnd(void)
{

	// �ر��豸
	waveInClose(TheRecorderWaveIn);

	// �ͷ��������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		if(TheRecorderWaveHandle[i]){free(TheRecorderWaveHandle[i]);}
	}

}

// ����¼������
void RecorderData(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// �Ѿ�¼������
	DWORD size = ((PWAVEHDR)lParam)->dwBytesRecorded;
	LPSTR data = ((PWAVEHDR)lParam)->lpData;

	// ������
	if(size==RECORDER_BUFFER_SIZE){
		// ��������
		CopyMemory(TheRecorderWaveData,data,size);
	}
	
	// ������������ϵͳ
	waveInAddBuffer(TheRecorderWaveIn, (PWAVEHDR)lParam, sizeof(WAVEHDR));	

}

// �豸��
void RecorderOpen(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// ��ʼ¼��
	TheRecorderStatus = true;

}

// �豸�ر�
void RecorderClose(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// �ͷŻ�����
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		waveInUnprepareHeader(TheRecorderWaveIn, TheRecorderWaveHandle[i], sizeof (WAVEHDR));
	}

	// ��ʼ¼��
	TheRecorderStatus = false;

}