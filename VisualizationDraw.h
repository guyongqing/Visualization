#pragma once

// DirectDraw
#include <ddraw.h>

// ��Ļ����
#define	DRAW_SCREEN_WIDTH			480			// ��Ļ���
#define	DRAW_SCREEN_HEIGHT			720			// ��Ļ�߶�
#define	DRAW_SCREEN_WIDTH_MID		240			// ��Ļ���һ��
#define	DRAW_SCREEN_HEIGHT_MID		360			// ��Ļ�߶�һ��
#define DRAW_SCREEN_COLOR			16			// 16 λɫ
#define DRAW_SCREEN_SIZE			345600		// ��Ļռ���ֽ���

// ������ɫ
#define DRAW_COLOR_BLACK			0					// ��ɫ
#define DRAW_COLOR_WHITE			0xFFFF				// ��ɫ
#define DRAW_COLOR_GREEN			0x07E0				// ��ɫ
#define DRAW_COLOR_BLUE				0x001F				// ��ɫ
#define DRAW_COLOR_RED				0xF800				// ��ɫ
#define DRAW_COLOR_YELLOW			0xFFE0				// ��ɫ

// ��ɫ�������
#define DRAW_COLOR_STEP				32					// ������
#define DRAW_COLOR_ALL_STEP			0x821				// ������
#define DRAW_COLOR_RED_STEP			0x800				// ��ɫ
#define DRAW_COLOR_YELLOW_STEP		0x820				// ��ɫ
#define DRAW_COLOR_GREEN_STEP		0x20				// ��ɫ
#define DRAW_COLOR_BLUE_STEP		0x1					// ��ɫ
#define DRAW_COLOR_WHITE_STEP		0x841				// ��ɫ


// �����Ƿ�͸��
#define DRAW_BLT_NORMAL				0				// �������
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// ͸�����

// ��͸������
#define DRAW_ALPHA_MIN				0				// ��С��͸��ɫ
#define DRAW_ALPHA_MID				128				// 50% ��͸��ɫ
#define DRAW_ALPHA_MAX				255				// ����͸��ɫ

// ͼ�񻺳�
#define DRAW_BACKGROUND_WIDTH		480			// �������
#define DRAW_BACKGROUND_HEIGHT		720			// �����߶�
#define DRAW_BACKGROUND_SIZE		691200		// ������С
#define DRAW_BACKGROUND_FILE		L"Visualization.dat"

#define DRAW_FOREGROUND_WIDTH		1			// ǰ�����
#define DRAW_FOREGROUND_HEIGHT		1			// ǰ���߶�
#define DRAW_FOREGROUND_SIZE		4			// ǰ����С
#define DRAW_FOREGROUND_FILE		L"10681027.dat"

// ������ʾ����
#define DRAW_WAVE_MIN				-32767			// ��Сֵ
#define DRAW_WAVE_MIDDLE			0				// �м�ֵ
#define DRAW_WAVE_MAX				32767			// ���ֵ
#define DRAW_WAVE_RATE_SMALL		69				// ��ֵС
#define DRAW_WAVE_RATE				138				// ��ֵ
#define DRAW_WAVE_RATE_BIG			276				// ��ֵ��

// ������ʾ����
#define DRAW_NAME_MIN				0			// ��Сֵ
#define DRAW_NAME_MAX				7			// ���ֵ
#define DRAW_NAME_WAVE				0			// ����
#define DRAW_NAME_WAVE_LINE			1			// ��������
#define DRAW_NAME_LASER				2			// ����
#define DRAW_NAME_LASER_LINE		3			// ��������
#define DRAW_NAME_DOT				4			// ����
#define DRAW_NAME_DOT_LINE			5			// ��������
#define DRAW_NAME_STAR				6			// ����
#define DRAW_NAME_STAR_LINE			7			// ��������

// ����״̬
#define DRAW_STATUS_START			0			// ��ʼ
#define DRAW_STATUS_LOGO			1			// ��־
#define DRAW_STATUS_RUN				2			// ����

