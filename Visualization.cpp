// Visualization.cpp : ����Ӧ�ó������ڵ㡣
//

// Ԥ����
#include "stdafx.h"
// ͷ�ļ�
#include "Visualization.h"

// ȫ��Ӧ�ó������
MyApp TheApp;

// ������
MyWindow TheWindow;

// ����ȫ�ֱ���
HWND	TheHwnd;

// USB ����
int TheUsbNotify;
// ���紦��
UINT TheCallNotify;
// ���Ŵ���
UINT TheSmsNotify;
// ���Ŵ���
UINT TheMmsNotify;
// ��������
UINT TheBlueToothNotify;

// ������Ϣ
DWORD TheCallMessage;
// ������Ϣ
DWORD TheSmsMessage;
// ������Ϣ
DWORD TheMmsMessage;

// �շ���֤
bool TheLicenseVerify = false;

// MZFC�����༰������Ĵ������������
MZ_IMPLEMENT_DYNAMIC(MyWindow)

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************

// ���캯��
MyWindow::MyWindow(void)
{
}

// ��������
MyWindow::~MyWindow(void)
{
}

// ��ʼ��
BOOL MyWindow::OnInitDialog()
{
	
	// ������ִ�и�����ĳ�ʼ������
	if (!CMzWndEx::OnInitDialog())
	{
		return false;
	}

	// �ɹ�
	return true;

}

// ��HOME��������ʱ
int MyWindow::OnShellHomeKey(UINT message, WPARAM wParam, LPARAM lParam)
{

	// Ĭ���˳�
	return SHK_RET_DEFAULT;

}

// ���˫��
void MyWindow::OnLButtonDblClk(UINT fwKeys, int xPos, int yPos)
{

	// ��������¼�
	MouseClick(xPos,yPos);

}

// ���̧��ʱ
void MyWindow::OnLButtonUp(UINT fwKeys, int xPos, int yPos) 
{

	// ��������¼�
	MouseUp(xPos,yPos);

}

// ����ƶ�ʱ
void MyWindow::OnMouseMove(UINT fwKeys, int xPos, int yPos) 
{

	// ��������¼�
	MouseMove(xPos,yPos);

}

// ��갴��ʱ
void  MyWindow::OnLButtonDown(UINT fwKeys, int xPos, int yPos) 
{

	// ��������¼�
	MouseDown(xPos,yPos);

}

// ��Ϣ����
LRESULT MyWindow::MzDefWndProc(UINT message, WPARAM  wParam, LPARAM  lParam) 
{

	// ĳЩ״̬
	int id = int(lParam);

	// ������Ϣ
	switch(message){

		// �õ�����
		case WM_SETFOCUS:
			
			// ������Ϸ
			GameLive();
			break;

		// ʧȥ����	
		case WM_KILLFOCUS:

			// ֹͣ��Ϸ
			GameDead();
			break;

		// �����������Ϣ
		case MZ_WM_TASKMAN_ONOFF:

			// ��ʾ�����������Ϣ
			if(lParam==TASKMAN_SHOW_WND){
				// ֹͣ��Ϸ
				GameDead();
			}

			// ���������������
			if(lParam==TASKMAN_EXEC_PROG){
				// ������Ϸ
				GameLive();
			}

			// ���������������Ϣ
			if(lParam==TASKMAN_QUIT_WND){
				if (GetForegroundWindow()==m_hWnd){
					// ������Ϸ
					GameLive();
				}
			}

			break;

		
		// ������
		case MM_WIM_DATA: 

			// ������Ƶ����
			RecorderData(message, wParam, lParam);
			break;


		// �豸��
		case MM_WIM_OPEN: 

			// �����豸��
			RecorderOpen(message, wParam, lParam);
			break;

		// �豸�ر�
		case MM_WIM_CLOSE: 

			// �����豸�ر�
			RecorderClose(message, wParam, lParam);
			break;

	}

	// U���¼�
	if(message==TheUsbNotify){

		// U�̽���
		if(wParam==USB_MASSSTORAGE_ATTACH){
			PostQuitMessage(0);
		}
	
	}

	// �����¼�
	if(message==TheBlueToothNotify){

		// ֹͣ��Ϸ
		GameDead();
	
	}

	// ����ϵͳĬ����Ϣ������
	return CMzWndEx::MzDefWndProc(message,wParam,lParam);

}

