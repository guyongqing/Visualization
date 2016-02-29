#pragma once

// GUID
#include <initguid.h>
// MZFC ͷ�ļ�
#include <mzfc_inc.h>
// Shell ͷ�ļ�
#include <ShellNotifyMsg.h>

// USB �¼�
#include <UsbNotifyApi.h>
// �����¼�
#include <CallNotifyApi.h>

// FPS �����ļ�
#include "Fps.h"

// �ļ����������ļ�
#include "VisualizationFile.h"
// ��괦��
#include "VisualizationMouse.h"
// ��Ϸ����
#include "VisualizationGame.h"
// �������
#include "VisualizationDraw.h"
// ͼ�λ���
#include "VisualizationPaint.h"
// ¼����
#include "VisualizationRecorder.h"

// ����
#define APP_MUTEX_NAME			L"VisualizationMutex"
#define APP_WINDOW_TEXT			L"����"
#define APP_GUID				L"{A29D7D70-62AE-4518-BAAE-9CA65128CE27}"
#define APP_VERSION_MAIN		1
#define APP_VERSION_MIDDLE		0
#define APP_VERSION_LAST		0

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************

// �����ڶ���
class MyWindow : public CMzWndEx
{

	// MZFC�����༰������Ĵ�������������
	MZ_DECLARE_DYNAMIC(MyWindow);

	// ���г�Ա
	public:

		// ���캯��
		MyWindow(void);
		// ��������
		~MyWindow(void);

		// ��������
		bool CreateWindowNow(void);

	// ������Ա
	protected:

		// ��ʼ��
		virtual BOOL OnInitDialog();
		// ��HOME����ʱ
		virtual int OnShellHomeKey(UINT, WPARAM, LPARAM);
		// ��Ϣ����
		virtual LRESULT MzDefWndProc(UINT, WPARAM, LPARAM);
		// ���˫��
		virtual void OnLButtonDblClk(UINT, int, int);
		// ����ƶ�ʱ
		virtual void OnMouseMove(UINT, int, int);		
		// ���̧��ʱ
		virtual void OnLButtonUp(UINT, int, int);
		// ��갴��ʱ
		virtual void  OnLButtonDown(UINT, int, int);

	// ˽�г�Ա
	private:



};

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************


// �� CMzApp ������Ӧ�ó�����
class MyApp : public CMzApp
{

	// ���г�Ա
	public:

		// ���캯��
		MyApp(void);
		// ��������
		~MyApp(void);

	// ������Ա
	protected:

		// ��ʼ��
		virtual BOOL Init(void);
		// ����
		virtual int Run(void);

	// ˽�г�Ա
	private:

		// �����ж�
		bool IsAppRunning(void);
		// ��Ϣ����
		void MessageRegister(void);

};