// ��������
#define DRAW_LOCATION_COUNT			720			// �������

// ��������
#define DRAW_JACKSON_COUNT				10			// ��������
#define DRAW_JACKSON_NAME_STAND			0			// վ��
#define DRAW_JACKSON_NAME_WALK			1			// ����
#define DRAW_JACKSON_NAME_MOONWALK		2			// ̫�ղ�
#define DRAW_JACKSON_NAME_KICK			3			// ����
#define DRAW_JACKSON_NAME_SPINING		4			// ��ת
#define DRAW_JACKSON_NAME_BEAT_IT		5			// BEAT
#define DRAW_JACKSON_NAME_BEAT_IT_DANCE	6			// BEAT IT DANCE
#define DRAW_JACKSON_NAME_BILLIE_JEAN	7			// BILLIE JEAN
#define DRAW_JACKSON_NAME_JUMP			8			// ����
#define DRAW_JACKSON_NAME_THRILLER		9			// ��ʬ
#define DRAW_JACKSON_NAME_SMOOTH		10			// ��

// ���ﶯ������
#define DRAW_JACKSON_STAND_COUNT		2			// վ��֡��
#define DRAW_JACKSON_STAND_WIDTH		46			// վ�����
#define DRAW_JACKSON_STAND_HEIGHT		130			// վ���߶�

#define DRAW_JACKSON_WALK_COUNT			7			// ����֡��
#define DRAW_JACKSON_WALK_WIDTH			60			// ���п��
#define DRAW_JACKSON_WALK_HEIGHT		130			// ���и߶�

// ����ṹ
typedef struct{

	RECT*	left;		// ������������
	RECT*	right;		// ������������
	BYTE*	step;		// ÿһ������
	BYTE*	time;		// ÿһ��ʱ��
	BYTE	count;		// ֡��
	BYTE	width;		// ���
	BYTE	height;		// �߶�

}MICHAEL_JACKSON;

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}
#define _RGB16BIT565(r,g,b) ((b&31)+((g&63)<<5)+((r&31)<<11))

// ��ʼ��
bool DirectDrawInit(HWND);
// ����
void DirectDrawEnd(void);
// ��������
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** ����״̬ ***********************************************************
//************************************************************************************************

// ��������״̬��������
void DrawSetWaveNameStep(int);

// ��������״̬��ֱ�ӣ�
void DrawSetWaveName(int);

//************************************************************************************************
//*************************** �Ӿ�Ч�� ***********************************************************
//************************************************************************************************

// ���Ʋ���
void DrawVisualizationWave(USHORT*, int);
// ��������
void DrawVisualizationStar(USHORT*, int, bool);
// ���Ʋ�������
void DrawVisualizationWaveLine(USHORT*, int, bool);
// ���Ƽ�������
void DrawVisualizationLaserLine(USHORT*, int, bool);
// ���Ƶ���
void DrawVisualizationDotLine(USHORT*, int, bool);

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��������
void DrawMichaelJackson(void);

//************************************************************************************************
//*************************** ��־���� ***********************************************************
//************************************************************************************************

// ���Ʊ�־
void DrawLogo(void);

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��Ϸ�������
void Draw(void);
// ����Ļ���ڴ棩
void DrawCls(USHORT*, int, USHORT);
// ����
void DrawClsRect(void);
// ����������
void DrawPrimary(void);

/*************************** ���λ��� ****************************************/

// ���ƾ���
void DrawRect(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// ���ٻ��ƾ��Σ���͸����
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);

//************************************************************************************************
//*************************** ��Ƶ���� ***********************************************************
//************************************************************************************************

// ����ͼģ�鷢������ָ��
void DrawSetWaveData(SHORT*);
// ��������ͼ��
void DrawWaveData(void);

//************************************************************************************************
//*************************** �� �� �� ȡ ********************************************************
//************************************************************************************************

// ��ȡͼ���ļ�
bool LoadingImageFile(LPTSTR, int, LPDIRECTDRAWSURFACE);