// ��������
bool MyWindow::CreateWindowNow(void)
{

	// ����������
	Create(0,0,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT, 0, 0, 0);
	SetWindowText(APP_WINDOW_TEXT);
	SetBgColor(DRAW_COLOR_BLACK);

	// ���ڶ���Ч��
	if(MzGetParam(MZGP_APP_START_ANIMATION)){
		AnimateWindow(MZ_ANIMTYPE_ZOOM_IN,true);
	}

	// ��ʾ������
	Show();

	// ���ھ��
	TheHwnd = m_hWnd;

	if(TheHwnd<=0){
		return false;
	}

	return true;

}

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************


// ���캯��
MyApp::MyApp(void)
{
}

// ��������
MyApp::~MyApp(void)
{
}

// ��Ϣ����
void MyApp::MessageRegister(void)
{

	// ע��USB��Ϣ
	TheUsbNotify = RegisterUsbNotifyMsg();

	// �����¼�
	TheCallNotify = RegisterWindowMessage(WM_CALL_MESSAGE);
	// ����Ϣ�¼�
	TheSmsNotify = RegisterWindowMessage(WM_SMS_MESSAGE);
	// �����¼�
	TheMmsNotify = RegisterWindowMessage(WM_MMS_MESSAGE);
	// �����¼�
	TheBlueToothNotify = RegisterWindowMessage(WM_BT_MESSAGE);

	// ������Ϣ
	TheCallMessage = GetCallRegisterMessage();
	// ������Ϣ
	TheSmsMessage = GetSmsRegisterMessage();
	// ������Ϣ
	TheMmsMessage = GetMmsRegisterMessage();

}

// �����ж�
bool MyApp::IsAppRunning(void)
{

	//����Ƿ��Ѿ��������ʵ����������:
    bool bFound = false;

	// ��ȡ���
    HANDLE hMutexOneInstantance = CreateMutex(NULL, true, APP_MUTEX_NAME);

	// �ҵ�ʵ��
    if (GetLastError()==ERROR_ALREADY_EXISTS){
		bFound = true;
    }

	// �ͷž��
    if(hMutexOneInstantance){
		ReleaseMutex(hMutexOneInstantance);
    }

	// ����ҵ�ʵ��
	if(bFound){
		
		//�����Ѿ������е�ʵ���Ĵ���   
		HWND pwndFirst = FindWindow((LPCTSTR)MyWindow::m_pwszMyWindowClassName, (LPCTSTR)NULL);

		// �Ѿ��ҵ�����ʵ��
		if(pwndFirst){

			// ������ڱ�����
            if(!IsWindowVisible(pwndFirst)){
				// ��ʾ����
				ShowWindow(pwndFirst, SW_SHOW);
            }

			// �����
			SetForegroundWindow(pwndFirst);

        }

	}

	return bFound;

}

// ��ʼ��
BOOL MyApp::Init()
{

	// ����Ѿ�����
	if(IsAppRunning()){
		return false;
	}

	// ���ض���
	HideMzTopBar();

	// ע��COM
	CoInitializeEx(0, COINIT_MULTITHREADED);

	
	// ���ڴ���ʧ��
	if(!TheWindow.CreateWindowNow()){
		return false;
	}

	// ע�������Ϣ
	MessageRegister();

	// ��ȡ��ǰ��������Ŀ¼
	FileGetPath();

	// �ɹ�
	return true;

}

// ����
int MyApp::Run()
{

	MSG msg;

	// ¼�������󴴽�ʧ��
	if(!RecorderInit(TheHwnd)){
		GameError(GAME_ERROR_INIT);
		return false;
	}

	// ��ʼ����Ϸ
	if(!GameInit(TheHwnd)){
		GameError(GAME_ERROR_INIT);
		return false;
	}

	// ������Ϸ
	GameLive();

	// �����Ȩ����
	TheLicenseVerify = LicenseVerify();

	// ����FPS����
	FpsInit();

	// ��ʼFPS��ʱ
	FpsStart();

	// ����Ϣѭ��
	while(true){

		// ������Ϣ
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){

			// �˳�
			if(msg.message==WM_QUIT){
				goto End;
			}

			// ����������Ϣ
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		
		}

		// ��Ϸ����״̬
		if(GameIsLive()){

			// ������Ϸ
			GameRun();

			// �ȴ���һ֡
			FpsWait();

		}

		// �ó�����
		Sleep(0);
	
	}

	// ��Ϸ����
	End:GameEnd();

	return true;

}